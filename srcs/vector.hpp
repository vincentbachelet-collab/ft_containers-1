#pragma once

#include <iostream>
//Set of standard exceptions 
#include <stdexcept>
//Header providing string stream classes
#include <sstream>

//Allocator
#include <memory>
#include <iterator>
#include <vector>
#include <iterator>
//#include "../srcs/utils.hpp"
#include "../srcs/vector_iterator.hpp"
#include "utility"//std::pair 
//#include "../srcs/reverse_iterator.hpp"

#include <climits>
#include <limits>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cstring>

# define DEBUG 1

namespace ft
{
	//https://docs.microsoft.com/fr-fr/cpp/standard-library/allocator-class?view=msvc-170
    template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	//dans le code source c est protected
	public:
		typedef T															value_type;
		typedef Alloc														allocator_type;
		typedef value_type&													reference;
		typedef const value_type&											const_reference;
		typedef value_type*													pointer;
		typedef const value_type*											const_pointer;
	
		/*
		** revoir les allocator traits
		*/
		//typedef allocator_traits<allocator_type>         					__alloc_traits;

		/*
		** Utiliser les iterateurs customs - implementation defined
		*/
		typedef ft::vector_iterator<value_type>								iterator;
		typedef ft::vector_iterator<const value_type>						const_iterator;

		/*
		** Pour utiliser les iterateurs de la librairie standard
		*/
		// typedef std::vector<value_type>::iterator<const value_type>		const_iterator;
		typedef typename allocator_type::size_type       					size_type;
		typedef typename allocator_type::difference_type 					difference_type;
		typedef std::reverse_iterator<iterator>          					reverse_iterator;
		typedef std::reverse_iterator<const_iterator>    					const_reverse_iterator;

		
		// typedef ft::reverse_iterator< iterator >			reverse_iterator;
		// typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
		// typedef std::ptrdiff_t							difference_type;
		// typedef size_t									size_type;

		/*
		** Prototypes
		*/
		//void push_back(const value_type& x);
	
	protected:
		//pointer 							begin;
		//pointer								end;
		//std::pair<pointer, allocator_type>	end_cap;
		//pointer								end_cap;

	private:
		size_type		_size;//nombre d'elements effectifs
		size_type		_capacity;//taille memoire allouee
		allocator_type	_allocator;//notre allocateur sur lequel on va appeler allocate
		pointer			_ptr;//pointeur vers le premier element du vecteur


		/*
		** n cap = begin + capacity
		*/
		pointer	get_endcap()
		{
			return (begin + capacity);
		}

		/* Fonctions utiles perso */
		void	setCapacity(size_type capacity)
		{
			_capacity = capacity;
		}
	
		static size_type	fitted_capacity(size_type target)
		{
			size_type	capacity = 1;
			if (DEBUG)
			{
				std::cout << "The target is " << target << std::endl;
			}
			if (target == 0)
				return (0);
			while (capacity < target)
				capacity = capacity * 2;
			if (DEBUG)
			{
				std::cout << "The capacity is now " << capacity << std::endl;
			}
			return (capacity);
		}

		/*
		** Constructs an object of type T in allocated unintialized storage pointed to by p
		** using placement-new
		*/
		void construct(size_type index, const_reference val, pointer data)
		{
			//va noud []
			_allocator.construct(_allocator.address(data[index]), val);
			if (DEBUG)
			{
			//	std::cout << "First construct private function called" << std::endl;
			}
		}

		/*
		** On va toujours "passer par l'interface du premier construct"
		*/
		void	construct(size_type index, const_reference val)
		{
			construct(index, val, _ptr);
			if (DEBUG)
			{	
			//	std::cout << "Second construct private function called" << std::endl;
			}
		}

	/*
	** Max size (a remettre en prive ?)
	*/

	/*
	** allocate
	*/
		void	allocate(size_type n)
		{
			(void)n;
			/*
			if (n > max_size())
			{

			}
			*/
		}
	public:

	/*
	** A remettre au 
	*/
	size_t	max_size() const
	{
		size_t ret = _allocator.max_size();
		if (DEBUG == 1)
		{
			std::cout << "Max size function called" << std::endl;
			std::cout << "ret is " << ret << std::endl;
		}
		return (ret);
	}
	/*
	** Constructeurs 
	*/
		vector(const allocator_type &alloc = allocator_type()): _size(0), _capacity(0), _allocator(alloc), _ptr(_allocator.allocate(_capacity))
		{
			if (DEBUG == 1)
			{
			//	std::cout << "First constructor called" << std::endl;
			}
		}

		/*
		** This constructor allows to create a vector with n elements of value val
		** This constructor must call construct
		*/
		vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()): _size(n), _capacity(fitted_capacity(n)), _allocator(alloc), _ptr(_allocator.allocate(_capacity))
		{
			if (DEBUG)
			{
				std::cout << "Second constructor called" << std::endl;
			}
			size_t i = 0;
			while (i < n)
			{
				construct(i, val);
				i++;
			}
		}

		
		/*
		** Version inspiree du code source
		*/
		template<typename InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type &alloc = allocator_type())
		{
			(void)first;
			(void)last;
			(void)alloc;
	//		for (; first != last; ++first)
	//			push_back(*first);
		}

		size_type size() const 
		{
			return (this->_size);
		}

		void	push_back(const value_type& x)
		 {
			(void)x;
			if (DEBUG)
			{
				std::cout << "push_back function called" << std::endl;
			}
			size_type size = this->size();
			//On pourra appeler la fonction size() quand elle sera prete
			
		 }
	/*
	** allocator, it provides a layer of abstraction for the user. 
	** allocator can return constructed object, non-initialized memory space, 
	** destroy an object or release the space. 
	** STL containers use allocator to get memory space and create object.
	*/

	};
}