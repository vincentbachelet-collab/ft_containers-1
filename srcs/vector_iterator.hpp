#pragma once 

#include <cstddef>//ptrdiff_t
#include <iterator>//On a en besoin pour random_access_iterator_tag

namespace ft
{
    template<typename T>
    class vector_iterator
    {
    public:
        typedef T											value_type;
		typedef std::ptrdiff_t								difference_type;
		typedef T*											pointer;
		typedef T&											reference;
		typedef std::random_access_iterator_tag				iterator_category;
		typedef vector_iterator								iterator;
		typedef vector_iterator<const T>					const_iterator;
    protected:
        value_type *_p;
    public:
        vector_iterator() : _p(0) {}
		vector_iterator(value_type &x) : _p(&x) {}
		vector_iterator(value_type *x) : _p(x) {}
		vector_iterator(const iterator &x) { *this = x; }
		virtual ~vector_iterator(void) {}
    };
}