#pragma once

#include <memory>
#include <iostream>
#include <string>
#include "iterator.hpp"

struct enable_if;
class vector_iterator;

namespace ft
{
	template <typename T, typename Alloc = std::allocator<T> >
	class vector
	{
	public:
		typedef T value;
		typedef Alloc allocator;
		typedef long int difference;
		typedef typename allocator::reference reference;
		typedef typename allocator::const_reference const_reference;
		typedef typename allocator::size_type size_type;
		typedef typename allocator::pointer pointer;
		typedef typename allocator::const_pointer const_pointer;
		typedef vector_iterator<value> iterator;
		typedef vector_iterator<value const> const_iterator;
		typedef ft::reverse_iterator<iterator> reverse_iterator;
		typedef ft::reverse_iterator<const_iterator> const_reverse_iterator;

	private:
		size_type _size;	  // taille du vecteur
		size_type _capacity;  // taille en termes de capacite/memoire
		allocator _allocator; // type de l'allocateur du container (peut etre custom)
		pointer _ptr;		  // Addresse du tableau

	public:
		// Getters, setters
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

		allocator get_allocator(void) const
		{
			return (this->_allocator);
		}

		void construct_allocator(pointer ptr, const value val)
		{
			this->_allocator.construct(ptr, val);
		}

		void alloc_vec(size_type len)
		{
			set_ptr(get_allocator().allocate(len));
		}

		// https://en.cppreference.com/w/cpp/container/vector/vector
		// Constructeur par defaut / default constructor
		vector(const allocator &alloc = allocator()) : _size(0), _capacity(0), _allocator(alloc), _ptr(NULL) {}

		// Iterateur (necessaires pour tester les autres constructeurs notamment)
		iterator begin()
		{
			return (iterator(this->_ptr));
		}

		const_iterator begin() const
		{
			return (const_iterator(this->_ptr));
		}

		iterator end()
		{
			return (iterator(this->_ptr + this->_size));
		}

		const_iterator end() const
		{
			return const_iterator(this->_ptr + this->_size);
		}

