#pragma once 

/*
** The true map container is defined in header <map>
** https://en.cppreference.com/w/cpp/container/map
** 
*/

#include "utils.hpp"
#include "reverse_iterator.hpp"
#include "map_iterator.hpp"
#include "pair.hpp"
#include "make_pair.hpp"

#include <functional>

/*
** Faire une classe node ?
*/

/*
** std::less is defined in <functional>
** "function object for performing comparisons"
** Unless specialized, invokes operator < on type T. 
** TO DO: est-ce qu'il faut faire un ft less ?
*/
namespace ft
{
    template<class Key, class T, class Compare = std::less<Key>, class Allocator = std::allocator<ft::pair<const Key, T> > >
    class map
    {

    };
}