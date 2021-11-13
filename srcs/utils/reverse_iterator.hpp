#pragma once

#include "../../includes/includes.hpp"

/*
** std::reverse_iterator::reverse_iterator
*/

/*
** Construct reverse_iterator object
** default constructor
*** construct a reverse iterator that points to no object.
*** The internal base iterator is value-initialized.
** initialization constructor
*** construct a reverse iterator from some original iterator it.
*** reverses the order
** copy / type-cast constructor
*** construct a reverse iterator from some other reverse iterator.
*/

/*
** http://www.cplusplus.com/reference/iterator/reverse_iterator/
** reverses the direction in which a bidirectional or random-access iterator iterates though a range
** a copy of the original iterator (base iterator) is kept internally and used to reflect the operations performed
** on the reserve iterator. Whenever the reverse iterator is incremented, the base iterator is decreased.
*/
namespace ft 
{
    /* template parameter : bidirectional iterator type or random-access iterator */
    template <class Iterator>
    class reverse_iterator
    {
        protected:
            /*
            ** On aurait pu appeler _p egalement _base_iterator 
            */

            iterator_type _p;
        //verifier le niveau de "protection"
        public:
            typedef Iterator                                                iterator_type;
            /* Preserves Iteror's category */
            typedef typename iterator_traits<Iterator>::iterator_category   iterator_category;
            /*Preserves iterator's value type */
            typedef typename iterator_traits<Iterator>::value_type          value_type;
            /* Preserves Iterator's pointer type */
            typedef typename iterator_traits<Iterator>::difference_type     difference_type;
            /* Preserves Iterator's difference type */
            typedef typename iterator_traits<Iterator>::pointer             pointer;
            /* Preserves iterator's reference type */
            typedef typename iterator_traits<Iterator>::reference           reference;

            /* Member functions */
            /*
            ** Constructors
            */
            reverse_iterator(): _p(NULL)
            {
                if (DEBUG)
                {
                    std::cout << "reverse iterator default constructor called" << std::endl;
                }
            }

            reverse_iterator(iterator_type ptr): _p(ptr)
            {
                if (DEBUG)
                {
                    std::cout << "reverse iterator ptr constructor called" << std::endl;
                }
            }

            /*
            ** Base (constructor par copie)
            ** iterator_type base() const
            ** returns a copu of the base iterator
            ** the base iterator is an iterator of the same type as the one used to construct reverse_iterator 
            ** but pointing to the element next to the one the reverse_iterator is currently pointing to)
            ** a reverse iterator has always an offset of -1 with respect to its base iterator. 
            */
           template <typename iter>
           reverse_iterator(const reverse_iterator<iter> &src) _p(src.base())
           {
               //TODO: a retester, comparer
               if (DEBUG)
               {
                   std::cout << "reverse iterator base constructor called" << std::endl;
               }
           }

           iterator_type base(void) const 
           {
               if (DEBUG)
               {
                   std::cout << "reverse iterator base function called" << std::endl;
               }
               return (this->_p);
           }
            
            /*
            ** Operateur d'assignation
            */
            reverse_iterator & operator=(reverse_iterator<type> & src)
            {
                if (DEBUG)
                {
                    std::cout << "asssignation operator function called" << std::endl;
                }
                this->_p = src._p;
                return (*this);
            }
            /*
            ** Destructor
            */
            virtual ~reverse_iterator() 
            {
                if (DEBUG)
                {
                    std::cout << "reverse iterator destructor called" << std::endl;
                }
            }

            /*
            ** Operateur de cast ? (pas vu dans la documentation)
            */
           /*
            operator    reverse_iterator<vector_iterator<value_type const>() const 
            {
                if (DEBUG)
                {
                    std::cout << "reverse iterator operator" << std::endl;
                }
                return (reverse_iterator<vector_iterator<value_type const>(_p);
            }

            operator    reverse_iterator<vector_iterator<value_type>()
            {
                if (DEBUG)
                {
                    std::cout << "reverse iterator operator" << std::endl;
                }
                return (reverse_iterator<vector_iterator<value_type>(_p);
            }
            */

           /*
           **  OPERATOR OVERLOADS
           */
          
          /*
          ** Overload * (derefencement)
          ** TODO: faire des tests
          */
            reference operator *() const 
            {
                iterator_type it = this->_p;
                it--;
                return it;
            }

            /*
            ** Checker si on a besoin de faire une version const et pas const
            */
            reference operator *()
            {
                iterator_type it = this->_p;
                it--;
                return it;
            }

           /*
           ** Operator ++ post incrementation
           ** Dans le cadre d'un reverse_iterator on va faire l'inverse d'un iterator
           ** TO DO: voir s il faut modifier le base ?
           */
            reverse_iterator &operator++()
            {
                if (DEBUG)
                {
                    std::cout << "post incrementation reverse_iterator called" << std::endl;
                }
                this->_p--;
                return (*this);
            }

