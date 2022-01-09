#pragma once

//TODO: rajouter l include

namespace ft
{   
    /* Implementation inspiree de la documentation officielle */
    template<class InputIt1, class InputIt2>
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2 )
    {
        
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            if (*first1 < *first2)
            {
                if (DEBUG == 1)
                    std::cout << "lexicographical_compare will return true" << std::endl;
                return true;
            }
            /* On retourne true si la premiere range est lexicographiquement inferieure a la seconde */
            if (*first2 < *first1)
            {
                if (DEBUG == 1)
                    std::cout << "lexicographical_compare will return false" << std::endl;
                return false;
            }
        }
        return (first1 == last1) && (first2 != last2);
    }


    /* Implementation inspiree de la documentation officielle */
    template< class InputIt1, class InputIt2, class Compare >
    bool lexicographical_compare( InputIt1 first1, InputIt1 last1,
                              InputIt2 first2, InputIt2 last2,
                              Compare comp)
    {
        for ( ; (first1 != last1) && (first2 != last2); ++first1, (void) ++first2 )
        {
            if (comp(*first1, *first2))
            {
                if (DEBUG == 1)
                    std::cout << "lexicographical comp function will return true" << std::endl;
                return true;
            }
            if (comp(*first2, *first1))
            {
                if (DEBUG == 1)
                    std::cout << "lexicographical comp function will return false" << std::endl;
                return false;
            }
        }
        return (first1 == last1) && (first2 != last2);
    }
}