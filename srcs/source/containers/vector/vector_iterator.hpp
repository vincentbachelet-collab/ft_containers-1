#pragma once

//TODO: revoir l include

namespace ft
{
    template <typename T>
    class vector_iterator
    {
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;
        typedef vector_iterator iterator;
        typedef vector_iterator<const T> const_iterator;

    protected:
        value_type *_p;

    public:
        vector_iterator() : _p(NULL)
        {
            if (DEBUG == 1)
                std::cout << "vector iterator default constructor called" << std::endl;
        }
        vector_iterator(value_type &x) : _p(&x)
        {
            if (DEBUG == 1)
            {
                std::cout << "vector iterator reference value_typed constructor called" << std::endl;
                std::cout << "value type is " << x << std::endl;
            }
        }

        vector_iterator(value_type *x) : _p(x)
        {
            if (DEBUG == 1)
            {
                std::cout << "vector iterator pointer value_typed constructor called" << std::endl;
                std::cout << "value type is " << x << std::endl;
            }
        }

        vector_iterator(const iterator &x)
        {
            if (DEBUG == 1)
                std::cout << "copy constructor called" << std::endl;
            _p = x._p;
            return (*this);
        }
        virtual ~vector_iterator(void)
        {
            if (DEBUG == 1)
                std::cout << "vector iterator destructor called" << std::endl;
        }

        vector_iterator &operator=(vector_iterator const &rhs)
        {
            if (DEBUG == 1)
                std::cout << "assignation operator called" << std::endl;
            _p = rhs._p;
            return (*this);
        }

        value_type *get_ptr(void) const
        {
            if (DEBUG == 1)
                std::cout << "vector iterator get ptr function called" << std::endl;
            return (this->_p);
        }

        operator vector_iterator<value_type const>(void) const
        {
            return (vector_iterator<value_type const>(_p));
        }

        vector_iterator &operator++()
        {
            if (DEBUG == 1)
                std::cout << "vector iterator post incrementation operator called" << std::endl;
            this->_p++;
            return (*this);
        }

        vector_iterator operator++(int)
        {
            if (DEBUG == 1)
                std::cout << "vector iterator pre incrementation operator called" << std::endl;
            vector_iterator it = *this;
            (this->p)++;
            return (it);
        }

        vector_iterator &operator--()
        {
            if (DEBUG == 1)
                std::cout << "vector iterator post decrementation operator called" << std::endl;
            this->_p--;
            return (*this);
        }

        vector_iterator operator--(int)
        {
            if (DEBUG == 1)
                std::cout << "vector iterator pre decrementation operator called" << std::endl;
            vector_iterator it = *this;
            (*this)--;
            return it;
        }

        value_type &operator[](int index)
        {
            return *(this->_p + index);
        }

        value_type *operator->()
        {
            value_type *p = get_ptr();
            if (DEBUG == 1)
            {
                std::cout << "operator -> called" << std::endl;
                std::cout << "the value_type * is " << p << "and the value is " << *p << std::endl;
            }
            return (p);
        }

        value_type &operator*()
        {
            value_type v = *this->p;
            if (DEBUG == 1)
            {
                std::cout << "operator * called" << std::endl;
                std::cout << "the value_type is " << v << std::endl;
            }
            return (v);
        }

        bool operator==(const vector_iterator &other) const
        {
            bool b = this->_p == other._p;
            if (DEBUG == 1)
            {
                std::cout << "operator == called" << std::endl;
                std::cout << "the result is " << b << std::endl;
            }
            return (b);
        }

        bool operator!=(const vector_iterator &other) const
        {
            bool b = this->_p != other._p;
            if (DEBUG == 1)
            {
                std::cout << "operator != called" << std::endl;
                std::cout << "the result is " << b << std::endl;
            }
            return (b);
        }

        bool operator<(const vector_iterator &other) const
        {
            bool b = this->_p < other._p;
            if (DEBUG == 1)
            {
                std::cout << "operator < called" << std::endl;
                std::cout << "the result is " << b << std::endl;
            }
            return (b);
        }

