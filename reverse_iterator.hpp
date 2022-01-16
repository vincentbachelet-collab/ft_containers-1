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
        reverse_iterator() : _ptr() {}
        reverse_iterator(iterator_type ptr) : _ptr(ptr) {}

        // Attention aux constructeurs
        template <typename iterator>
        reverse_iterator(reverse_iterator<iterator> &src) : _ptr(&(*src)) {}

        iterator_type base(void) const
        {
            return (this->_ptr);
        }

        reverse_iterator &operator=(reverse_iterator const &src)
        {
            _ptr = &(*src);
            return (*this);
        }

        virtual ~reverse_iterator() {}

        reference_type operator*() const
        {
            iterator_type it = this->_ptr;
            it--;
            return it;
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

        reverse_iterator operator+(difference_type n) const
        {
            return (reverse_iterator(this->_ptr - n));
        }

        reverse_iterator operator-(difference_type n) const
        {
            return (reverse_iterator(this->_ptr + n));
        }

        reverse_iterator &operator--()
        {
            this->_ptr--;
            return (*this);
        }

        reverse_iterator &operator-=(difference_type n)
        {
            this->_ptr += n;
            return (*this);
        }

        pointer_type operator->() const
        {
            iterator_type tmp(this->_ptr);
            tmp--;
            return (tmp.operator->());
        }

        reference_type operator[](difference_type n) const
        {
            return (base()[-n - 1]);
        }
    };

    template <class Iterator1, class Iterator2>
    bool operator==(reverse_iterator<Iterator1> &lhs, reverse_iterator<Iterator2> &rhs)
    {
        return (lhs.base() == rhs.base());
    }

    template <class Iterator1, class Iterator2>
    bool operator!=(reverse_iterator<Iterator1> &lhs, reverse_iterator<Iterator2> &rhs)
    {
        return (lhs.base() != rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<(reverse_iterator<Iterator1> &lhs, reverse_iterator<Iterator2> &rhs)
    {
        return (lhs.base() < rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<=(reverse_iterator<Iterator1> &lhs, reverse_iterator<Iterator2> &rhs)
    {
        return (lhs.base() <= rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>(reverse_iterator<Iterator1> &lhs, reverse_iterator<Iterator2> &rhs)
    {
        return (lhs.base() > rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>=(reverse_iterator<Iterator1> &lhs, reverse_iterator<Iterator2> &rhs)
    {
        return (lhs.base() >= rhs.base());
    }

    template <typename Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> &src)
    {
        return (src + n);
    }

    template <typename Iterator>
    reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, reverse_iterator<Iterator> &src)
    {
        return (src - n);
    }
}