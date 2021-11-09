#pragma once

#include <iostream>
//Set of standard exceptions 
#include <stdexcept>
//Header providing string stream classes
#include <sstream>

//#include "../srcs/utils.hpp"
//#include "../srcs/vector_iterator.hpp"
#include "../srcs/allocator.hpp"
//#include "../srcs/reverse_iterator.hpp"

namespace ft
{
    template < typename T, typename Alloc = ft::allocator<T> >
	class vector
	{
	public:
		typedef T										value_type;
		typedef Alloc									allocator_type;
		typedef value_type&								reference;
		typedef const value_type&						const_reference;
		typedef value_type*								pointer;
		typedef const value_type*						const_pointer;
		typedef ft::vector_iterator<value_type>			iterator;
		typedef ft::vector_iterator<const value_type>	const_iterator;
		typedef ft::reverse_iterator< iterator >		reverse_iterator;
		typedef ft::reverse_iterator< const_iterator >	const_reverse_iterator;
		typedef std::ptrdiff_t							difference_type;
		typedef size_t									size_type;
}