        bool operator<=(const vector_iterator &other) const
        {
            bool b = this->_p <= other._p;
            if (DEBUG == 1)
            {
                std::cout << "operator < called" << std::endl;
                std::cout << "the result is " << b << std::endl;
            }
            return (b);
        }

        bool operator>(const vector_iterator &other) const
        {
            bool b = this->_p > other._p;
            if (DEBUG == 1)
            {
                std::cout << "operator > called" << std::endl;
                std::cout << "the result is " << b << std::endl;
            }
            return (b);
        }

        bool operator>=(const vector_iterator &other) const
        {
            bool b = this->_p >= other._p;
            if (DEBUG == 1)
            {
                std::cout << "operator >= called" << std::endl;
                std::cout << "the result is " << b << std::endl;
            }
            return (b);
        }

        //TODO: a verifier
        vector_iterator<T> operator+(difference_type n, const vector_iterator &rhs)
        {
            return (n + rhs._p);
        }

        vector_iterator<T> operator+(difference_type n) const
        {
            vector_iterator<T> res = this->_p + n;
            if (DEBUG == 1)
            {
                std::cout << "operator + called (difference type parameter)" << std::endl;
                std::cout << "the result is " << res << std::endl;
            }
            return (res);
        }

        vector_iterator<T> operator-(difference_type n) const
        {
            vector_iterator<T> res = this->_p - n;
            if (DEBUG == 1)
            {
                std::cout << "operator - called (difference type parameter)" << std::endl;
                std::cout << "the result is " << res << std::endl;
            }
            return (res);
        }

        difference_type operator-(const vector_iterator &rhs) const
        {
            difference_type res = this->_p - rhs._p;
            if (DEBUG == 1)
            {
                std::cout << "operator - called (vector iterator reference)" << std::endl;
                std::cout << "the result is " << res << std::endl;
            }
            return (res);
        }

        vector_iterator<T> operator+=(difference_type n) const
        {
            vector_iterator<T> res = this->_p += n;
            if (DEBUG == 1)
            {
                std::cout << "operator += called" << std::endl;
                std::cout << "the result is " << res << std::endl;
            }
            return (this->_p += n);
        }

        vector_iterator<T> operator-=(difference_type n) const
        {
            vector_iterator<T> res = this->_p -= n;
            if (DEBUG == 1)
            {
                std::cout << "operator -= called" << std::endl;
                std::cout << "the result is " << res << std::endl;
            }
            return (res);
        }
    };

    template <typename it1, typename it2>
    bool operator==(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() == b.get_ptr();
        if (DEBUG == 1)
        {
            std::cout << "non member operator == called" << std::endl;
            std::cout << "the result is " << res << std::endl;
        }
        return (res);
    }

    template <typename it1, typename it2>
    bool operator!=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() != b.get_ptr();
        if (DEBUG == 1)
        {
            std::cout << "non member operator != called" << std::endl;
            std::cout << "the result is " << res << std::endl;
        }
        return (res);
    }

    template <typename it1, typename it2>
    bool operator<(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() < b.get_ptr();
        if (DEBUG == 1)
        {
            std::cout << "non member operator < called" << std::endl;
            std::cout << "the result is " << res << std::endl;
        }
        return (res);
    }

    template <typename it1, typename it2>
    bool operator<=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() <= b.get_ptr();
        if (DEBUG == 1)
        {
            std::cout << "non member operator <= called" << std::endl;
            std::cout << "the result is " << res << std::endl;
        }
        return (res);
    }

    template <typename it1, typename it2>
    bool operator>(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() > b.get_ptr();
        if (DEBUG == 1)
        {
            std::cout << "non member operator > called" << std::endl;
            std::cout << "the result is " << res << std::endl;
        }
        return (a.get_ptr() > b.get_ptr());
    }

    template <typename it1, typename it2>
    bool operator>=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() >= b.get_ptr();
        if (DEBUG == 1)
        {
            std::cout << "non member operator >= called" << std::endl;
            std::cout << "the result is " << res << std::endl;
        }
        return (res);
    }
}
