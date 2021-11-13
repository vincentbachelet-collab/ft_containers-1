#pragma once

#include "../../includes/includes.hpp"

/*
** std::make_pair is defined in <utility>
** https://en.cppreference.com/w/cpp/utility/pair/make_pair
** Creates a std::pair object, deducing the target type from the types of arguments.
*/

/*
** pair objects can be constructed from other pair objects containing different types, 
** if the respective types are implicitly convertible.
*/

/*
** TODO: voir pourquoi ca ete ajoute en plus du constructeur de pair
*/
namespace ft
{
    template<class T1, class T2 >
    ft::pair<T1, T2> make_pair(T1 x, T2 y)
    {
        if (DEBUG)
        {
            std::cout << "make_pair utility called" << std::endl;
        }
        return (pair<T1,T2>(x, y));
    }
}