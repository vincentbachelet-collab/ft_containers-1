#pragma once

#include "includes.hpp"

namespace ft
{
    template <typename T>
    class vector_iterator
    {
    public:
        typedef T value_type;
        typedef long int difference_type;
        typedef size_t size_type;
        typedef std::random_access_iterator_tag iterator_category;
        typedef value_type *pointer;
        typedef value_type &reference;
        typedef T *ptr;

    protected:
        value_type *_p;

    public:
        //TODO: a revoir (toutes), tester, decrire
        vector_iterator(ptr p = 0) : _p(p) {}
        //vector_iterator(value_type *x) : _p(x) {}
        vector_iterator(vector_iterator const &src) : _p(src._p) {}
        virtual ~vector_iterator() {}

        vector_iterator &operator=(const vector_iterator &rhs)
        {
            if (this != &rhs)
                this->_p = rhs._p;
            return (*this);
        }
        value_type *get_ptr(void) const
        {
            return this->_p;
        }

        vector_iterator &operator++()
        {
            this->_p++;
            return (*this);
        }

        vector_iterator operator++(int)
        {
            vector_iterator res(*this);
            ++(*this);
            return (res);
        }

        vector_iterator &operator--()
        {
            vector_iterator res(*this);
            --(*this);
            return (res);
        }

        vector_iterator operator--(int)
        {
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
            --_p;
            return (*this);
        }

        reference operator*() const { return (*_p); }

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

        vector_iterator<T> operator+(difference_type n) const
        {
            vector_iterator<T> res = this->_p + n;
            return (res);
        }

        vector_iterator<T>
        operator-(difference_type n) const
        {
            vector_iterator<T> res = this->_p - n;
            return (res);
        }

        difference_type operator-(const vector_iterator &rhs) const
        {
            difference_type res = this->_p - rhs._p;
            return (res);
        }

        vector_iterator<T> operator+=(difference_type n) const
        {
            vector_iterator<T> res = this->_p += n;
            return (this->_p += n);
        }

        vector_iterator<T> operator-=(difference_type n) const
        {
            vector_iterator<T> res = this->_p -= n;
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