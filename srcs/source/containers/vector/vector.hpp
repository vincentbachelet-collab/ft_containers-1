#pragma once

#include "../../../../includes/common/includes.hpp"
#include "./vector_iterator.hpp"
//#include "../../utils/reverse_iterator.hpp"

class reverse_iterator;

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::size_type size_type;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		//TODO: a remettre en ft quand iterateur prets a etre teste
		typedef vector_iterator<value_type> iterator;
		typedef vector_iterator<value_type const> const_iterator;
		typedef reverse_iterator<iterator> reverse_iterator;
		//TODO: revoir les iterateurs const
		//typedef reverse_iterator<const_iterator> const_reverse_iterator;
		//typedef pointer iterator;
		//typedef const_pointer const_iterator;
		//typedef std::reverse_iterator<iterator> reverse_iterator;
		//typedef std::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;

	private:
		size_type _size;		   //taille du vecteur (remplie)
		size_type _capacity;	   //taille en terme de capacite/memoire
		allocator_type _allocator; //type de l'allocateur du container
		pointer _ptr;			   //Addresse du premier element du vecteur (a verifier en test)

	public:
		pointer get_ptr(void)
		{
			return (this->_ptr);
		}

		void set_ptr(pointer ptr)
		{
			this->_ptr = ptr;
		}

		size_type get_size(void)
		{
			return (this->_size);
		}

		void set_size(size_type size)
		{
			this->_size = size;
		}

		size_type get_capacity(void)
		{
			return (this->_capacity);
		}

		void set_capacity(size_type capacity)
		{
			this->_capacity = capacity;
		}

		allocator_type get_allocator(void)
		{
			return (this->_allocator);
		}

		void construct_alloc(pointer ptr, const value_type val)
		{
			this->_allocator.construct(ptr, val);
		}

		void alloc_vec(size_type len)
		{
			set_ptr(get_allocator().allocate(len));
		}

		//https://en.cppreference.com/w/cpp/container/vector/vector
		//Constructeur par defaut
		vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc), _ptr(NULL) {}

		//Iterateur (necessaires pour tester les autres constructeurs notamment)
		iterator begin()
		{
			if (empty())
				return (end());
			return (iterator(_ptr));
		}

		const_iterator begin() const
		{
			if (empty())
				return (end());
			return (const_iterator(_ptr[0]));
		}

		iterator end()
		{
			if (empty())
				return (end());
			return (iterator(this->_ptr + this->_size));
		}

		const_iterator end() const
		{
			if (empty())
				return (end());
			return (const_iterator(_ptr[size()]));
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(_ptr[size()]));
		}

		reverse_iterator rend()
		{
			return (reverse_iterator(_ptr[0]));
		}

		void reserve(size_type size)
		{
			if (size > this->get_capacity())
			{
				pointer n = this->_allocator.allocate(size);
				int i = 0;
				int max = this->get_size();
				while (i < max)
				{
					this->_allocator.construct(&n[i], this->_ptr[i]);
					this->_allocator.destroy(&this->_ptr[i]);
					i++;
				}
				//set_capacity(size);
				this->_allocator.deallocate(this->_ptr, this->_capacity);
				this->_ptr = n;
				set_ptr(n);
				set_capacity(size);
			}
		}

		bool empty() const
		{
			if (size() != 0)
				return (false);
			return (true);
		}

		size_type size() const
		{
			return (this->_size);
		}

		//Constructeur deprecie depuis C++11
		/* */
		vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc), _ptr(NULL)
		{
			alloc_vec(n);
			size_t i = 0;
			while (i < n)
			{
				construct_alloc(&_ptr[i], val);
				i++;
			}
		}

		/*
		vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()) : _size(n), _capacity(n), _allocator(alloc), _ptr(NULL)
		{
			_ptr = _allocator.allocate(n);
			for (size_type i = 0; i < n; i++)
				_allocator.construct(&_ptr[i], val);
		}*/

		size_t max_size() const
		{
			size_t ret = _allocator.max_size();
#if DEBUG == 1
			std::cout << "Max size function called" << std::endl;
			std::cout << "ret is " << ret << std::endl;
#endif
			return (ret);
		}

		size_type capacity() const
		{
#if DEBUG == 1
			std::cout << "Capacity function called" << std::endl;
			std::cout << "The capacity is now at " << this->_capacity << std::endl;
#endif
			return (this->_capacity);
		}

		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->get_capacity())
			{
				if (n < this->get_capacity() * 2)
					reserve(this->get_capacity() * 2);
				else
					reserve(n);
			}
			size_type i = this->get_size();
			//Construction des elements qui seraient supplementaires
			while (i < n)
			{
				//TODO: appeler la fonction que j ai faite ?
				this->_allocator.construct(&_ptr[i], val);
				i++;
			}
			//Deconstruction des elements qui seraient en trop
			i = n;
			while (i < this->get_size())
			{
				_allocator.destroy(&_ptr[i]);
				i++;
			}
			this->set_size(n);
		}

		//Assign : fill version
		void assign(size_type count, const T &value)
		{
			reserve(count);
			resize(count);
			size_type i = 0;
			while (i < count && i < this->get_size())
			{
				_allocator.destroy(&_ptr[i]);
				i++;
			}
			i = 0;
			while (i < count)
			{
				this->_allocator.construct(&_ptr[i], value);
				i++;
			}
			if (count > this->get_size())
				set_size(count);
		}

		//Assign range version
		template <class InputIterator>
		void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			size_type n = 0;
			size_type i = 0;
			for (InputIterator it = first; it != last; it++)
				n++;
			reserve(n);
			resize(n);
			for (size_type i = 0; i < n && i < _size; i++)
				_allocator.destroy(&_ptr[i]);
			for (InputIterator it = first; it != last; it++, i++)
				_allocator.construct(&_ptr[i], *it);
			if (n > this->get_size())
				set_size(n);
		}

		/*
		//range constructeur
		template <typename InputIterator>
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type &alloc = allocator_type()) : _alloc_type(alloc), _array(NULL), _size(0), _capacity(0)
		{
			size_type n = 0;
			size_type i = 0;
			for (InputIterator it = first; it != last; it++)
				n++;
			reserve(n);
			for (InputIterator it = first; it != last; it++, i++)
				this->_allocator.construct(&_p[i], *it);
			this->_size = n;
		}
		*/
	};
}
/*
		 //pointeur vers le premier element du vecteur
		

		vector(const vector &src) : _allocator(src._allocator), _size(src.size), _p(_allocator.allocate(_capacity)), _capacity(src._capacity)
		{
			if (DEBUG == 1)
				std::cout << "vector copy constructor called" << std::endl;
			size_type i = 0;
			while (i < this->_size)
			{
				_allocator.construct(&_p[i], src._p[i]);
				i++;
			}
		}

		~vector()
		{
			if (DEBUG == 1)
				std::cout << "vector destructor called" << std::endl;
			ft::vector<T>::iterator it = this->begin();
			ft::vector<T>::iterator ite = this->end();
			while (it != ite)
			{
				this->_allocator.destroy(&(*it));
				it++;
			}
			this->_allocator.deallocate(this->_p, this->_capacity);
		}

		vector &operator=(const vector &src)
		{
			if (DEBUG == 1)
				std::cout << "vector assignation operator called" << std::endl;
			if (this->_size < src._size)
			{
				reserve(src._size);
				resize(src._size);
			}
			else
			{
				int i = 0;
				while (i < this->getSize())
				{
					_allocator.destroy(&_p[i]);
					i++;
				}
			}
			this->_size = src.size;
			i = 0;
			while (i < this->_size)
			{
				_allocator.construct(&_p[i], src._p[i]);
				i++;
			}
			return (*this);
		}

		

		void resize(size_type n, value_type val = value_type())
		{
		(void)val;
		if (DEBUG == 1)
			std::cout << "resize function called" << std::endl;
		if (n > getCapacity())
			realloc(n);
		if (n > this->_capacity)
		{
			if (n < this->_capacity * 2)
				reserve(this->_capacity * 2);
			else
				reserve(n);
		}
		int i = this->_nsize;
		//Construction des elements qui seraient supplementaires
		while (i < n)
		{
			_allocator.construct(&_p[i], val);
			i++;
		}
		//Deconstruction des elements qui seraient en trop
		i = n;
		while (i < this->getSize())
		{
			_allocator.destroy(&_p[i]);
			i++;
		}
		this->_size = n;
		}

	void reserve(size_type n)
	{
		try
		{
			if (n > getCapacity())
				realloc(get_fit_capacity(n));
		}
		catch (std::exception &e)
			throw;
		if (n > this->getCapacity())
		{
			pointer_type new = _allocator.allocate(n);
			int i = 0;
			while (i < this->getSize())
			{
				_allocator.construct(&new[i], _p[i]);
				_allocator.destroy(&_p[i]);
				i++;
			}
			_allocator.deallocate(this->_p, n);
			this->_p = new;
			this->_capacity = n;
		}
	}

	protected:

	void setCapacity(size_type target)
	{
		if (DEBUG == 1)
			std::cout << "Set capacity function called" << std::endl;
		this->_capacity = target;
	}

	static size_type fitted_capacity(size_type target)
	{
		size_type capacity = 1;
		if (DEBUG == 1)
			std::cout << "The target is " << target << std::endl;
		if (target == 0)
			return (0);
		while (capacity < target)
			capacity = capacity * 2;
		if (DEBUG == 1)
			std::cout << "The capacity is now " << capacity << std::endl;
		return (capacity);
	}

	void construct(size_type index, const_reference val, pointer data)
	{
		_allocator.construct(_allocator.address(data[index]), val);
		if (DEBUG == 1)
			std::cout << "First construct private function called" << std::endl;
	}

	void construct(size_type index, const_reference val)
	{
		construct(index, val, _ptr);
		if (DEBUG == 1)
			std::cout << "Second construct private function called" << std::endl;
	}

	pointer allocate(size_type n)
	{
		if (DEBUG == 1)
			std::cout << "allocate function called" << std::endl;
		return (_allocator.allocate(n));
	}

	void deallocate()
	{
		if (DEBUG == 1)
			std::cout << "deallocate function called" << std::endl;
		_allocator.deallocate(_ptr);
	}

	void destroy(size_type index, pointer data)
	{
		if (DEBUG == 1)
			std::cout << "Destroy index + pointer function called" << std::endl;
		_allocator.destroy(_allocator.address(data[index]));
	}

	void destroy(size_type index)
	{
		if (DEBUG == 1)
			std::cout << "destroy index parameter called" << std::endl;
		destroy(index, this->_p);
	}

	void destroy(iterator position)
	{
		if (DEBUG == 1)
			std::cout << "destroy iterator parameter function called" << std::endl;
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

	void clear()
	{
		std::cout << "clear function called" << std::endl;
		this->size = 0;
	}

	iterator erase(iterator first, iterator last)
	{
		if (DEBUG == 1)
			std::cout << "erase function called" << std::endl;

		size_type i = &(*first) - &(*begin());
		size_type j = &(*last) - &(*begin());
		if (DEBUG == 1)
		{
			std::cout << "i equals " << i << std::endl;
			std::cout << "j equals " << j << std::endl;
		}
		for (size_type k = i; k < j; k++)
		{
			_allocator.destroy(&_ptr[k]);
		}
	}


		void push_back(const value_type &src)
		{
			(void)src;
			if (DEBUG == 1)
				std::cout << "push_back function called" << std::endl;
			size_type size = this->size();
			if (size == capacity())
			{
				//revoir mon realloc
				if (this->_size == this->_capacity)
				{
					if (this->_capacity == 0)
						reserve(1);
					else
						reserve(this->_capacity * 2);
				}
				_allocator.construct(&_p[this->_size], val);
				this->_size++;
				//On pourra appeler la fonction size() quand elle sera prete
			}

			void pop_back()
			{
				if (DEBUG == 1)
					std::cout << "pop back function called" << std::endl;
				_allocator.destroy(&_p[--this->size]);
			}

			void insert(iterator position, size_type n, const value_type &val)
			{
				size_type begin_to_p = 0;
				iterator it = this->begin();
				size_type pos_to_end = 0;
				while (it != position)
				{
					begin_to_p++;
					it++;
				}
				while (it != this->end())
				{
					pos_to_end++;
					it++;
				}
				if (DEBUG == 1)
				{
					std::cout << "insert fill function called" << std::endl;
					std::cout << "begin to p = " << begin_to_p << std::endl;
					std::cout << "pos to end = " << pos_to_end << std::endl;
				}
				if (this->_size + n > this->_capacity)
				{
					if (this->size + n < this->_capacity * 2)
						reserve(this->capacity * 2);
					else
						reverse(this->_size + n);
				}
				//TODO: a reprendre, tout tester
				for (size_type i = 0, i < pos_to_end; i++)
				{
					_allocator.construct(&_p[begin_to_p + n _ pos_to_end - i - 1])
				}
			}

			iterator insert(iterator position, const value_type &val)
			{
				difference_type diff = position.get_ptr() - this->_p;
				if (DEBUG == 1)
				{
					std::cout << "insert single element called" << std::endl;
					std::cout << "diff is " << diff << std::endl;
				}
				insert(position, 1, val);
				return (iterator(begin() + diff));
			}
		

		void swap(vector &x)
		{
			swap(this->_size, x._size);
			swap(this->_capacity, x._capacity);
			swap(this->_allocator, x._allocator);
			swap(this->_ptr, x._ptr);
		}

	public:
		reference operator[](size_type n)
		{
			reference ref = this->_p[n];
			if (DEBUG == 1)
				std::cout << "Value accessed is " << ref << std::endl;
			return (ref)
		}

		const reference operator[](size_type n) const
		{
			reference ref = this->_p[n];
			if (DEBUG == 1)
				std::cout << "Value accessed is " << ref << std::endl;
			return (ref)
		}

		reference at(size_type n)
		{
			if (n >= this->_size)
				throw std::out_of_range("out of range");
			reference ref = _p[n];
			if (DEBUG == 1)
			{
				std::cout << "at operator called" << std::endl;
				std::cout << ref << std::endl;
			}
			return (ref);
		}

		const reference at(size_type n) const
		{
			if (n >= this->_size)
				throw std::out_of_range("out of range");
			reference ref = _p[n];
			if (DEBUG == 1)
			{
				std::cout << "at const operator called" << std::endl;
				std::cout << ref << std::endl;
			}
			return (ref);
		}

		reference front()
		{
			reference ref = _p[0];
			if (DEBUG == 1)
			{
				std::cout << "front accessor called" << std::endl;
				std::cout << "ref is " << ref << std::endl;
			}
			return (ref);
		}

		const_reference front() const
		{
			reference ref = _p[0];
			if (DEBUG == 1)
			{
				std::cout << "front accessor called" << std::endl;
				std::cout << "ref is " << ref << std::endl;
			}
			return (ref);
		}

		reference back()
		{
			reference ref = this->_p[this->_size - 1];
			if (DEBUG == 1)
			{
				std::cout << "back accessor called" << std::endl;
				std::cout << "ref is " << ref << std::endl;
			}
			return (ref);
		}

		const_reference back() const
		{
			reference ref = this->_p[this->_size - 1];
			if (DEBUG == 1)
			{
				std::cout << "back accessor called" << std::endl;
				std::cout << "ref is " << ref << std::endl;
			}
			return (ref);
		}

		allocator_type get_allocator() const
		{
			if (DEBUG == 1)
				std::cout << "get_allocator function called" << std::endl;
			return (this->_allocator);
		}

	protected:
		size_type getCapacity() const
		{
			if (DEBUG == 1)
				std::cout << "The capacity is " << this->_capacity << std::endl;
			return (this->_capacity);
		}

		size_type getSize() const
		{
			if (DEBUG == 1)
				std::cout << "The size is " << this->_size << std::endl;
			return (this->_size);
		}

		pointer getPtr() const
		{
			if (DEBUG == 1)
				std::cout << "getPtr function called" << std::endl;
			return (this->ptr);
		}
}

	template <typename T, typename Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		if (DEBUG == 1)
			std::cout << "Swap non member function called" << std::endl;
		x.swap(y);
	}

	template <typename T, typename Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (DEBUG == 1)
			std::cout << "Operator == called" << std::endl;
		if (lhs.size() != rhs.size())
		{
			if (DEBUG == 1)
				std::cout << "Comparison == is false, the size is different" << std::endl;
			return (false);
		}
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
			{
				if (DEBUG == 1)
					std::cout << "Comparison == is false, the values are different" << std::endl;
				return (false);
			}
		}
		if (DEBUG == 1)
			std::cout << "Comparison == is true" << std::endl;
		return (true);
	}

	template <typename T, typename Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (DEBUG == 1)
			std::cout << "Operator != called" << std::endl;
		bool ret = !(lhs == rhs);
		if (DEBUG == 1)
			std::cout << "Operation != is" << ret << std::endl;
		return (ret);
	}

	template <typename T, typename Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		(void)lhs;
		(void)rhs;
		if (DEBUG == 1)
			std::cout << "Operator < called" << std::endl;
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		bool ret1 = lhs < rhs;
		bool ret2 = lhs == rhs;
		if (DEBUG == 1)
		{
			std::cout << "operator <= called" << std::endl;
			std::cout << "ret1 is " << ret1 << std::endl;
			std::cout << "ret2 is " << ret2 << std::endl;
		}
		return (ret1 || lhs == ret2);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		bool ret = rhs < lhs;
		if (DEBUG == 1)
		{
			std::cout << "operator > called" << std::endl;
			std::cout << "ret is " << ret << std::endl;
		}
		return (ret);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		bool ret1 = lhs > rhs;
		bool ret2 = lhs == rhs;
		if (DEBUG == 1)
		{
			std::cout << "operator <= called" << std::endl;
			std::cout << "ret1 is " << ret1 << std::endl;
			std::cout << "ret2 is " << ret2 << std::endl;
		}
		return (ret1 || ret2);
	}
*/