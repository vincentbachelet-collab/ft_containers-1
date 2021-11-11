#pragma once
#include <iostream>
#include <iterator>

#define DEBG 0 
namespace ft
{
    /*
	** lexicographical_compare
	** https://en.cppreference.com/w/cpp/algorithm/lexicographical_compare
	** defined in algorithm 
	*/

    /*
    ** Ne pas implementer les prototypes mentionnes dans la doc qui 
    ** sont "since" autre chose que 98.
    ** Checks if the first range [first1, last1) is lexicographically
    ** less than the second range [first2, last2).
    */

    /*
    ** Algorithm properties 
    ** Two ranges are compared element by element.
    ** The first mismatching element defines which range is lexicographically less or greater than the other.
    ** If one range is a prefix of another, the shorter range is lexicographically less than the other.
    ** If two ranges have equivalent elements and are of the same length, then the ranges are lexicographically equal.
    ** An empty range is lexicographically less than any non-empty range.
    ** Two empty ranges are lexicographically equal.
    */
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2 )
    {
        //Implementation inspiree de la documentation officielle
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            /* des qu'ils ne vont pas etre egaux on va etre en mesure de lequel est inferieur */
            if (*first1 < *first2)
            {
                if (DEBUG)
                {
                    std::cout << "lexicographical_compare will return true" << std::endl;
                }
                return true;
            }
            /* On retourne true si la premiere range est lexicographiquement inferieure a la seconde */
            if (*first2 < *first1)
            {
                if (DEBUG)
                {
                    std::cout << "lexicographical_compare will return false" << std::endl;
                }
                return false;
            }
        }
        return (first1 == last1) && (first2 != last2);
    }

    /*
    ** Cette fois-ci il est attendu d'utiliser la fonction comp
    ** pour effectuer la comparaison.
    ** comp is a "comparison function object" -> object that satifies
    ** the Compare requirements.
    ** InputIt1, InputIt2 must meet the requirements of LegacyInputIterator.
    */
    template< class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              Compare comp)
    {
        /* Implementation inspiree de la documentation officielle */
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            if (comp(*first1, *first2))
            {
                if (DEBUG)
                {
                    std::cout << "lexicographical comp function will return true" << std::endl;
                }
                return true;
            }
            if (comp(*first2, *first1))
            {
                if (DEBUG)
                {
                    std::cout << "lexicographical comp function will return false" << std::endl;
                }
                return false;
            }
        }
        return (first1 == last1) && (first2 != last2);
    }
}