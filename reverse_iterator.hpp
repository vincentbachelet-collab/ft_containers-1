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
        bool operator==(const reverse_iterator &other) const { return this->_ptr == other._ptr; }
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

        //friend reverse_iterator<Iterator> operator+(difference_type n, reverse_iterator const &rhs) {return rhs.base() - n;}
       // friend reverse_iterator<Iterator> operator-(difference_type n, reverse_iterator const &rhs) {return rhs.base() + n;}
    };

    /* */
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

    /*
    template <typename T>
    reverse_iterator<T> &operator+(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &it) { return it + n; }
    template <typename T>
    reverse_iterator<T> &operator-(typename reverse_iterator<T>::difference_type n, const reverse_iterator<T> &it) { return it - n; }
    */
    template <typename Iterator>
    std::ostream &operator<<(std::ostream &o, reverse_iterator<Iterator> &rhs)
        {
            o << *rhs._pointer;
            return o;
        }
}