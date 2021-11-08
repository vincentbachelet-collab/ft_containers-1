#pragma once
//voir tutoriel programmerall
//voir jeetsukumaran, customer iterator.cpp
/* Reimplementation des iterateurs */
#include <cstddef>
#include <typeinfo>
#include <iostream>
#include <cassert>
#include <algorithm>

/* il n y a que les reverse iterateurs qui doivent etre reimplementes dans le sujet */
namespace ft
{
    /* Definition officielle de la documentation */
    //https://cplusplus.com/reference/iterator/iterator/
    //voir tutoriel iterateurs personnalises : it-swarm-fr

    /* Base class template */
    template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
    class my_iterator
    {
    private:
        pointer _ptr;
    public:
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;

        /* Classe canonique */
        //Constructeur par defaut
        my_iterator(): pointer(NULL) {}
        my_iterator(pointer ptr): pointer(ptr) {}
        my_iterator(my_iterator const &src): _ptr(src._ptr) {}
        virtual ~my_iterator() {}
        my_iterator & operator=(my_iterator const &rhs)
        {
            _ptr = rhs._ptr;
            return (*this);
        }

        //Surcharge d'operateurs pour un iterateur
        value_type operator++()
        {
            value_type i = *this;
            _ptr++;
            return (i);
        }

        reference operator*()
        {
            return *_ptr;
        }

        pointer operator->()
        {
            return (_ptr);
        }

        bool operator==(const self_type &rhs)
        {
            return (_ptr == rhs._ptr);
        }

        bool operator!=(const self_type &rhs)
        {
            return (_ptr != rhs._ptr);
        }
    };

    //https://cplusplus.com/reference/iterator/iterator_traits/

}