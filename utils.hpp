#pragma once

#include <iostream>

namespace ft
{
    template <class T, T v>
    class integral_constant
    {
    public:
        const static T value = v;
        typedef T value_type;
        typedef integral_constant<T, v> type;
        const value_type operator()() const { return value; }
    };

    typedef integral_constant<bool, true> true_type;
    typedef integral_constant<bool, false> false_type;

    template <class T>
    struct is_integral : public false_type
    {
    };

    template <class T>
    struct is_integral<const T> : public is_integral<T>
    {
    };
    template <class T>
    struct is_integral<volatile const T> : public is_integral<T>
    {
    };
    template <class T>
    struct is_integral<volatile T> : public is_integral<T>
    {
    };

    template <>
    struct is_integral<unsigned char> : public true_type
    {
    };
    template <>
    struct is_integral<unsigned short> : public true_type
    {
    };
    template <>
    struct is_integral<unsigned int> : public true_type
    {
    };
    template <>
    struct is_integral<unsigned long> : public true_type
    {
    };
    template <>
    struct is_integral<signed char> : public true_type
    {
    };
    template <>
    struct is_integral<short> : public true_type
    {
    };
    template <>
    struct is_integral<int> : public true_type
    {
    };
    template <>
    struct is_integral<long int> : public true_type
    {
    };
    template <>
    struct is_integral<long long int> : public true_type
    {
    };
    template <>
    struct is_integral<unsigned long long int> : public true_type
    {
    };
    template <>
    struct is_integral<char> : public true_type
    {
    };
    template <>
    struct is_integral<bool> : public true_type
    {
    };

    template <class Iterator>
    class iterator_traits
    {
    public:
        //Member types - Iter is the iterator type the retrived properties for
        typedef typename Iterator::difference_type difference_type;
        typedef typename Iterator::value_type value_type;
        typedef typename Iterator::pointer pointer;
        typedef typename Iterator::reference reference;
        typedef typename Iterator::iterator_category iterator_category;
    };

    template <class T>
    class iterator_traits<T *>
    {
    public:
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef T *pointer;
        typedef T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    template <class T>
    class iterator_traits<const T *>
    {
    public:
        typedef std::ptrdiff_t difference_type;
        typedef T value_type;
        typedef const T *pointer;
        typedef const T &reference;
        typedef std::random_access_iterator_tag iterator_category;
    };

    //If B is true, std::enable_if has a public member typedef type,
    //equal to T; otherwise, there is no member typedef.
    template <bool B, typename T = void>
    struct enable_if
    {
    };

    template <typename T>
    struct enable_if<true, T>
    {
        typedef T type;
    };

    template <class InputIt1, class InputIt2>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2)
    {
        //Inspiree de la documentation officielle
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!(*first1 == *first2))
                return false;
        }
        return true;
    }

    template <class InputIt1, class InputIt2, class BinaryPredicate>
    bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
    {
        //Inspiree de la documentation officielle
        for (; first1 != last1; ++first1, ++first2)
        {
            if (!p(*first1, *first2))
                return false;
        }
        return true;
    }
}

namespace ft
{
    /* Implementation inspiree de la documentation officielle */
    template <class InputIt1, class InputIt2>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2)
    {

        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (*first1 < *first2)
            {
                return true;
            }
            /* On retourne true si la premiere range est lexicographiquement inferieure a la seconde */
            if (*first2 < *first1)
            {
                return false;
            }
        }
        return (first1 == last1) && (first2 != last2);
    }

    /* Implementation inspiree de la documentation officielle */
    template <class InputIt1, class InputIt2, class Compare>
    bool lexicographical_compare(InputIt1 first1, InputIt1 last1,
                                 InputIt2 first2, InputIt2 last2,
                                 Compare comp)
    {
        for (; (first1 != last1) && (first2 != last2); ++first1, (void)++first2)
        {
            if (comp(*first1, *first2))
            {
                return true;
            }
            if (comp(*first2, *first1))
            {
                return false;
            }
        }
        return (first1 == last1) && (first2 != last2);
    }

    template <class InputIterator>
    typename ft::iterator_traits<InputIterator>::difference_type
    distance(InputIterator first, InputIterator last)
    {
        typename ft::iterator_traits<InputIterator>::difference_type rtn = 0;
        while (first != last)
        {
            first++;
            rtn++;
        }
        return (rtn);
    }
}