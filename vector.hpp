#pragma once

#include "includes.hpp"

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
		typedef vector_iterator<value_type> iterator;
		typedef vector_iterator<value_type const> const_iterator;
		//typedef reverse_iterator<iterator> reverse_iterator;

		//typedef typename ft::vector_iterator<T, false> iterator;
		//typedef typename ft::vector_iterator<T, true> const_iterator;

		//typedef typename ft::reverse_iterator<T, false> reverse_iterator;
		//typedef typename ft::reverse_iterator<T, true> const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;

	private:
		size_type _size;		   //taille du vecteur (remplie)
		size_type _capacity;	   //taille en terme de capacite/memoire
		allocator_type _allocator; //type de l'allocateur du container
		pointer _ptr;			   //Addresse du premier element du vecteur (a verifier en test)

	public:
		pointer get_ptr(void) const
		{
			return (this->_ptr);
		}

		void set_ptr(pointer ptr)
		{
			this->_ptr = ptr;
		}

		size_type get_size(void) const
		{
			return (this->_size);
		}

		void set_size(size_type size)
		{
			this->_size = size;
		}

		size_type get_capacity(void) const
		{
			return (this->_capacity);
		}

		void set_capacity(size_type capacity)
		{
			this->_capacity = capacity;
		}

		allocator_type get_allocator(void) const
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
		//Constructeur par defaut / default constructor
		vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc), _ptr(NULL) {}

		//Iterateur (necessaires pour tester les autres constructeurs notamment)
		iterator begin()
		{
			//if (empty())
			//	return (end());
			return (iterator(_ptr));
		}

		const_iterator begin() const
		{
			//if (empty())
			//	return (end());
			return (const_iterator(_ptr));
		}

		iterator end()
		{
			//if (empty())
			//	return (end());
			return (iterator(this->_ptr + this->_size));
		}

		/**/
		const_iterator end() const
		{
			//if (empty())
			//	return (end());
			//return (const_iterator(_ptr[size()]));
			return const_iterator(_ptr + _size);
		}

		//TODO:revoir reverse iterator et reverse iterator
		/*
		reverse_iterator rbegin()
		{
			//return (reverse_iterator(_ptr[size()]));
			return reverse_iterator(_vector + _size - 1);
		}*/

		/*
		const_reverse_iterator rbegin()
		{
			//return (reverse_iterator(_ptr[size()]));
			return const_reverse_iterator(_vector + _size - 1);
		}

		reverse_iterator rend()
		{
			return reverse_iterator(_vector - 1);
		}

		const_reverse_iterator rend() const { return const_reverse_iterator(_vector - 1); }
	*/
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

		//Constructeur deprecie depuis C++11 / fill constructeur
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

		//range constructeur ()
		//Le enable if est necessaire sinon la fonction construct ne pourra pas compiler
		//Dans le enable if, si la premiere partie avant la virgule est fausse, la deuxieme partie sera ignoree
		//Is integral represente grosso modo les data types qu on connait depuis le c
		template <class InputIterator>
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc), _ptr(NULL)
		{
			InputIterator tmp(first);
			while (tmp++ != last)
				this->_size++;

			this->set_capacity(this->get_size());
			this->_ptr = _allocator.allocate(this->get_capacity());

			for (int i = 0; first != last; ++first, ++i)
				_allocator.construct(&_ptr[i], *first);
		}

		//Copy constructor (4)
		vector(const vector &src) : _allocator(src._allocator), _size(src._size), _ptr(_allocator.allocate(_capacity)), _capacity(src._capacity)
		{
			size_type i = 0;
			while (i < this->_size)
			{
				_allocator.construct(&_ptr[i], src._ptr[i]);
				i++;
			}
		}

		//destructeur
		~vector()
		{
			size_type i = 0;
			size_type size = this->get_size();
			while (i < size)
			{
				this->_allocator.destroy(&_ptr[i]);
				i++;
			}
			this->_allocator.deallocate(this->_ptr, this->_capacity);
		}

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

		//retourne une reference de l element a la position n dans le vecteur
		reference at(size_type n)
		{
			if (n >= this->get_size())
				throw std::out_of_range("out of range");
			reference ref = this->_ptr[n];
#if DEBUG == 1
			std::cout << "at operator called" << std::endl;
			std::cout << ref << std::endl;
#endif
			return (ref);
		}

		//retourne une reference de l element a la position n dans le vecteurs
		const reference at(size_type n) const
		{
			if (n >= this->get_size())
				//C'est bien le comportement qui a lieu avec la std
				throw std::out_of_range("out of range");
			reference ref = _ptr[n];
#if DEBUG == 1
			std::cout << ref << std::endl;
#endif
			return (ref);
		}

		void push_back(const value_type &src)
		{
			size_type size = this->get_size();
			if (size == this->get_capacity())
			{
				if (this->get_capacity() == 0)
					this->reserve(1);
				else
					this->reserve(this->get_capacity() * 2);
			}
			_allocator.construct(&_ptr[_size++], src);
		}

		//deux versions de erase
		iterator erase(iterator position)
		{
			return erase(position, position + 1);
		}

		//Le compilateur appelle ca un subscript operator
		reference operator[](size_type n)
		{
			reference ref = this->_ptr[n];
			return (ref);
		}

		const reference operator[](size_type n) const
		{
			reference ref = this->_ptr[n];
			return (ref);
		}

		//Removes from the vector either a single element (position) or a range of elements ([first,last)).
		iterator erase(iterator first, iterator last)
		{
			if (first == this->end() || first == last)
				return first;

			size_type begin = 0;
			size_type first_to_last = 0;
			size_type last_to_end = 0;
			for (iterator it = this->begin(); it != first; it++)
				begin++;
			for (iterator it = first; it != last; it++)
				first_to_last++;
			for (iterator it = last; it != end(); it++)
				last_to_end++;
			for (size_type i = 0; i < last_to_end; i++)
			{
				_allocator.destroy(&_ptr[begin + i]);
				_allocator.construct(&_ptr[begin + i], _ptr[begin + i + first_to_last]);
			}
			for (size_type i = 0; i < first_to_last; i++)
				_allocator.destroy(&_ptr[begin + last_to_end + i]);
			_size -= first_to_last;
			return first;
		}

		//TODO: faire des sous fonctions
		iterator insert(iterator position, const value_type &val)
		{
			size_type pos_len = &(*position) - _ptr;
			if (size_type(_capacity - _size) >= this->size() + 1)
			{
				for (size_type i = 0; i < pos_len; i++)
					_allocator.construct(_size - i, *(_size - i - 1));
				_size++;
				_allocator.construct(&(*position), val);
			}
			else
			{
				pointer new_start = pointer();
				pointer new_end = pointer();
				pointer new_end_capacity = pointer();

				int next_capacity = (this->size() * 2 > 0) ? this->size() * 2 : 1;
				new_start = _allocator.allocate(next_capacity);
				new_end = new_start + this->size() + 1;
				new_end_capacity = new_start + next_capacity;

				for (size_type i = 0; i < pos_len; i++)
					_allocator.construct(new_start + i, *(_ptr + i));
				_allocator.construct(new_start + pos_len, val);
				for (size_type j = 0; j < this->size() - pos_len; j++)
					_allocator.construct(new_end - j - 1, *(_size - j - 1));

				for (size_type l = 0; l < this->size(); l++)
					_allocator.destroy(_ptr + l);
				if (_ptr)
					_allocator.deallocate(_ptr, this->capacity());

				_ptr = new_start;
				_size = new_end;
				_capacity = new_end_capacity;
			}
			return (iterator(_ptr + pos_len));
		}

		//TODO: corriger cette version
		/*
		void insert(iterator position, size_type n, const value_type &val)
		{
			if (n == 0)
				return;
			if (n > this->max_size())
				throw(std::length_error("vector::insert (fill)"));
			size_type pos_len = (*position) - _ptr[0];
			if (size_type(_capacity - _size) >= n)
			{
				for (size_type i = 0; i < this->size() - pos_len; i++)
					_allocator.construct(_size - i + (n - 1), _size - i - 1);
				_size += n;
				while (n)
				{
					_allocator.construct(&(*position) + (n - 1), val);
					n--;
				}
			}
			else
			{
				pointer new_start = pointer();
				pointer new_end = pointer();
				pointer new_end_capacity = pointer();

				int next_capacity = (this->capacity() > 0) ? (int)(this->size() * 2) : 1;
				new_start = _allocator.allocate(next_capacity);
				new_end_capacity = new_start + next_capacity;

				if (size_type(new_end_capacity - new_start) < this->size() + n)
				{
					if (new_start)
						_allocator.deallocate(new_start, new_start - new_end_capacity);
					next_capacity = this->size() + n;
					new_start = _allocator.allocate(next_capacity);
					new_end = new_start + this->size() + n;
					new_end_capacity = new_start + next_capacity;
				}

				new_end = new_start + this->size() + n;

				for (int i = 0; i < (&(*position) - _ptr); i++)
					_allocator.construct(new_start + i, *(_ptr + i));
				for (size_type k = 0; k < n; k++)
					_allocator.construct(new_start + pos_len + k, val);
				for (size_type j = 0; j < (this->size() - pos_len); j++)
					_allocator.construct(new_end - j - 1, *(_size - j - 1));

				for (size_type u = 0; u < this->size(); u++)
					_allocator.destroy(_ptr + u);
				_allocator.deallocate(_ptr, this->capacity());

				_ptr = new_start;
				_size = new_end;
				_capacity = new_end_capacity;
			}
		}
		*/

		template <class InputIterator>
		void insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			//(void)value;
			(void)first;
			(void)last;
			(void)false;
			/*
			size_type n = 0;
			size_type begin = 0;
			size_type end = 0;
			for (InputIterator it = first; it != last; it++)
				n++;
			iterator it = this->begin();
			for (; it != position; it++)
				begin++;
			for (; it != this->end(); it++)
				end++;
			if (_size + n > this->capacity())
			{
				if (_size + n < _capacity * 2)
					reserve(_capacity * 2);
				else
					reserve(_size + n);
			}
			for (size_type i = 0; i < end; i++)
			{
				_allocator.construct(&_ptr[begin + n + end - i - 1], _ptr[begin + end - i - 1]);
				_allocator.destroy(&_ptr[begin + end - i - 1]);
			}
			InputIterator curs = first;
			for (size_type i = 0; i < n; i++)
			{
				_allocator.construct(&_ptr[begin + i], *curs);
				curs++;
			}
			_size += n;
			*/
			bool is_valid = true;

			size_type dist = ft::distance(first, last);
			if (size_type(_capacity - _size) >= dist)
			{
				for (size_type i = 0; i < this->size() - (&(*position) - _ptr); i++)
					_allocator.construct(_size - i + (dist - 1), *(_size - i - 1));
				_size += dist;
				for (; &(*first) != &(*last); first++, position++)
					_allocator.construct(&(*position), *first);
			}
			else
			{
				pointer new_start = pointer();
				pointer new_end = pointer();
				pointer new_end_capacity = pointer();

				new_start = _allocator.allocate(this->size() * 2);
				new_end = new_start + this->size() + dist;
				new_end_capacity = new_start + (this->size() * 2);

				if (size_type(new_end_capacity - new_start) < this->size() + dist)
				{
					if (new_start)
						_allocator.deallocate(new_start, new_end_capacity - new_start);
					new_start = _allocator.allocate(this->size() + dist);
					new_end = new_start + this->size() + dist;
					new_end_capacity = new_end;
				}

				for (int i = 0; i < &(*position) - _ptr; i++)
					_allocator.construct(new_start + i, *(_ptr + i));
				for (int j = 0; &(*first) != &(*last); first++, j++)
					_allocator.construct(new_start + (&(*position) - _ptr) + j, *first);
				for (size_type k = 0; k < this->size() - (&(*position) - _ptr); k++)
					_allocator.construct(new_start + (&(*position) - _ptr) + dist + k, *(_ptr + (&(*position) - _ptr) + k));

				for (size_type l = 0; l < this->size(); l++)
					_allocator.destroy(_ptr + l);
				_allocator.deallocate(_ptr, this->capacity());

				_ptr = new_start;
				_size = new_end;
				_capacity = new_end_capacity;
			}
		}
		reference back()
		{
			reference ref = this->_ptr[this->_size - 1];
			return (ref);
		}

		const_reference back() const
		{
			reference ref = this->_ptr[this->_size - 1];
			return (ref);
		}

		void pop_back()
		{
			this->_allocator.destroy(&_ptr[--this->_size]);
		}

		void swap(vector &x)
		{
			/*
			swap(this->_size, x._size);
			swap(this->_capacity, x._capacity);
			swap(this->_allocator, x._allocator);
			swap(this->_ptr, x._ptr);
			*/
			if (x == *this)
				return;

			pointer save_start = x._ptr;
			size_type save_end = x._size;
			size_type save_end_capacity = x._capacity;
			allocator_type save_alloc = x._allocator;

			x._ptr = this->_ptr;
			x._size = this->_size;
			x._capacity = this->_capacity;
			x._allocator = this->_allocator;

			this->_ptr = save_start;
			this->_size = save_end;
			this->_capacity = save_end_capacity;
			this->_allocator = save_alloc;
		}
	};
	template <typename T, typename Alloc>
	void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
	{
		x.swap(y);
	}

	template <typename T, typename Alloc>
	bool operator==(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		if (lhs.size() != rhs.size())
		{
			return (false);
		}
		for (size_t i = 0; i < lhs.size(); i++)
		{
			if (lhs[i] != rhs[i])
			{
				return (false);
			}
		}
		return (true);
	}
}
/*

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


	public:

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