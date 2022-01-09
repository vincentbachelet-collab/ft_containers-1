#pragma once

#include "../../includes/includes.hpp"

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

	template <class Iter>
	struct iterator_traits
	{
		/*
		** Member types - Iter is the iterator type the retrived properties for
		*/
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
		typedef typename Iter::iterator_category iterator_category;
	};

	template <class T>
	struct iterator_traits<T *>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef T *pointer;
		typedef T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	template <class T>
	struct iterator_traits<const T *>
	{
		typedef std::ptrdiff_t difference_type;
		typedef T value_type;
		typedef const T *pointer;
		typedef const T &reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

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
		/* Inspiree de la documentation officielle */
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!(*first1 == *first2))
			{
				if (DEBUG == 1)
					std::cout << "equal algorithm will return false" << std::endl;
				return false;
			}
		}
		if (DEBUG == 1)
			std::cout << "equal algorithm will return true" << std::endl;
		return true;
	}

	template <class InputIt1, class InputIt2, class BinaryPredicate>
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, BinaryPredicate p)
	{
		/* Inspiree de la documentation officielle */
		for (; first1 != last1; ++first1, ++first2)
		{
			if (!p(*first1, *first2))
			{
				if (DEBUG == 1)
					std::cout << "equal algorithm will return false" << std::endl;
				return false;
			}
		}
		if (DEBUG == 1)
			std::cout << "equal algorithm will return true" << std::endl;
		return true;
	}
}