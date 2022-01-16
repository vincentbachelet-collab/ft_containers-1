#pragma once

#include <memory>
#include <iostream>
#include <string>
#include "utils.hpp"
#include "vector_iterator.hpp"

namespace ft
{
    template <class Iterator>
    class reverse_iterator
    {
    public:
        typedef Iterator iterator_type;

        // typedef typename iterator_traits<iterator_type>::iterator_category iterator_category;
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

        // Attention aux constructeurs
        template <typename iterator>
        // TODO: a revoir base

        iterator_type base(void) const
        {
            return _ptr;
        }

        // TODO: a revoir
        operator reverse_iterator<vector_iterator<value_type const> >() const { return reverse_iterator<vector_iterator<value_type const> >(_ptr); }
        operator reverse_iterator<vector_iterator<value_type> >() { return reverse_iterator<vector_iterator<value_type> >(_ptr); }

        reverse_iterator(const reverse_iterator<iterator_type> &src) : _ptr(src.base())
        {
        }

        iterator_type base(void) const
        {
            return (this->_ptr);
        }

        reverse_iterator &operator=(reverse_iterator const &src)
        {
            _ptr = src._ptr;
            return (*this);
        }

        virtual ~reverse_iterator() {}

        reference_type operator*() const
        {
            iterator_type it = this->_ptr;
            it--;
            return *it;
        }

        reference_type operator*()
        {
            iterator_type it = this->_ptr;
            return (*--it);
        }

        reverse_iterator &operator++()
        {
            this->_ptr--;
            return (*this);
        }

        reverse_iterator operator++(int)
        {
            reverse_iterator it = *this;
            this->_ptr--;
            return (it);
        }

        // TODO: voir si besoin ?
        /*reverse_iterator operator+(difference_type n) const
        {
            return (reverse_iterator(this->_ptr - n));
        }

        reverse_iterator operator-(difference_type n) const
        {
            return (reverse_iterator(this->_ptr + n));
        }
        */

        reverse_iterator &operator--()
        {
            this->_ptr--;
            return (*this);
        }

        reverse_iterator operator--(int)
        {
            reverse_iterator it = *this;
            _ptr++;
            return it;
        }

        reverse_iterator &operator-=(difference_type n)
        {
            this->_ptr += n;
            return (*this);
        }

        pointer_type operator->() const
        {
            /*
            iterator_type tmp(this->_ptr);
            tmp--;
            return (tmp.operator->());
            */
            return &(operator*());
        }

        reference_type
        operator[](difference_type n) const
        {
            (void)n;
            // return (base()[-n - 1]);
            return *(_ptr - n - 1);
        }

        // TODO: a changer
        reverse_iterator<Iterator> &operator+=(difference_type n)
        {
            _ptr -= n;
            return *this;
        }

        // TODO: verifier si tous les operators sont bien implantes
        bool operator==(const reverse_iterator &other) const { return _ptr == other._ptr; }
        bool operator!=(const reverse_iterator &other) const { return _ptr != other._ptr; }
        bool operator<(const reverse_iterator &other) const { return _ptr > other._ptr; }
        bool operator<=(const reverse_iterator &other) const { return _ptr >= other._ptr; }
        bool operator>(const reverse_iterator &other) const { return _ptr < other._ptr; }
        bool operator>=(const reverse_iterator &other) const { return _ptr <= other._ptr; }

        // reverse_iterator<Iterator> operator-(difference_type n) const { return _ptr + n; }       // a - n
        // difference_type operator-(const reverse_iterator &rhs) const { return rhs._ptr - _ptr; } // a - b

        // TODO: revoir cette derniere ?
        //  friend reverse_iterator<Iterator> operator+(difference_type n, const reverse_iterator &rhs) { return rhs._pointer - n; } // n + a
        reverse_iterator<Iterator> operator+(difference_type n) const { return _ptr - n; }       // a + n
        reverse_iterator<Iterator> operator-(difference_type n) const { return _ptr + n; }       // a - n
        difference_type operator-(const reverse_iterator &rhs) const { return rhs._ptr - _ptr; } // a - b
        reverse_iterator<Iterator> &operator+=(difference_type n)
        {
            _ptr -= n;
            return *this;
        }
        reverse_iterator<Iterator> &operator-=(difference_type n)
        {
            _ptr += n;
            return *this;
        }
    };

    // TODO: refaire de tests pour tester ce qui est dans la classe et pas dans la classe
    template <class Iterator1, class Iterator2>
    bool operator==(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
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
        return (lhs.base() < rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<=(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>=(reverse_iterator<Iterator1> const &lhs, reverse_iterator<Iterator2> const &rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> const &src)
    {
        return (src + n);
    }

    template <typename Iterator>
    reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> const &src)
    {
        return (src - n);
    }
}