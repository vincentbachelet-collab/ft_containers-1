#include "../srcs/utils.hpp"
#include <iterator>
#include <iostream>
#include <typeinfo>
#include <vector>

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
*/
template<class BidirIt>
void their_reverse(BidirIt first, BidirIt last)
{
    typename std::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    for (--n; n > 0; n -= 2) {
        typename std::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
    }
}

template<class BidirIt>
void my_reverse(BidirIt first, BidirIt last)
{
    typename ft::iterator_traits<BidirIt>::difference_type n = std::distance(first, last);
    for (--n; n > 0; n -= 2) {
        typename ft::iterator_traits<BidirIt>::value_type tmp = *first;
        *first++ = *--last;
        *last = tmp;
    }
}

int main(void)
{
    //https://www.geeksforgeeks.org/initialize-a-vector-in-cpp-different-ways/
    std::vector<int> v;
    v.push_back(1);
    v.push_back(2);
    v.push_back(3);
    v.push_back(4);
    v.push_back(5);

    std::vector<int> v1;
    v1.push_back(1);
    v1.push_back(2);
    v1.push_back(3);
    v1.push_back(4);
    v1.push_back(5);

    their_reverse(v.begin(), v.end());
    {
        std::cout << "-------------------" << std::endl;
        std::cout << "Their reverse" << std::endl;
        std::vector<int>::iterator it = v.begin();
        std::vector<int>::iterator ite = v.end();

        while (it < ite)
        {
            std::cout << *it << " ";
            it++;
        }
        std::cout << std::endl;
    }
    my_reverse(v1.begin(), v1.end());
    {
        std::cout << "-------------------" << std::endl;
        std::cout << "My reverse" << std::endl;
        std::vector<int>::iterator it = v1.begin();
        std::vector<int>::iterator ite = v1.end();

        while (it < ite)
        {
            std::cout << *it << " ";
            it++;
        }
        std::cout << std::endl;
    }
    

    /*
    my_reverse(v.begin(), v.end());    
    std::cout << std::endl;
    */

    /*
    // VRAI ITERATOR TRAITS
    typedef std::iterator_traits<int*> traits;
    if (typeid(traits::iterator_category)==typeid(std::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator" << std::endl;

    

    // MON ITERATEUR TRAITS
    typedef ft::iterator_traits<int *> my_traits;
    if (typeid(my_traits::iterator_category)==typeid(std::random_access_iterator_tag))
        std::cout << "int* is a random-access iterator" << std::endl;
    */
    return (0);
} 