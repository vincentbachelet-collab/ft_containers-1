#pragma once

#include "../../../includes/common/includes.hpp"

namespace ft
{
        template <class Iterator>
        class reverse_iterator
        {
        public:
                typedef Iterator iterator_type;

        protected:
                iterator_type _p;
        };
}

/*
//Preserves Iteror's category
typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
//Preserves iterator's value type
typedef typename iterator_traits<Iterator>::value_type value_type;
//Preserves Iterator's pointer type
typedef typename iterator_traits<Iterator>::difference_type difference_type;
//Preserves Iterator's difference type
typedef typename iterator_traits<Iterator>::pointer pointer;
//Preserves iterator's reference type
typedef typename iterator_traits<Iterator>::reference reference;

        //TODO: a reprendre
        reverse_iterator() : _p(NULL)
        {
#if DEBUG == 1
            std::cout << "reverse iterator default constructor called" << std::endl;
#endif
        }

        reverse_iterator(iterator_type ptr) : _p(ptr)
        {
#if DEBUG == 1
            std::cout << "reverse iterator ptr constructor called" << std::endl;
#endif
        }

        template <typename iter>
        reverse_iterator(const reverse_iterator<iter> &src) _p(src.base())
        {
#if DEBUG == 1
            std::cout << "reverse iterator base constructor called" << std::endl;
#endif
        }

        iterator_type base(void) const
        {
#if DEBUG == 1
            std::cout << "reverse iterator base function called" << std::endl;
#endif
            return (this->_p);
        }

        reverse_iterator &operator=(reverse_iterator<type> &src)
        {
#if DEBUG == 1
            std::cout << "asssignation operator function called" << std::endl;
#endif
            this->_p = src._p;
            return (*this);
        }

        virtual ~reverse_iterator()
        {
#if DEBUG == 1
            std::cout << "reverse iterator destructor called" << std::endl;
#endif
        }

        operator reverse_iterator<vector_iterator<value_type const>() const
        {
#if DEBUG == 1
            std::cout << "reverse iterator operator" << std::endl;
#endif
            return (reverse_iterator<vector_iterator<value_type const>(_p);
        }

        operator reverse_iterator<vector_iterator<value_type>()
        {
#if DEBUG == 1
            std::cout << "reverse iterator operator" << std::endl;
#endif
            return (reverse_iterator<vector_iterator<value_type>(_p);
        }
        reference operator*() const
        {
            iterator_type it = this->_p;
            it--;
            return it;
        }

        reference operator*()
        {
            iterator_type it = this->_p;
            it--;
            return it;
        }

        reverse_iterator &operator++()
        {
#if DEBUG == 1
            std::cout << "post incrementation reverse_iterator called" << std::endl;
#endif
            this->_p--;
            return (*this);
        }

        reverse_iterator operator++(int)
        {
#if DEBUG == 1
            std::cout << "pre incrementation reverse_iterator called" << std::endl;
#endif
            reverse_iterator it = *this;
            this->_p--;
            return (it);
        }

        reverse_iterator operator+(difference_type n) const
        {
#if DEBUG == 1
            std::cout << "operator + called" << std::endl;
#endif
            return (reverse_iterator(this->_p - n));
        }

        reverse_iterator operator-(difference_type n) const
        {
#if DEBUG == 1
            std::cout << "operator - called" << std::endl;
#endif
            return (reverse_iterator(this->_p + n));
        }

        reverse_iterator &operator--()
        {
#if DEBUG == 1
            std::cout << "post decrementation reverse_iterator called" << std::endl;
#endif
            this->_p--;
            return (*this);
        }

        reverse_iterator operator++(int)
        {
#if DEBUG == 1
            std::cout << "pre decrementation reverse_iterator called" << std::endl;
#endif
            reverse_iterator it = *this;
            this->_p--;
            return (it);
        }

        reverse_iterator &operator-=(difference_type n)
        {
#if DEBUG == 1
            std::cout << "operator -= called" << std::endl;
#endif
            this->_p += n;
            return (*this);
        }

        pointer operator->() const
        {
#if DEBUG == 1
            std::cout << "operator-> called" << std::endl;
#endif
            iterator_type tmp(this->_p);
            tmp--;
            return (tmp.operator->());
        }

        refrence operator[](difference_type n) const
        {
#if DEBUG == 1
            std::cout << "Operator at called" << std::endl;
#endif
            return (base()[-n - 1]);
        }
    };

    template <class Iterator1, class Iterator2>
    bool operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
#if DEBUG == 1
        std::cout << "non member operator==" << std::endl;
#endif
        return (lhs.base() == rhs.base());
    }

    template <class Iterator1, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
#if DEBUG == 1
        std::cout << "non member operator!=" << std::endl;
#endif
        return (lhs.base() != rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
#if DEBUG == 1
        std::cout << "non member operator < called" << std::endl;
#endif
        return (lhs.base() < rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
#if DEBUG == 1
        std::cout << "non member operator <= called" << std::endl;
#endif
        return (lhs.base() <= rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
#if DEBUG == 1
        std::cout << "non member operator > called" << std::endl;
#endif
        return (lhs.base() > rhs.base());
    }

    template <typename Iterator1, typename Iterator2>
    bool operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
#if DEBUG == 1
        std::cout << "non member operator >= called" << std::endl;
#endif
        return (lhs.base() >= rhs.base());
    }

    template <typename Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &src)
    {
#if DEBUG == 1
        std::cout << "non member operator + called" << std::endl;
#endif
        return (src + n);
    }

    template <typename Iterator>
    reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n, const reverse_iterator<Iterator> &src)
    {
#if DEBUG == 1
        std::cout << "non member operator - called" << std::endl;
#endif
        return (src - n);
    }
}
*/