		reverse_iterator rbegin()
		{
			return (reverse_iterator(end()));
		}

		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(end()));
		}

		reverse_iterator rend()
		{
			return reverse_iterator(begin());
		}

		const_reverse_iterator rend() const
		{
			return const_reverse_iterator(begin());
		}

		void clear(void)
		{
			this->_size = 0;
		}

		// https://www.cplusplus.com/reference/vector/vector/reserve/
		// Requests that the vector capacity be at least enough to contain n elements.
		void reserve(size_type size)
		{
			if (size > this->get_capacity())
			{
				//As requested, allocate in one call
				pointer n = this->_allocator.allocate(size);
				int i = 0;
				int max = this->get_size();
				while (i < max)
				{
					this->_allocator.construct(&n[i], this->_ptr[i]);
					this->_allocator.destroy(&_ptr[i]);
					i++;
				}
				this->_allocator.deallocate(this->_ptr, this->_capacity);
				set_ptr(n);
				set_capacity(size);
			}
		}

		bool empty() const
		{
			if (this->size() != 0)
				return (false);
			return (true);
		}

		size_type size() const
		{
			return (this->_size);
		}

		// Constructeur deprecie depuis C++11 / fill constructeur
		vector(size_type n, const value &val = value(), const allocator &alloc = allocator()) : _size(n), _capacity(n), _allocator(alloc), _ptr(NULL)
		{
			alloc_vec(n);
			size_t i = 0;
			while (i < n)
			{
				construct_allocator(&_ptr[i], val);
				i++;
			}
		}

		// range constructeur ()
		// Le enable if est necessaire sinon la fonction construct ne pourra pas compiler
		// Dans le enable if, si la premiere partie avant la virgule est fausse, la deuxieme partie sera ignoree
		// Is integral represente grosso modo les data types qu on connait depuis le c
		template <class InputIterator>
		vector(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last, const allocator &alloc = allocator()) : _size(0), _capacity(0), _allocator(alloc), _ptr(NULL)
		{
			InputIterator tmp(first);
			while (tmp++ != last)
				this->_size++;

			this->set_capacity(this->get_size());
			//As requested, allocated in one call
			this->_ptr = _allocator.allocate(this->get_size()); //get_capacity()

			for (int i = 0; first != last; ++first, ++i)
				_allocator.construct(&this->_ptr[i], *first);
		}

		// Copy constructor (4)
		vector(const vector &src) : _size(src._size), _capacity(src._capacity), _allocator(src._allocator), _ptr(NULL)
		{
			this->_ptr = _allocator.allocate(this->_capacity);
			size_type i = 0;
			while (i < this->get_size())
			{
				_allocator.construct(&_ptr[i], src._ptr[i]);
				i++;
			}
			return;
		}

		// destructeur
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

		size_type max_size() const
		{
			size_type ret = this->_allocator.max_size();
			return (ret);
		}

		//Equivalent de mon get capacity
		size_type capacity() const
		{
			return (this->_capacity);
		}

		void resize(size_type n, value val = value())
		{
			if (n > this->get_capacity())
			{
				if (n < this->get_capacity() * 2)
					reserve(this->get_capacity() * 2);
				else
					reserve(n);
			}
			size_type i = this->get_size();
			while (i < n)
			{
				this->_allocator.construct(&_ptr[i], val);
				i++;
			}
			i = n;
			while (i < this->get_size())
			{
				_allocator.destroy(&_ptr[i]);
				i++;
			}
			this->set_size(n);
		}

		// Assign : fill version
		//Assigns new contents to the vector, replacing its current contents, and modifying its size accordingly.
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

		// Assign range version
		template <class InputIterator>
		void assign(typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			size_type n = 0;
			size_type i = 0;
			InputIterator it = first;
			while (it != last)
			{
				n++;
				it++;
			}
			reserve(n);
			resize(n);
			i = 0;
			while (i < n && i < this->size())
			{
				this->_allocator.destroy(&_ptr[i]);
				i++;
			}
			it = first;
			i = 0;
			while (it != last)
			{
				this->_allocator.construct(&_ptr[i], *it);
				it++;
				i++;
			}
			if (n > this->get_size())
				set_size(n);
		}

		// retourne une reference de l element a la position n dans le vecteur
		reference at(size_type n)
		{
			if (n >= this->get_size())
				throw std::out_of_range("out of range");
			reference ref = this->_ptr[n];
			return (ref);
		}

		// retourne une reference de l element a la position n dans le vecteurs
		const_reference at(size_type n) const
		{
			if (n >= this->get_size())
				throw std::out_of_range("out of range");
			const_reference ref = this->_ptr[n];
			return (ref);
		}

		void push_back(const value &val)
		{
			size_type size = this->get_size();
			if (size == this->get_capacity())
			{
				if (this->get_capacity() == 0)
					this->reserve(1);
				else
					this->reserve(this->get_capacity() * 2);
			}
			this->_allocator.construct(&_ptr[size], val);
			this->_size++;
		}

		// Le compilateur appelle ca un subscript operator
		reference operator[](size_type n)
		{
			reference ref = this->_ptr[n];
			return (ref);
		}

		const_reference operator[](size_type n) const
		{
			const_reference ref = this->_ptr[n];
			return (ref);
		}

		// deux versions de erase
		iterator erase(iterator position)
		{
			return erase(position, position + 1);
		}

		// Removes from the vector either a single element (position) or a range of elements ([first,last)).
		iterator erase(iterator first, iterator last)
		{
			if (first == this->end() || first == last)
				return first;

			size_type begin = 0;
			size_type first_to_last = 0;
			size_type last_to_end = 0;
			size_type i = 0;

			iterator it = this->begin();
			//count begin
			while (it != first)
			{
				begin++;
				it++;
			}
			it = first;
			while (it != last)
			{
				first_to_last++;
				it++;
			}
			//count last to end
			it = last;
			while (it != this->end())
			{
				last_to_end++;
				it++;
			}
			//Va permettre de ne pas perdre les premiers qui ne seraient pas a supprimer
			while (i < last_to_end)
			{
				_allocator.destroy(&_ptr[begin + i]);
				_allocator.construct(&_ptr[begin + i], _ptr[begin + i + first_to_last]);
				i++;
			}
			///on detruit tout ce qu il y a entre first et last
			while (i < first_to_last)
			{
				_allocator.destroy(&_ptr[begin + last_to_end + i]);
				i++;
			}
			this->_size -= first_to_last;
			return (first);
		}

		iterator insert(iterator position, const value &val)
		{
			difference diff = position.get_ptr() - this->_ptr;
			insert(position, 1, val);
			return iterator(begin() + diff);
		}

		void insert(iterator position, size_type n, const value &val)
		{
			size_type begin_to_pos = 0;
			size_type pos_to_end = 0;
			size_type i = 0;
			iterator it = begin();
			while (it != position)
			{
				begin_to_pos++;
				it++;
			}
			while (it != this->end())
			{
				pos_to_end++;
				it++;
			}
			if (this->_size + n > this->_capacity)
			{
				if (this->_size + n < this->_capacity * 2)
					reserve(this->_capacity * 2);
				else
					reserve(this->_size + n);
			}
			while (i < pos_to_end)
			{
				this->_allocator.construct(&_ptr[begin_to_pos + n + pos_to_end - i - 1], _ptr[begin_to_pos + pos_to_end - i - 1]);
				this->_allocator.destroy(&_ptr[begin_to_pos + pos_to_end - i - 1]);
				i++;
			}
			i = 0;
			while (i < n)
			{
				this->_allocator.construct(&_ptr[begin_to_pos + i], val);
				i++;
			}
			this->set_size(this->get_size() + n);
		}

		template <class InputIterator>
		void insert(iterator position, typename ft::enable_if<!ft::is_integral<InputIterator>::value, InputIterator>::type first, InputIterator last)
		{
			size_type n = 0;
			size_type begin_to_pos = 0;
			size_type pos_to_end = 0;
			InputIterator Init = first;

			while (Init != last)
			{
				Init++;
				n++;
			}
			iterator it = this->begin();
			while (it != position)
			{
				begin_to_pos++;
				it++;
			}
			while (it != this->end())
			{
				pos_to_end++;
				it++;
			}
			if (this->_size + n > this->_capacity)
			{
				if (this->_size + n < this->_capacity * 2)
					reserve(this->_capacity * 2);
				else
					reserve(this->_size + n);
			}
			size_type i = 0;
			while (i < pos_to_end)
			{
				this->_allocator.construct(&_ptr[begin_to_pos + n + pos_to_end - i - 1], _ptr[begin_to_pos + pos_to_end - i - 1]);
				this->_allocator.destroy(&_ptr[begin_to_pos + pos_to_end - i - 1]);
				i++;
			}
			Init = first;
			i = 0;
			while (i < n)
			{
				this->_allocator.construct(&_ptr[begin_to_pos + i], *Init);
				Init++;
				i++;
			}
			this->set_size(this->get_size() + n);
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
			if (x == *this)
				return;

			pointer save_start = x._ptr;
			size_type save_end = x._size;
			size_type save_end_capacity = x._capacity;
			allocator save_allocator = x._allocator;

			x._ptr = this->_ptr;
			x._size = this->_size;
			x._capacity = this->_capacity;
			x._allocator = this->_allocator;

			this->_ptr = save_start;
			this->_size = save_end;
			this->_capacity = save_end_capacity;
			this->_allocator = save_allocator;
		}

		// fonction iterateur
		reference front()
		{
			reference ref = *(this->get_ptr());
			return (ref);
		}

		const_reference front() const
		{
			const_reference ref = *(this->get_ptr());
			return (ref);
		}

		vector &operator=(const vector &x)
		{
			if (this != &x)
			{
				if (this->_size < x._size)
				{
					reserve(x._size);
					resize(x._size);
				}
				else
					for (size_type i = 0; i < _size; i++)
						_allocator.destroy(&_ptr[i]);
				this->_size = x._size;
				size_type i = 0;
				while (i < this->get_size())
				{
					_allocator.construct(&_ptr[i], x._ptr[i]);
					i++;
				}
			}
			return (*(this));
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
			return (false);
		size_t i = 0;
		while (i < lhs.size())
		{
			if (lhs[i] != rhs[i])
				return (false);
			i++;
		}
		return (true);
	}

	template <typename T, typename Alloc>
	bool operator!=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		bool ret = !(lhs == rhs);
		return (ret);
	}

	template <typename T, typename Alloc>
	bool operator<(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	template <class T, class Alloc>
	bool operator<=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		bool ret1 = lhs < rhs;
		bool ret2 = lhs == rhs;
		return (ret1 || ret2);
	}

	template <class T, class Alloc>
	bool operator>(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		bool ret = rhs < lhs;
		return (ret);
	}

	template <class T, class Alloc>
	bool operator>=(const vector<T, Alloc> &lhs, const vector<T, Alloc> &rhs)
	{
		bool ret1 = lhs > rhs;
		bool ret2 = lhs == rhs;
		return (ret1 || ret2);
	}
}