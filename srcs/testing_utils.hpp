#include "../srcs/utils.hpp"
#include <iterator>
#include <iostream>
#include <typeinfo>
#include <vector>

/* 
void    iterator_traits(void);

/*
** Les iterator traits permettent d'implementer des algorithmes "only in terms of iterator"
*/

/*
** Par exemple ici, on definit un iterateur traits qui va permettre de reverse les elements
** d un vector.
*/

/*
** Selon la documentation microsoft, c'est une "struct d'assistance" 
** de module utilise pour specifier toutes les definitions de type critiques
** qu'un iterateur doit avoir.
** Il n'y a que des types et pas des fonctions membres.
*/

/*
** Les iterateurs traits permettent de savoir vers quels types pointent les pointeurs/iterateurs.
*/

/*
** Les iterateurs traits contiennent des "nested typedefs"
** function template pour tester les iterator_traits
*/
template<class BidirIt>
void std_reverse(BidirIt first, BidirIt last)
{
    typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    for (--n; n > 0; n -= 2) {
        typename std::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
    }
}

template<class BidirIt>
void ft_reverse(BidirIt first, BidirIt last)
{
    typename ft::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    for (--n; n > 0; n -= 2) {
        typename ft::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
    }
}