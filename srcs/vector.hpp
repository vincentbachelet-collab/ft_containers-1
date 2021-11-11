#pragma once

#include <iostream>
#include <stdexcept>
#include <sstream>
#include <memory>//allocator
#include <iterator>
#include <vector>
#include <climits>
#include <limits>
#include <algorithm>
#include <cstring>

/*
** Voir pourquoi on ne traite pas les reverse iterator 
** de la meme facon que les iterateurs
*/
#include "../srcs/vector_iterator.hpp"
#include "../srcs/reverse_iterator.hpp"
#include "../srcs/pair.hpp"
#include "utility"//std::pair

# define DEBUG 0

/*
** Documentation
** https://www.cplusplus.com/reference/vector/vector/
** Les vecteurs sont des "dynamic size arrays"
** c'est-a-dire qu'ils ont la capacite d'agrandir leur capacite au fur et a mesure
** que l'on ajoute des elements.
** Contiguous storage locations for their elements.
** They can be access by using offsets on regular pointers to its elements.
*/
namespace ft
{
	//https://docs.microsoft.com/fr-fr/cpp/standard-library/allocator-class?view=msvc-170
	/*
	*** Notion d'allocator
	** allocator, it provides a layer of abstraction for the user.
	** allocator can return constructed object, non-initialized memory space,
	** destroy an object or release the space.
	** STL containers use allocator to get memory space and create object.
	*/
    template < typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	//dans le code source c est protected, verifier ce qu'il est preferable
	public:
		typedef T                                        value_type;
		//typedef value_type*                            pointer_type;
		//typedef value_type&                            reference_type;
		typedef Alloc                                    allocator_type;
		typedef typename allocator_type::reference       reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type       size_type;
		typedef typename allocator_type::pointer         pointer;
		typedef typename allocator_type::const_pointer   const_pointer;
		typedef vector_iterator<value_type>              iterator;
		typedef vector_iterator<value_type const>        const_iterator;
		typedef ft::reverse_iterator<iterator>           reverse_iterator;
		typedef ft::reverse_iterator<const_iterator>     const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;

	private:
		size_type		_size;//nombre d'elements effectifs
		size_type		_capacity;//taille memoire allouee
		allocator_type	_allocator;//notre allocateur sur lequel on va appeler allocate
		pointer			_ptr;//pointeur vers le premier element du vecteur

	public:
		/*
		** Constructeurs 
		** default, fill, range, copy
		** J'ai retire le keyword explicit puisqu'il ne fait pas partie du standard 98
		** https://en.cppreference.com/w/cpp/container/vector/vector
		*/
		vector(const allocator_type &alloc = allocator_type()): _size(0), _capacity(0), _allocator(alloc), _ptr(NULL)//_ptr(_allocator.allocate(_capacity)
		{
			if (DEBUG == 1)
			{
				std::cout << "vector default constructor called" << std::endl;
			}
		}

