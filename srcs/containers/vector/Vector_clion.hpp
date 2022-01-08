#pragma once

#ifndef _LIBCPP_VECTOR
#define _LIBCPP_VECTOR

//En utilisant le code source ouvert via CLion
namespace ft
{
    template <class _Tp, class _Allocator /* = allocator<_Tp> */>
    class vector<_Tp, _Allocator>
    {
    private:
        /* base = allocator_type */
        typedef __vector_base<_Tp, _Allocator>           __base;
        typedef allocator<_Tp>                           __default_allocator_type;
    public:
        typedef vector                                   __self;
        typedef _Tp                                      value_type;
        typedef _Allocator                               allocator_type;
        typedef typename __base::reference               reference;
        typedef typename __base::const_reference         const_reference;
        typedef typename __base::size_type               size_type;
        typedef typename __base::difference_type         difference_type;
        typedef typename __base::pointer                 pointer;
        typedef typename __base::const_pointer           const_pointer;
        typedef __wrap_iter<pointer>                     iterator;
        typedef __wrap_iter<const_pointer>               const_iterator;
        //Reverse iterator a reimplementer
        //typedef _VSTD::reverse_iterator<iterator>         reverse_iterator;
        //typedef _VSTD::reverse_iterator<const_iterator>   const_reverse_iterator;

    };
}