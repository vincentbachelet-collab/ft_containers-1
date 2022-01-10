#pragma once

#include "../../../includes/common/includes.hpp"
//#include "../containers/vector/vector.hpp"
//#include "../containers/vector/vector_iterator.hpp"

//class vector;
//class vector_iterator;
//class iterator_traits;

#include "./utils.hpp"

//TODO: verifier que tout est bien implemente
namespace ft
{
        template <class Iterator>
        class reverse_iterator
        {
        public:
                typedef Iterator iterator_type;
                typedef typename iterator_traits<Iterator>::iterator_category iterator_category;
                typedef typename iterator_traits<Iterator>::reference reference;
                typedef typename iterator_traits<Iterator>::pointer pointer;
                typedef typename iterator_traits<Iterator>::difference_type difference_type;
                typedef typename iterator_traits<Iterator>::value_type value_type;

        protected:
                iterator_type _ptr;

        public:
                reverse_iterator() : _ptr(NULL) {}
                reverse_iterator(iterator_type ptr) : _ptr(ptr) {}
                template <typename iter>
                reverse_iterator(reverse_iterator<iter> &src) : _ptr(src.base()) {}

                iterator_type base(void) const
                {
                        return (this->_ptr);
                }

                reverse_iterator &operator=(reverse_iterator const &src)
                {
                        this->_ptr = src._ptr;
                        return (*this);
                }

                virtual ~reverse_iterator() {}

                /*
                operator reverse_iterator<vector_iterator<value_type const>() const
                {
                        return (reverse_iterator<vector_iterator<value_type const>(_ptr);
                }

                operator reverse_iterator<vector_iterator<value_type>()
                {
                        return (reverse_iterator<vector_iterator<value_type>(_ptr);
                }
                */

                reference operator*() const
                {
                        iterator_type it = this->_ptr;
                        it--;
                        return it;
                }

                reference operator*()
                {
                        iterator_type it = this->_ptr;
                        it--;
                        return it;
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

                //Attention doublon
                /*
                reverse_iterator &operator++(int)
                {
                        reverse_iterator it = *this;
                        this->_ptr--;
                        return (it);
                }
                */

                reverse_iterator &operator-=(difference_type n)
                {
                        this->_ptr += n;
                        return (*this);
                }

                pointer operator->() const
                {
                        iterator_type tmp(this->_ptr);
                        tmp--;
                        return (tmp.operator->());
                }

                reference operator[](difference_type n) const
                {
                        return (base()[-n - 1]);
                }
        };

        /*
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
        */
}