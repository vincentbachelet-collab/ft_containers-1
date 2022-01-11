#pragma once

#include "includes.hpp"

namespace ft
{
    template <typename T>
    class vector_iterator
    {
    public:
        typedef T value_type;
        typedef std::ptrdiff_t difference_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef value_type *pointer;
        typedef value_type &reference;

    protected:
        value_type *_p;

    public:
        //TODO: a revoir (toutes), tester, decrire
        vector_iterator() : _p(NULL) {}
        //vector_iterator(value_type &x) : _p(&x) {}
        vector_iterator(value_type *x) : _p(x) {}
        vector_iterator(vector_iterator const &src) : _p(src._p) {}
        vector_iterator &operator=(vector_iterator const &rhs)
        {
            _p = rhs._p;
            return *this;
        }
        value_type *get_ptr(void) const
        {
            return this->_p;
        }
        virtual ~vector_iterator() {}
        operator vector_iterator<value_type const>() const
        {
            return vector_iterator<value_type const>(this->_p);
        }

        vector_iterator &operator++()
        {
#if DEBUG == 1
            std::cout << "vector iterator post incrementation operator called" << std::endl;
#endif
            this->_p++;
            return (*this);
        }

        vector_iterator operator++(int)
        {
#if DEBUG == 1
            std::cout << "vector iterator pre incrementation operator called" << std::endl;
#endif
            vector_iterator it = *this;
            this->_p++;
            return (it);
        }

        vector_iterator &operator--()
        {
#if DEBUG == 1
            std::cout << "vector iterator post decrementation operator called" << std::endl;
#endif
            this->_p--;
            return (*this);
        }

        vector_iterator operator--(int)
        {
#if DEBUG == 1
            std::cout << "vector iterator pre decrementation operator called" << std::endl;
#endif
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
#if DEBUG == 1
            std::cout << "the value_type * is " << p << "and the value is " << *p << std::endl;
#endif
            return (p);
        }

        //TODO: a revoir
        /*
        value_type &operator*()
        {
            value_type v = *this->p;
#if DEBUG == 1
            std::cout << "the value_type is " << v << std::endl;
#endif
            return (v);
        }
        */

        bool operator==(const vector_iterator &other) const
        {
            bool b = this->_p == other._p;
#if DEBUG == 1

            std::cout << "the result is " << b << std::endl;
#endif
            return (b);
        }

        bool operator!=(const vector_iterator &other) const
        {
            bool b = this->_p != other._p;
#if DEBUG == 1
            std::cout << "the result is " << b << std::endl;
#endif
            return (b);
        }

        bool operator!=(const vector_iterator &other)
        {
            bool b = this->_p != other._p;
#if DEBUG == 1
            std::cout << "the result is " << b << std::endl;
#endif
            return (b);
        }

        bool
        operator<(const vector_iterator &other) const
        {
            bool b = this->_p < other._p;
#if DEBUG == 1
            std::cout << "the result is " << b << std::endl;
#endif
            return (b);
        }

        bool operator<=(const vector_iterator &other) const
        {
            bool b = this->_p <= other._p;
#if DEBUG == 1
            std::cout << "the result is " << b << std::endl;
#endif
            return (b);
        }

        bool operator>(const vector_iterator &other) const
        {
            bool b = this->_p > other._p;
#if DEBUG == 1
            std::cout << "the result is " << b << std::endl;
#endif
            return (b);
        }

        bool operator>=(const vector_iterator &other) const
        {
            bool b = this->_p >= other._p;
#if DEBUG == 1
            std::cout << "the result is " << b << std::endl;
#endif
            return (b);
        }

        vector_iterator<T> operator+(difference_type n) const
        {
            vector_iterator<T> res = this->_p + n;
            return (res);
        }

        vector_iterator<T>
        operator-(difference_type n) const
        {
            vector_iterator<T> res = this->_p - n;
#if DEBUG == 1
            std::cout << "the result is " << res << std::endl;
#endif
            return (res);
        }

        difference_type operator-(const vector_iterator &rhs) const
        {
            difference_type res = this->_p - rhs._p;
#if DEBUG == 1
            std::cout << "the result is " << res << std::endl;
#endif
            return (res);
        }

        vector_iterator<T> operator+=(difference_type n) const
        {
            vector_iterator<T> res = this->_p += n;
#if DEBUG == 1
            std::cout << "the result is " << res << std::endl;
#endif
            return (this->_p += n);
        }

        vector_iterator<T> operator-=(difference_type n) const
        {
            vector_iterator<T> res = this->_p -= n;
#if DEBUG == 1
            std::cout << "the result is " << res << std::endl;
#endif
            return (res);
        }

        value_type operator*()
        {
            return (*(this->_p));
        }
    };

    template <typename it1, typename it2>
    bool operator==(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() == b.get_ptr();
#if DEBUG == 1
        std::cout << "the result is " << res << std::endl;
#endif
        return (res);
    }

    template <typename it1, typename it2>
    bool operator!=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() != b.get_ptr();
#if DEBUG == 1
        std::cout << "the result is " << res << std::endl;
#endif
        return (res);
    }

    template <typename it1, typename it2>
    bool operator<(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() < b.get_ptr();
#if DEBUG == 1
        std::cout << "the result is " << res << std::endl;
#endif
        return (res);
    }

    template <typename it1, typename it2>
    bool operator<=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() <= b.get_ptr();
#if DEBUG == 1
        std::cout << "the result is " << res << std::endl;
#endif
        return (res);
    }

    template <typename it1, typename it2>
    bool operator>(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() > b.get_ptr();
#if DEBUG == 1
        std::cout << "the result is " << res << std::endl;
#endif
        return (res);
    }

    template <typename it1, typename it2>
    bool operator>=(const vector_iterator<it1> &a, const vector_iterator<it2> &b)
    {
        bool res = a.get_ptr() >= b.get_ptr();
#if DEBUG == 1
        std::cout << "the result is " << res << std::endl;
#endif
        return (res);
    }
}