            /*
            ** TO DO:revoir tutoriel pour expliquer pourquoi on procede comme ca
            */
            reverse_iterator operator++(int)
            {
                if (DEBUG)
                {
                    std::cout << "pre incrementation reverse_iterator called" << std::endl;
                }
                reverse_iterator it = *this;
                this->_p--;
                return (it);
            }

            /*
           **Operator +
           */
             reverse_iterator operator+(difference_type n ) const 
            {
                if (DEBUG)
                {
                    std::cout << "operator + called" << std::endl;
                }
                return (reverse_iterator(this->_p - n));
            }

            /*
           **Operator -
           */
            reverse_iterator operator-(difference_type n ) const 
            {
                if (DEBUG)
                {
                    std::cout << "operator - called" << std::endl;
                }
                return (reverse_iterator(this->_p + n));
            }

            /*
           **Operator --
           */
           reverse_iterator &operator--()
            {
                if (DEBUG)
                {
                    std::cout << "post decrementation reverse_iterator called" << std::endl;
                }
                this->_p--;
                return (*this);
            }

            /*
            ** TO DO:revoir tutoriel pour expliquer pourquoi on procede comme ca
            */
            reverse_iterator operator++(int)
            {
                if (DEBUG)
                {
                    std::cout << "pre decrementation reverse_iterator called" << std::endl;
                }
                reverse_iterator it = *this;
                this->_p--;
                return (it);
            }

            /*
            ** Operator -=
            ** TODO: a tester
            */
            reverse_iterator &operator-=(difference_type n)
            {
                if (DEBUG)
                {
                    std::cout << "operator -= called" << std::endl;
                }
                this->_p += n;
                return (*this);
            }
         

            /*
            ** Operator ->
            ** access the pointed to element
            ** https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator*
            ** A tester
            */
            pointer operator->() const 
            {
                if (DEBUG)
                {
                    std::cout << "operator-> called" << std::endl;
                }
                iterator_type tmp(this->_p);
                tmp--;
                //TO DO: verifier le retour
                return (tmp.operator->());
            }

            /*
            ** Operator[]
            ** access an element by index 
            ** https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator_at
            */
            refrence operator[](difference_type n) const 
            {
                if (DEBUG)
                {
                    std::cout << "Operator at called" << std::endl;
                }
                //TO DO: checker code source
                return (base()[-n - 1]);
            }
    };

    /*
    ** Non-member function overloads
    ** https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator_cmp
    */

    /*
    ** Operator == 
    */
    template<class Iterator1, class Iterator2>
    bool operator==(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
        if (DEBUG)
        {
            std::cout << "non member operator==" << std::endl;
        }
        return (lhs.base() == rhs.base());
    }
    /*
    ** Operator != 
    */
    template<class Iterator1, class Iterator2>
    bool operator!=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
        if (DEBUG)
        {
            std::cout << "non member operator!=" << std::endl;
        }
        return (lhs.base() != rhs.base());
    }
    /*
    ** Operator < 
    */
    template<typename Iterator1, typename Iterator2>
    bool operator<(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
        if (DEBUG)
        {
            std::cout << "non member operator < called" << std::endl;
        }
        return (lhs.base() < rhs.base());
    }
    /*
    ** Operator <=
    */
    template<typename Iterator1, typename Iterator2>
    bool operator<=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
        if (DEBUG)
        {
            std::cout << "non member operator <= called" << std::endl;
        }
        return (lhs.base() <= rhs.base());
    }

    /*
    ** Operator >
    */
    template<typename Iterator1, typename Iterator2>
    bool operator>(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
        if (DEBUG)
        {
            std::cout << "non member operator > called" << std::endl;
        }
        return (lhs.base() > rhs.base());
    }

    /*
    ** Operator >=
    */
    template<typename Iterator1, typename Iterator2>
    bool operator>=(const reverse_iterator<Iterator1> &lhs, const reverse_iterator<Iterator2> &rhs)
    {
        if (DEBUG)
        {
            std::cout << "non member operator >= called" << std::endl;
        }
        return (lhs.base() >= rhs.base());
    }

    /*
    ** Operator+
    **TODO: checker les "constexprr" -> faire une version const ?
    **TODO: a tester
    ** https://en.cppreference.com/w/cpp/iterator/reverse_iterator/operator%2B
    */
    template<typename Iterator>
    reverse_iterator<Iterator> operator+(typename reverse_iterator<Iterator>::difference_type n,const reverse_iterator<Iterator> &src)
    {
        if (DEBUG)
        {
             std::cout << "non member operator + called" << std::endl;
        }
        return (src + n);
    }

    /*
    ** Operator -
    ** computes the distance between two iterator adaptators
    */
    template<typename Iterator>
    reverse_iterator<Iterator> operator-(typename reverse_iterator<Iterator>::difference_type n,const reverse_iterator<Iterator> &src)
    {
        if (DEBUG)
        {
             std::cout << "non member operator - called" << std::endl;
        }
        return (src - n);
    }
}