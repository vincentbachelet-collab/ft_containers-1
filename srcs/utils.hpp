#pragma once

#include <cstddef>
#include <type_traits>

namespace ft
{
	//#include <boost/config.hpp>
	//#include <boost/type_traits/integral_constant.hpp>

	//https://en.cppreference.com/w/cpp/memory/allocator_traits
	//https://en.cppreference.com/w/cpp/header/type_traits

	/*
	** Defined in header <type_traits>
	** Check that T is an integral type.
	** verifie si la valeur rentre dans les limites d'un entier
	** https://code.woboq.org/appleseed/include/boost/type_traits/is_integral.hpp.html
	*/

	/*
	** integral_constant is supposed to be defined in type_traits
	*/
	/*
	template <class T, T v>
	struct iterator_constant
	{
  		const static T 					value = v;
  		typedef T						value_type;
  		typedef iterator_constant<T,v>	type;
 		bool operatorT()				{ return v; }
	};
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

	/* tous les types non definis seront faux */
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
	template<> struct is_integral<long> : public true_type{};
	template<> struct is_integral<long int> : public true_type{};
	template<> struct is_integral<long long int> : public true_type {};
	template<> struct is_integral<unsigned short int> : public true_type {};
	template<> struct is_integral<unsigned int> : public true_type {};
	template<> struct is_integral<unsigned long int> : public true_type {};
	template<> struct is_integral<unsigned long long int> : public true_type {};
	template<> struct is_integral<long long int> : public true_type {};
	template<> struct is_integral<short int> : public true_type {};
	template<> struct is_integral<signed char> : public true_type {};
	template<> struct is_integral<short int> : public true_type {};
	template<> struct is_integral<char> : public true_type{};
	template<> struct is_integral<bool> : public true_type{};

	/*
	** Ajouter enable if 
	*/ 
}
