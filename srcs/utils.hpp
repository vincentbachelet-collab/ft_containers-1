#pragma once

#include <cstddef>
#include <type_traits>
#include <iterator>

namespace ft
{
	//https://en.cppreference.com/w/cpp/memory/allocator_traits
	//https://en.cppreference.com/w/cpp/header/type_traits

	/*
	** Defined in header <type_traits>
	** Check that T is an integral type.
	** verifie si la valeur rentre dans les limites d'un entier
	** https://code.woboq.org/appleseed/include/boost/type_traits/is_integral.hpp.html
	*/
	template <class T, T v>
	class integral_constant
    {
	public:
      const static  T		               value =v;
      typedef T	                           value_type;
      typedef integral_constant<T, v>   	type;
      const value_type operator()() const { return value; }
    };

	/*
	** https://code.woboq.org/gcc/libstdc++-v3/include/std/type_traits.html
	*/
	typedef integral_constant<bool,true> true_type;
	typedef integral_constant<bool,false> false_type;

	/* 
	** tous les types non definis seront faux
	*/
	template <class T> struct is_integral : public false_type {};
	template <class T> struct is_integral<const T> : public is_integral<T> {};
	template <class T> struct is_integral<volatile const T> : public is_integral<T>{};
	template <class T> struct is_integral<volatile T> : public is_integral<T>{};
	template<> struct is_integral<unsigned char> : public true_type {};
	template<> struct is_integral<unsigned short> : public true_type{};
	template<> struct is_integral<unsigned int> : public true_type{};
	template<> struct is_integral<unsigned long> : public true_type{};
	template<> struct is_integral<signed char> : public true_type{};
	template<> struct is_integral<short> : public true_type{};
	template<> struct is_integral<int> : public true_type{};
	template<> struct is_integral<long int> : public true_type{};
	template<> struct is_integral<long long int> : public true_type {};
	template<> struct is_integral<unsigned long long int> : public true_type {};
	template<> struct is_integral<char> : public true_type{};
	template<> struct is_integral<bool> : public true_type{};

	/*
	** Ajouter enable if 
	*/

	/*
	** Si on definit un custom Iterateur, il faudra s'assurer que les iterator_traits sont
	** correctement definis. Pour cela, le mieux est d'expliciter/ de rediger une specialisation
	** des iterator traits. 
	** Les iterator traits sont relativement recents et ont en quelque sorte remplace les
	** iterator tags.
	** les iterateurs traits vont permettrent de recuperer la value type ou la difference type de pointeur
	** ce qui ne serait apparemment pas possible sans.
	*/

	/*
	** Iterator_traits 
	** https://en.cppreference.com/w/cpp/iterator/iterator_traits
	*/
	 /*
    ** defined in header <iterator>
	** std::iterator_traits is the type trait class that provides uniform interface 
	**to the properties of LegacyIterator types.This makes it possible to implement algorithms only in terms of iterators.
    ** the template can be specialized for user-defined iterators.
	*/

	/*
	** Template parameter
	** Fully generic version
	*/
    template <class Iter>
    struct iterator_traits
	{
		/*
		** Member types - Iter is the iterator type the retrived properties for
		*/
		typedef typename Iter::difference_type		difference_type;
		typedef typename Iter::value_type			value_type;
		typedef typename Iter::pointer				pointer;
		typedef typename Iter::reference			reference;
		typedef typename Iter::iterator_category	iterator_category;
	};

	/*
	** Specialisation
	** used whenever the template argument is a pointer type
	** May be specialised for user-provided types that may be used as iterators.
	** The standard library provides partial specializations for pointer types T * 
	** which makes it possible to use all iterator based algorithms with raw pointers 
	*/
    template <class T>
	struct iterator_traits<T *>
	{
		typedef std::ptrdiff_t					difference_type;
		typedef T							 	value_type;
		typedef T* 								pointer;
		typedef T&								reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

	/*
	** Verifier que d'autres membres ne doivent pas etre const
	*/
	template <class T>
	struct iterator_traits<const T*>
	{
		typedef std::ptrdiff_t 					difference_type;
		typedef T 								value_type;
		typedef const T* 						pointer;
		typedef const T& 						reference;
		typedef std::random_access_iterator_tag	iterator_category;
	};

}
