#pragma once

//TODO: ajout include

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
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;
		typedef typename allocator_type::difference_type difference_type;

	private:
		size_type _size;		   //nombre d'elements effectifs
		size_type _capacity;	   //taille memoire allouee
		allocator_type _allocator; //notre allocateur sur lequel on va appeler allocate
		pointer _ptr;			   //pointeur vers le premier element du vecteur

	public:
		vector(const allocator_type &alloc = allocator_type()) : _size(0), _capacity(0), _allocator(alloc), _ptr(NULL) //_ptr(_allocator.allocate(_capacity)
		{
			if (DEBUG == 1)
				std::cout << "vector default constructor called" << std::endl;
		}

		vector(size_type n, const value_type &val = value_type(), const allocator_type &alloc = allocator_type()): _size(n), _capacity(0), _allocator(alloc), _ptr(NULL))
		{
			if (DEBUG == 1)
				std::cout << "vector fill constructor called" << std::endl;

			this->_p = this->_allocator.allocate(n);
			size_t i = 0;
			while (i < n)
			{
				this->_allocator.construct(&_ptr[i], val);
				i++;
			}
		}

		template <typename InputIterator>
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator_type &alloc = allocator_type()) : _alloc_type(alloc), _array(NULL), _size(0), _capacity(0)
		{
			size_type n = 0;
			size_type i = 0;
			for (InputIterator it = first; it != last; it++)
				n++;
			reserve(n);
			for (InputIterator it = first; it != last; it++, i++)
				_allocator.construct(&_p[i], *it);
			_size = n;
		}

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

		size_type capacity() const
		{
			if (DEBUG == 1)
			{
				std::cout << "Capacity function called" << std::endl;
				std::cout << "The capacity is now at " << this->_capacity << std::endl;
			}
			return (this->_capacity);
		}

		size_type size() const
		{
			if (DEBUG)
			{
				std::cout << "The size is " << this->_size << std::endl;
			}
			return (this->_size);
		}

		size_t max_size() const
		{
			size_t ret = _allocator.max_size();
			if (DEBUG == 1)
			{
				std::cout << "Max size function called" << std::endl;
				std::cout << "ret is " << ret << std::endl;
			}
			return (ret);
		}

		void resize(size_type n, value_type val = value_type())
		{
			/* */
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
			/* Construction des elements qui seraient supplementaires */
			while (i < n)
			{
				_allocator.construct(&_p[i], val);
				i++;
			}
			/* Deconstruction des elements qui seraient en trop */
			i = n;
			while (i < this->getSize())
			{
				_allocator.destroy(&_p[i]);
				i++;
			}
			this->_size = n;
		}

		bool empty() const
		{
			if (DEBUG == 1)
				std::cout << "empty function called" << std::endl;
			if (size() != 0)
			{
				if (DEBUG == 1)
					std::cout << "empty function will return false" << std::endl;
				return (false);
			}
			if (DEBUG == 1)
				std::cout << "empty function will return true" << std::endl;
			return (true);
		}

		void reserve(size_type n)
		{
			/* */
			try
			{
				if (n > getCapacity())
					realloc(get_fit_capacity(n));
			}
			catch (std::exception &e)
			{
				throw;
			}
			if (n > this->getCapacity())
			{
				pointer_type new = _allocator.allocate(n);
				int i = 0;
				//reconstruction de tous les elements du vecteur
				//destruction des elements de l'ancien vecteur
				while (i < this->getSize())
				{
					_allocator.construct(&new[i], _p[i]);
					_allocator.destroy(&_p[i]);
					i++;
				}
				//desallocation de l'ancien vector
				//_allocator.deallocate(this->_p, this->_capacity = n);
				_allocator.deallocate(this->_p, n);
				this->_p = new;
				this->_capacity = n;
			}
		}

		iterator begin()
		{
			if (DEBUG == 1)
				std::cout << "begin function called" << std::endl;
			if (empty())
				return (end());
			return (iterator(_ptr[0]));
		}

		const_iterator begin() const
		{
			if (DEBUG == 1)
				std::cout << "begin const function called" << std::endl;
			if (empty())
			{
				return (end());
			}
			return (const_iterator(_ptr[0]));
		}

		iterator end()
		{
			if (DEBUG == 1)
				std::cout << "end function called" << std::endl;
			//voir autres techniques
			if (empty())
				return (end());
			return (iterator(_ptr[size()]));
		}

		const_iterator end() const
		{
			if (DEBUG == 1)
				std::cout << "end const function called" << std::endl;

			if (empty())
			{
				return (end());
			}
			return (const_iterator(_ptr[size()]));
		}
		reverse_iterator rbegin()
		{
			if (DEBUG == 1)
				std::cout << "rbegin function called" << std::endl;
			return (reverse_iterator(_ptr[size()]));
		}

		const_reverse_iterator rbegin() const
		{
			if (DEBUG == 1)
				std::cout << "rbegin function called" << std::endl;
			return (const_reverse_iterator(_ptr[size()]));
		}

		reverse_iterator rend()
		{
			if (DEBUG == 1)
				std::cout << "rend fonction called" << std::endl;
			//pour moi il s agit d'un cast en c style - revoir le cast ?
			return (reverse_iterator(_ptr[0]));
		}

		const_reverse_iterator rend() const
		{
			if (DEBUG == 1)
				std::cout << "rend const function called" << std::endl;
			return (rend());
		}

		//TODO: a reprendre
		void push_back(const value_type &src)
		{
			/* */
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

			void assign(size_type count, const T &value)
			{
				//TO DO: revoir realloc
				/* */
				if (n > _capacity)
					realloc(n);
				if (DEBUG == 1)
					std::cout << "Assign function called" << std::endl;
				reserve(n);
				resize(n);
				int i = 0;
				while (i < n && i < this->_size)
				{
					/* Destruction des elements precedents */
					_allocator.destroy(&_p[i]);
					i++;
				}
				i = 0;
				while (i < n)
				{
					_allocator.construct(&_p[i], val);
					i++;
				}
				//Tester la difference
				/* */
				if (n > this->_size)
				{
					this->_size = n;
				}
			}

			template <class InputIt>
			void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
			{
				size_type n = 0;
				size_type i = 0;
				for (InputIterator it = first; it != last; it++)
					n++;
				reserve(n);
				resize(n);
				for (size_type i = 0; i < n && i < _size; i++)
					_alloc_type.destroy(&_p[i]);
				for (InputIterator it = first; it != last; it++, i++)
					_alloc_type.construct(&_p[i], *it);
				//if (n > _size)
				//	_size = n;
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

			void swap(vector & x)
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

		protected:
			void realloc(size_type target)
			{
				pointer new_tab;
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

			void realloc()
			{
				if (this->_capacity == 0)
					realloc(1);
				else
					realloc(this->_capacity * 2);
			}

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
		};

		template <typename T, typename Alloc>
		void swap(vector<T, Alloc> &x, vector<T, Alloc> &y)
		{
			if (DEBUG == 1)
				std::cout << "Swap non member function called" << std::endl;
			x.swap(y);
		};

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
		};

		template <typename T, typename Alloc>
		bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
		{
			if (DEBUG == 1)
				std::cout << "Operator != called" << std::endl;
			bool ret = !(lhs == rhs);
			if (DEBUG == 1)
				std::cout << "Operation != is" << ret << std::endl;
			return (ret);
		};

		template <typename T, typename Alloc>
		bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
		{
			(void)lhs;
			(void)rhs;
			if (DEBUG == 1)
				std::cout << "Operator < called" << std::endl;
			return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
		};

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
		};

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
		};

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
		};
		//}
