#pragma once 

#include "includes.hpp"

namespace ft
{
    template <typename T>
    class vector_iterator
    {
    public:
        typedef T value_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef std::ptrdiff_t difference_type;
        typedef value_type *pointer;
        typedef value_type &reference;

    protected:
        value_type *_p;

    public:
        vector_iterator() : _p(NULL) {}
        vector_iterator(value_type *ptr) : _p(ptr) {}
        vector_iterator(vector_iterator const &src) : _p(src._p) {}
        virtual ~vector_iterator() {}
        operator vector_iterator<value_type const>() const { return vector_iterator<value_type const>(_p); }

        vector_iterator &operator=(const vector_iterator &rhs)
        {
            if (this != &rhs)
                this->_p = rhs._p;
            return (*this);
        }
        
        //Equivalent de "base" pour les reverse iterator
        value_type *get_ptr(void) const
        {
            return this->_p;
        }

        value_type *base(void) const
		{
				return (_p);
		}

        vector_iterator &operator++()
        {
            _p++;
            return (*this);
        }

        vector_iterator operator++(int)
        {
            vector_iterator res = *this;
            ++(*this);
            return (res);
        }

        vector_iterator &operator--()
        {
            _p--;
            return (*this);
        }

        vector_iterator operator--(int)
        {
            vector_iterator it = *this;
            --(*this);
            return it;
        }

        value_type &operator[](int index)
        {
            return *(this->_p + index);
        }

        value_type *operator->()
        {
            return (this->_p);
        }

        //reference operator*() const { return (*_p); }

        bool operator==(const vector_iterator &other) const
        {
            bool b = this->_p == other._p;
            return (b);
        }

        bool operator!=(const vector_iterator &other) const
        {
            bool b = this->_p != other._p;
            return (b);
        }

        bool operator!=(const vector_iterator &other)
        {
            bool b = this->_p != other._p;
            return (b);
        }

        bool
        operator<(const vector_iterator &other) const
        {
            bool b = this->_p < other._p;
            return (b);
        }

        bool operator<=(const vector_iterator &other) const
        {
            bool b = this->_p <= other._p;
            return (b);
        }

        bool operator>(const vector_iterator &other) const
        {
            bool b = this->_p > other._p;
            return (b);
        }

        bool operator>=(const vector_iterator &other) const
        {
            bool b = this->_p >= other._p;
            return (b);
        }

        friend vector_iterator<T> operator+(difference_type n, const vector_iterator &rhs) { return n + rhs._p; }
        friend vector_iterator<T> operator-(difference_type n, const vector_iterator &rhs) { return rhs._p - n; }

        vector_iterator<T> operator+(difference_type n) const 
        { 
            vector_iterator<T> res = this->_p + n;
            return (res);
        }

        vector_iterator<T> operator-(difference_type n) const
        {
            vector_iterator<T> res = this->_p - n;
            return (res);
        }

        difference_type operator-(const vector_iterator &rhs) const
        {
            difference_type res = this->_p - rhs._p;
            return (res);
        }

        difference_type operator+(const vector_iterator &rhs) const
        {
            difference_type res = this->_p + rhs._p;
            return (res);
        }

        vector_iterator<T> &operator+=(difference_type n)
        {
            _p += n;
            return *this;
        }

        vector_iterator<T> &operator-=(difference_type n)
        {
            _p -= n;
            return *this;
        }

        value_type &operator*() { return *_p; }
    };

    template <typename it1, typename it2>
    bool operator==(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() == b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator!=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() != b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator<(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() < b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator<=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() <= b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator>(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() > b.get_ptr();
        return (res);
    }

    template <typename it1, typename it2>
    bool operator>=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() >= b.get_ptr();
        return (res);
    }
}

#include "utils.hpp"
#include "vector_iterator.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator iterator_type;
        typedef typename iterator_traits<iterator_type>::value_type value_type;
        typedef typename iterator_traits<iterator_type>::pointer pointer_type;
        typedef typename iterator_traits<iterator_type>::reference reference_type;
        typedef typename iterator_traits<iterator_type>::difference_type difference_type;
        typedef typename iterator_traits<iterator_type>::iterator_category iter_category;

    protected:
        iterator_type _ptr;

    public:
        reverse_iterator() : _ptr(NULL) {}
        reverse_iterator(iterator_type ptr) : _ptr(ptr) {}

        // Constructeur par copie, necessite de templeter pour que ca fonctionne avec n'importe quel type
        template <typename iter>
        reverse_iterator(const reverse_iterator<iter> &src) : _ptr(src.base()) {}

        virtual ~reverse_iterator() {}
        reverse_iterator &operator=(reverse_iterator const &src)
        {
            this->_ptr = src._ptr;
            return (*(this));
        }

        // https://en.cppreference.com/w/cpp/iterator/reverse_iterator/base
        // Returns the underlying iterator
        iterator_type base(void) const
        {
            return (this->_ptr);
        }

        reference_type operator*() const
        {
            iterator_type it = this->_ptr;
            it--;
            return *it;
        }

