#pragma once
//voir tutoriel programmerall

/* Reimplementation des iterateurs */
#include <cstddef>
#include <typeinfo>
#include <iostream>

namespace ft
{
    /* Definition officielle de la documentation */
    template <class Category, class T, class Distance = ptrdiff_t,
          class Pointer = T*, class Reference = T&>
    struct iterator {
        typedef T         value_type;
        typedef Distance  difference_type;
        typedef Pointer   pointer;
        typedef Reference reference;
        typedef Category  iterator_category;
    };
}