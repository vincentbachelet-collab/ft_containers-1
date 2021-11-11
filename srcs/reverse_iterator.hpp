#pragma once

#include <memory>
#include <iostream>
#include "./utils.hpp"
#include "vector_iterator.hpp"

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
               if (DEBUG)
               {
                   std::cout << "reverse iterator base constructor called" << std::endl;
               }
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
           **Operator *
           */

            /*
           **Operator +
           */

            /*
           **Operator ++
           */

            /*
           **Operator -
           */

            /*
           **Operator --
           */

          /*
          ** Operator -=
          */

         /*
         ** Operator ->
         */

        /*
        ** Operator[]
        */
    };

    /*
    ** Non-memver function overloads
    */
    /*
    ** Relational operators
    */

    /*
    ** Operator+
    */

    /*
    ** Operator -
    */
}