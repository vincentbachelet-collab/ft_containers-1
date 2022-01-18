#pragma once

#include "includes.hpp"

/*
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
*/