        // Pre increment by one
        reverse_iterator &operator++()
        {
            this->_ptr--;
            return (*this);
        }

        // Post decrement by one
        reverse_iterator operator++(int)
        {
            reverse_iterator it = *this;
            this->_ptr--;
            return it;
        }

        // Pre decrement
        reverse_iterator &operator--()
        {
            this->_ptr++;
            return (*this);
        }

        // Post decrement
        reverse_iterator operator--(int)
        {
            reverse_iterator it = *this;
            this->_ptr++;
            return it;
        }

        reverse_iterator &operator-=(difference_type n)
        {
            this->_ptr += n;
            return *this;
        }

        // Arrow operator
        pointer_type operator->() const
        {
            return (&(operator*()));
        }

        // Array index operator[]
        reference_type operator[](difference_type n) const
        {
            return (*(this->_ptr - n - 1));
        }

        // Member overloading
        bool operator==(const reverse_iterator &other) const 
        {
          //  std::cout << "Calling member overload" << std::endl;
            return this->_ptr == other._ptr;
        }

        bool operator!=(const reverse_iterator &other) const { return this->_ptr != other._ptr; }
        bool operator<(const reverse_iterator &other) const { return this->_ptr > other._ptr; }
        bool operator<=(const reverse_iterator &other) const { return this->_ptr >= other._ptr; }
        bool operator>(const reverse_iterator &other) const { return this->_ptr < other._ptr; }
        bool operator>=(const reverse_iterator &other) const { return this->_ptr <= other._ptr; }

        reverse_iterator<Iterator> &operator+=(difference_type n)
        {
            this->_ptr -= n;
            return *this;
        }

        reverse_iterator<Iterator> operator-(difference_type n) const {return this->_ptr + n;}
        difference_type operator-(const reverse_iterator& rhs) const {return rhs._ptr - this->_ptr;}

        reverse_iterator operator+(difference_type n) const
        {
            return (reverse_iterator(this->_ptr - n));
        }
    };

    template <typename Iterator>
	reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> & it)
	{
		return (reverse_iterator<Iterator>(it.base() - n));
	}

    template <typename Iterator>
	reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> & it)
	{
		return (reverse_iterator<Iterator>(it.base() + n));
    }

    // Non member overloading
    template <class Iterator1, class Iterator2>
    bool operator==(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
       // std::cout << "Calling non member overload" << std::endl;
        return (lhs.base() == rhs.base());
    }

    template <class Iterator1, class Iterator2>
    bool operator!=(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<=(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>=(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename Iterator>
    std::ostream &operator<<(std::ostream &o, reverse_iterator<Iterator> &rhs)
    {
        o << *rhs.base();
        return o;
    }
}

//Map iterator
//TODO: a refaire la fin
//#include "map.hpp"

/*
namespace ft
    {
    template<typename T, typename node_pointer>
    class map_iterator
    {
        public:
            typedef T value_type;
            typedef value_type* pointer;
            typedef value_type& reference;
            typedef std::ptrdiff_t difference_type;
            typedef std::bidirectional_iterator_tag iterator_category;

        protected:
            node_pointer _node;

        public:
            map_iterator() : _node(NULL) {}
            map_iterator(node_pointer ptr) : _node(ptr) {}
            map_iterator(map_iterator const & src) : _node(src._node) {}
            map_iterator & operator=(map_iterator const & rhs) {_node = rhs._node; return *this;}
            virtual ~map_iterator() {}

            map_iterator& operator++ (void) {increase(); return *this;}
            map_iterator operator++ (int) {map_iterator it = *this; ++(*this); return it;}
            map_iterator& operator-- (void) {decrease(); return *this;}
            map_iterator operator-- (int) {map_iterator it = *this; --(*this); return it;}

            reference operator*() const {return _node->value;}
            pointer operator->() const {return &(operator*());}
            node_pointer get_node() {return _node;}
            node_pointer get_node() const {return _node;}
            operator map_iterator<const T, node_pointer>() const {return map_iterator<const T, node_pointer>(_node);}

            template<typename it2>
            bool operator==(const map_iterator<it2, node_pointer>& b) const {return _node == b.get_node();}
            template<typename it2>
            bool operator!=(const map_iterator<it2, node_pointer>& b) const {return _node != b.get_node();}

        private:
            void increase() {
                if (_node->right) {
                    _node = _node->right;
                    while (_node->left)
                        _node = _node->left;
                }
                else {
                    node_pointer temp = _node;
                    _node = _node->parent;
                    while (_node->left != temp) {
                        temp = _node;
                        _node = _node->parent;
                    }
                }
            }

            void decrease()
            {
                if (_node->left)
                {
                    _node = _node->left;
                    while (_node->right)
                        _node = _node->right;
                }
                else {
                    node_pointer temp = _node;
                    _node = _node->parent;
                    while (_node->right != temp) {
                        temp = _node;
                        _node = _node->parent;
                    }
                }
            }
        };
}
*/