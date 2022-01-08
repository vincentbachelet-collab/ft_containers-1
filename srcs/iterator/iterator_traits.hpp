#pragma once

//Code source https://code.woboq.org/gcc/libstdc++-v3/include/bits/stl_iterator.h.html
//https://code.woboq.org/gcc/libstdc++-v3/include/bits/stl_iterator_base_types.h.html
//https://code.woboq.org/gcc/libstdc++-v3/include/std/type_traits.html
//https://en.cppreference.com/w/cpp/iterator/iterator_traits

#include <bits/cpp_type_traits.h>
#include <ext/type_traits.h>
#include <bits/move.h>
#include <bits/ptr_traits.h>

# include <cstddef> // ptrdiff_t
# include <typeinfo>

/*std::iterator_trait is the type trait class that provides uniform interface to 
** the properties of LegacyIterator types.
** This makes it possible to implement algorithms only in terms of iterators.

*/
namespace ft
{
//Reprise des typedefs du source code
    struct iterator_traits
    {
        //public member attributes
    typedef typename Iterator::difference_type   difference_type;
    typedef typename Iterator::value_type        value_type;
    typedef typename Iterator::pointer           pointer;
    typedef typename Iterator::reference         reference;
    typedef typename Iterator::iterator_category iterator_category;
    //checker si le make_unsigned est autorise avec la norme 98 ?
    typedef typename boost::move_detail::make_unsigned<difference_type>::type size_type;

    };

    template<class T>
    struct iterator_traits<T*>
    {
    typedef std::ptrdiff_t                    difference_type;
    typedef T                                 value_type;
    typedef T*                                pointer;
    typedef T&                                reference;
    typedef std::random_access_iterator_tag   iterator_category;
    typedef typename boost::move_detail::make_unsigned<difference_type>::type size_type;
    };
    template<class T>
    struct iterator_traits<const T*>
    {
    typedef std::ptrdiff_t                    difference_type;
    typedef T                                 value_type;
    typedef const T*                          pointer;
    typedef const T&                          reference;
    typedef std::random_access_iterator_tag   iterator_category;
    typedef typename boost::move_detail::make_unsigned<difference_type>::type size_type;
    };

}