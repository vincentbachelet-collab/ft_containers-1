#pragma once

#include <iostream>
//Set of standard exceptions
#include <stdexcept>
//Header providing string stream classes
#include <sstream>

#include <memory>//allocator
#include <iterator>
#include <vector>
#include <iterator>
#include "../srcs/vector_iterator.hpp"
#include "utility"//std::pair

#include <climits>
#include <limits>
#include <memory>
#include <stdexcept>
#include <algorithm>
#include <cstring>

# define DEBUG 0

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

	private:
		size_type		_size;//nombre d'elements effectifs
		size_type		_capacity;//taille memoire allouee
		/*
		** allocator, it provides a layer of abstraction for the user.
		** allocator can return constructed object, non-initialized memory space,
		** destroy an object or release the space.
		** STL containers use allocator to get memory space and create object.
		*/
		allocator_type	_allocator;//notre allocateur sur lequel on va appeler allocate
		pointer			_ptr;//pointeur vers le premier element du vecteur

		/*
		** Utils private
		*/
		void				setCapacity(size_type capacity)
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
				std::cout << "Second construct private function called" << std::endl;
			}
		}

		/*
		** allocate
		*/
		pointer	allocate(size_type n)
		{
			if (DEBUG)
			{
				std::cout << "allocate function called" << std::endl;
			}
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
		void	destroy(size_type index, const_reference val)
		{
			if (DEBUG)
			{
				std::cout << "Destroy 2nd function called" << std::endl;
			}
			//A verifier
			(void)val;
			_allocator.destroy(_allocator.address(_ptr[index]));
		}

		/*
		** A verifier
		*/
		void 	destroy(size_type index, pointer data)
		{
			(void)data;
			if (DEBUG)
			{
				std::cout << "Destroy first function called" << std::endl;
			}
			destroy(index, _ptr);
		}

		/**
		**TO DO: voir si necessaire d implementer realloc
		*/

		/*
		** shift left (defined in algorithm)
		** shift the elements in the range [first, last] by n positions
		** https://en.cppreference.com/w/cpp/algorithm/shift
		*/
		void	shift_left(size_type position, size_type n)
		{
			if (DEBUG)
			{
				std::cout << "shift left function called" << std::endl;
			}
			if (empty())
			{
				return;
			}
			for (size_type i = position; i < getSize() - n; i++)
			{
				_allocator.construct(&_ptr[i], _ptr[i + n]);
				_allocator.construct(&_ptr[i + n]);
			}
		}

	public:

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

	size_type getSize() const
	{
		if (DEBUG)
		{
			std::cout << "The size is " << this->_size << std::endl;
		}
		return (this->_size);
	}

	pointer getPtr() const
	{
		if (DEBUG)
		{
			std::cout << "getPtr function called" << std::endl;
		}
		return (this->ptr);
	}

	/*
	** Constructeurs
	*/
		vector(const allocator_type &alloc = allocator_type()): _size(0), _capacity(0), _allocator(alloc), _ptr(_allocator.allocate(_capacity))
		{
			if (DEBUG == 1)
			{
				std::cout << "First constructor called" << std::endl;
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
				//construct(i, val);
				/* construct takes a pointer an a const_reference val*/
				//A tester
				_allocator.construct(&_ptr[i], val);
				i++;
			}
		}

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
		** Main functions
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