		/*
		** This constructor allows to create a vector with n elements of value val
		** This constructor must call construct 
		** fill
		*/
		vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()): _size(n), _capacity(0), _allocator(alloc), _ptr(NULL))
		{
			if (DEBUG)
			{
				std::cout << "vector fill constructor called" << std::endl;
			}
			/* 
			** On doit d'abord allouer la place necessaire
			** Il faut recuperer via allocate le premier element (_p) du vector
			*/
			this->_p = this->_allocator.allocate(n);
			size_t i = 0;
			while (i < n)
			{
				/* 
				** Construct in defined in header <memory> (it is not asked to reimplement it)
				** Constructs an object of type T in allocated 
				** uninitialized storage pointed to by p, using placement-new 
				** Calls new((void *)p) T(val)
				*/
				/*
				** Va permettre de "construire" chaque elements 
				*/
				this->_allocator.construct(&_ptr[i], val);
				i++;
			}
		}

		/*
		** Troisieme constructeur 
		** range -> arguments : un iterateur first et un iterateur last
		** Constructs the container with the contents of the range [first, last).
		*/

		/*
		** This constructor has the same effect as vector(static_cast<size_type>(first), 
		** static_cast<value_type>(last), a) if InputIt is an integral type.
		** http://www.open-std.org/jtc1/sc22/wg21/docs/papers/2018/p1206r0.pdf
		*/
		template<typename InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type &alloc = allocator_type()) : _p(NULL), _size(0), _capacity(0), _allocator()//_allocator(alloc)
		{
			/*std::vector<T,Allocator>::assign */
			this->assign(first, last);
		}

		/*
		** Destructeur
		** TODO: voir le conde source, voir pourquoi destroy puis deallocate ?
		** pourquoi pas clear ? erase ?
		*/
		~vector()
		{
			if (DEBUG)
			{
				std::cout << "vector destructor called" << std::endl;
			}
			ft::vector<T>::iterator it = this->begin();
			ft::vector<T>::iterator ite = this->end();

			while (it != ite)
			{
				this->_allocator.destroy(&(*it));
				//this->_allocator.destroy(it);
				it++;
			}
			this->_allocator.deallocate(this->_p, this->_capacity);
		}
		/*
		**	 Utilitaires
		*/

		/*
		** capacity
		** https://www.cplusplus.com/reference/vector/vector/capacity/
		*/
		size_type capacity() const
		{
			if (DEBUG)
			{
				std::cout << "Capacity function called" << std::endl;
				std::cout << "The capacity is now at " << this->_capacity << std::endl;
			}
			return (this->_capacity);
		}

		/*
		** size
		** https://www.cplusplus.com/reference/vector/vector/size/
		*/
		size_type size() const
		{
			if (DEBUG)
			{
				std::cout << "The size is " << this->_size << std::endl;
			}
			return (this->_size);
		}

		/*
		** max_size() const
		** returns the maximum number of elements that the vectr can hold
		** https://www.cplusplus.com/reference/vector/vector/max_size/
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
		** resize
		*/
		void resize(size_type n, value_type val = value_type())
		{
			//A revoir
			(void)val;
			if (DEBUG)
			{
				std::cout << "resize function called" << std::endl;
			}
			if (n > getCapacity())
				realloc(n);
		}

		/*
		** empty
		** https://www.cplusplus.com/reference/vector/vector/empty/
		*/
		bool empty() const
		{
			if (DEBUG)
			{
				std::cout << "empty function called" << std::endl;
			}
			if (size() != 0)
			{
				if (DEBUG)
					std::cout << "empty function will return false" << std::endl;
				return (false);
			}
			if (DEBUG)
				std::cout << "empty function will return true" << std::endl;
			return (true);
		}

		/*
		** reserve
		** https://www.cplusplus.com/reference/vector/vector/reserve/
		** request a change in capacity
		** request that the vector capacity be at least enough to contain n elements
		*/
		void	reserve(size_type n)
		{
			try
			{
				if (n > getCapacity())
					realloc(get_fit_capacity(n));
			}
			catch (std::exception &e)
			{
				throw;
			}
		}

		/*
		** Iterateurs
		*/

		/*
		** begin()
		** https://www.cplusplus.com/reference/vector/vector/begin/
		*/
		iterator begin()
		{
			if (DEBUG)
			{
				std::cout << "begin function called" << std::endl;
			}
			//voir autres techniques
			if (empty())
			{
				return (end());
			}
			return (iterator(_ptr[0]));
		}

		/*
		** begin() const
		*/
		const_iterator begin() const
		{
			if (DEBUG)
			{
				std::cout << "begin const function called" << std::endl;
			}
			if (empty())
			{
				return (end());
			}
			return (const_iterator(_ptr[0]));
		}

		/*
		** end
		** https://www.cplusplus.com/reference/vector/vector/end/
		*/
		iterator end()
		{
			if (DEBUG)
			{
				std::cout << "end function called" << std::endl;
			}
			//voir autres techniques
			if (empty())
			{
				return (end());
			}
			return (iterator(_ptr[size()]));
		}

		/*
		** end const
		*/
		const_iterator end() const
		{
			if (DEBUG)
			{
				std::cout << "end const function called" << std::endl;
			}
			//voir autres techniques
			if (empty())
			{
				return (end());
			}
			return (const_iterator(_ptr[size()]));
		}

		/*
		** rbegin
		** return reverse iterator to reverse beginning (=end)
		** https://www.cplusplus.com/reference/vector/vector/rbegin/
		*/
		reverse_iterator rbegin()
		{
			if (DEBUG)
			{
				std::cout << "rbegin function called" << std::endl;
			}
 			return (reverse_iterator(_ptr[size()]));
		}

		/*
		** const rbegin
		*/
		const_reverse_iterator rbegin() const
		{
			if (DEBUG)
			{
				std::cout << "rbegin function called" << std::endl;
			}
 			return (const_reverse_iterator(_ptr[size()]));
		}

		/*
		** rend
		*/
		reverse_iterator rend()
		{
			if (DEBUG)
			{
				std::cout << "rend fonction called" << std::endl;
			}
			//pour moi il s agit d'un cast en c style - revoir le cast ?
			return (reverse_iterator(_ptr[0]));
		}

		/*
		** rend (const)
		*/
		const_reverse_iterator rend() const
		{
			if (DEBUG)
			{
				std::cout << "rend const function called" << std::endl;
			}
			return (rend());
		}

		/*
		** Main functions = MODIFIERS
		*/

		/*
		** push_back
		*/
		void	push_back(const value_type& x)
		 {
			(void)x;
			if (DEBUG)
			{
				std::cout << "push_back function called" << std::endl;
			}
			size_type size = this->size();
			if (size == capacity())
			{

			}
			//On pourra appeler la fonction size() quand elle sera prete
		 }
		
		/*
		** assign
		** std::vector<T,Allocator>::assign
		** Replaces the contents of the container.
		*/

		/*
		** Replaces the contents with count copies of value value
		*/
		void assign( size_type count, const T& value )
		{
			//TO DO: revoir realloc
			if (n > _capacity)
				realloc(n);
		}

		/*
		** Replaces the contents with the elements from the initializer list ilist.
		*/
		template< class InputIt >
		void assign( InputIt first, InputIt last )
		{

		}

		 /*
		 ** Cleaning functions
		 */

		/*
		** erase
		** removes from the vector either a single element (position)
		** or a range ([first, last])
		** https://www.cplusplus.com/reference/vector/vector/erase/
		*/

		iterator erase(iterator first, iterator last)
		{
			if (DEBUG)
			{
				std::cout << "erase function called" << std::endl;
			}
			//a verifier
			size_type i = &(*first) - &(*begin());
			size_type j = &(*last) - &(*begin());
			if (DEBUG)
			{
				std::cout << "i equals " << i << std::endl;
				std::cout << "j equals " << j << std::endl;
			}

			for (size_type k = i; k < j; k++)
			{
				_allocator.destroy(&_ptr[k]);

			}
		}

		/*
		** Swap
		** https://www.cplusplus.com/reference/vector/vector/swap/
		** Notice that a non-member function exists with the same name, swap,
		** overloading that algorithm with an optimization that behaves like this member function.
		*/
		void	swap(vector &x)
		{
			swap(this->_size, x._size);
			swap(this->_capacity, x._capacity);
			swap(this->_allocator, x._allocator);
			swap(this->_ptr, x._ptr);
		}

		protected:
		/*
		** Utils 
		*/
		/*
		** Augmente la capacite si besoin
		** Allocation d'un nouveau _p
		** "Remplissage" du nouveau tableau
		** Suppression de l'ancien
		*/
		void				realloc(size_type target)
		{
			pointer	new_tab;
			/*
			** Augmentation de this->capacity
			*/
			setCapacity(fitted_capacity(target));
			new_tab = allocate(_capacity);
			int i = 0;
			while (i < this->getSize())
			{
				construct(i, _p[i], new_tab);
				//destroy(i);
				i++;
			}
			deallocate();
			this->_p = new_tab;
		}

		void	realloc()
		{
			if (this->_capacity == 0)
				realloc(1);
			else
				realloc(this->_capacity * 2);
		}

		/*
		** Assigne target a this->_capacity
		*/
		void				setCapacity(size_type target)
		{
			if (DEBUG)
				std::cout << "Set capacity function called" << std::endl;
			this->_capacity = target;
		}

		/*
		** Modifie la valeur de la capacity mais n'alloue et ne construit rien
		*/
		static size_type	fitted_capacity(size_type target)
		{
			size_type	capacity = 1;
			if (DEBUG)
				std::cout << "The target is " << target << std::endl;
			if (target == 0)
				return (0);
			while (capacity < target)
				capacity = capacity * 2;
			if (DEBUG)
				std::cout << "The capacity is now " << capacity << std::endl;
			return (capacity);
		}
		/*
		** Constructs an object of type T in allocated unintialized storage pointed to by p
		** using placement-new
		*/
		void	construct(size_type index, const_reference val, pointer data)
		{
			//va noud []
			_allocator.construct(_allocator.address(data[index]), val);
			if (DEBUG)
			{
				std::cout << "First construct private function called" << std::endl;
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
				std::cout << "Second construct private function called" << std::endl;
			}
		}

		/*
		** https://en.cppreference.com/w/cpp/memory/allocator/allocate
		** Allocates n * sizeof(T) bytes of uninitialized storage by calling ::operator new(std::size_t)
		*/
		pointer	allocate(size_type n)
		{
			if (DEBUG)
				std::cout << "allocate function called" << std::endl;
			return (_allocator.allocate(n));
		}
		/*
		** deallocate -> public member function (std::allocator)
		** deallocates storage
		** https://en.cppreference.com/w/cpp/memory/allocator
		*/
		void	deallocate()
		{
			if (DEBUG)
			{
				std::cout << "deallocate function called" << std::endl;
			}
			_allocator.deallocate(_ptr);
		}

		/*
		** destroy
		** destructs an object in allocated storage
		** = calls the destructor of object
		** https://en.cppreference.com/w/cpp/memory/allocator
		*/

		/*
		** Va permettre de destroy un pointeur precis
		** Appel la fonction std::allocator::destroy
		** On destroy element par element
		*/
		void 	destroy(size_type index, pointer data)
		{
			if (DEBUG)
			{
				std::cout << "Destroy index + pointer function called" << std::endl;
			}
			_allocator.destroy(_allocator.address(data[index]));
		}

		/*
		** Will call destroy on _p at the index index
		*/
		void	destroy(size_type index)
		{
			if (DEBUG)
			{
				std::cout << "destroy index parameter called" << std::endl;
			}
			destroy(index, this->_p);
		}

		/*
		** Will destroy the element which is a the position position
		*/
		void	destroy(iterator position)
		{
			if (DEBUG)
			{
				std::cout << "destroy iterator parameter function called" << std::endl;
			}
			size_type i = 0;
			iterator first = begin();
			iterator end = end();
			while (first != position && first != end)
			{
				first++;
				i++;
			}
			destroy(i);
		}

		/*
		** shift left (defined in algorithm)
		** shift the elements in the range [first, last] by n positions
		** https://en.cppreference.com/w/cpp/algorithm/shift
		*/
		protected:
			/*
			** Getters - voir si je les laisse en public
			*/
			size_type	getCapacity() const
			{
				if (DEBUG)
				{
					std::cout << "The capacity is " << this->_capacity << std::endl;
				}
				return (this->_capacity);
			}

			size_type	getSize() const
			{
				if (DEBUG)
				{
					std::cout << "The size is " << this->_size << std::endl;
				}
				return (this->_size);
			}

			pointer		getPtr() const
			{
				if (DEBUG)
				{
					std::cout << "getPtr function called" << std::endl;
				}
				return (this->ptr);
			}
			/*
			** Ajouter des setters
			*/
	};

	/*
	** Operator overload
	** https://en.cppreference.com/w/cpp/container/vector/operator_cmp
	*/

	/*
	** Swap
	** https://www.cplusplus.com/reference/vector/vector/swap/
	** exchanges the content of the container by the context of x.
	** Must have the same types but sizes may differ.
	**TODO: faire des tests
	*/
	template <typename T, typename Alloc>
	void swap(vector<T, Alloc>& x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}

	template <typename T, typename Alloc>
	/*
	*TODO: revoir pourquoi ils ne sont pas a l interieur de la classe
	*/
	bool operator==(const vector<T, Alloc> & lhs, const vector<T, Alloc> &rhs)
	{
		if (DEBUG)
		{
			std::cout << "Operator == called" << std::endl;
		}
		if (lhs.size() != rhs.size())
		{
			if (DEBUG)
				std::cout << "Comparison == is false, the size is different" << std::endl;
			return (false);
		}
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if(lhs[i] != rhs[i])
			{
				if (DEBUG)
					std::cout << "Comparison == is false, the values are different" << std::endl;
				return (false);
			}
		}
		if (DEBUG)
			std::cout << "Comparison == is true" << std::endl;
		return (true);
	}

	template <typename T, typename Alloc>
	bool operator!=(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		if (DEBUG)
			std::cout << "Operator != called" << std::endl;
		bool ret = !(lhs==rhs);
		if (DEBUG)
		{
			std::cout << "Operation != is" << ret << std::endl;
		}
		return (ret);
	}

	/*
	** Necessite d'avoir implemente lexicographical compare au prealable
	** A reprendre
	*/
	template <typename T, typename Alloc>
	bool operator<(const vector<T,Alloc> &lhs, const vector<T,Alloc> &rhs)
	{
		(void)lhs;
		(void)rhs;
		if (DEBUG)
			std::cout << "Operator < called" << std::endl;
		//return(ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}
}
