/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_iterator.hpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 00:11:31 by charmstr          #+#    #+#             */
/*   Updated: 2021/01/26 12:43:04 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_ITERATOR_HPP
# define FT_ITERATOR_HPP

//#include <iterator>
# include <memory> //for the std:..._iterator_tag definitions and the ptrdiff_t

namespace ft
{	
	/*
	** ********************************************************************
	** Iterator_traits:	interface to get the iterators's types
	** ********************************************************************
	*/
	template< typename Iterator >
	class iterator_traits
	{
		public:
		typedef typename Iterator::value_type value_type;
		typedef typename Iterator::difference_type difference_type;
		typedef typename Iterator::pointer pointer;
		typedef typename Iterator::reference reference;
		typedef typename Iterator::iterator_category iterator_category;
	};

	
	// Iterator_traits:	raw pointer specialisation
	template< typename Iterator >
	class iterator_traits< Iterator* >
	{
		public:
		typedef Iterator value_type;
		typedef ptrdiff_t difference_type;
		typedef Iterator* pointer;
		typedef Iterator& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	// Iterator_traits:	const raw pointer specialisation
	template< typename Iterator >
	class iterator_traits< const Iterator* >
	{
		public:
		typedef Iterator value_type;
		typedef ptrdiff_t difference_type;
		typedef const Iterator* pointer;
		typedef const Iterator& reference;
		typedef std::random_access_iterator_tag iterator_category;
	};

	/*
	** iterator_traits specialisation to get ride of all the integral types:
	**  - bool
    **  - char
    **  - char16_t
    **  - char32_t
    **  - wchar_t
    **  - signed char
    **  - short int
    **  - int
    **  - long int
    **  - long long int
    **  - unsigned char
    **  - unsigned short int
    **  - unsigned int
    **  - unsigned long int
    **  - unsigned long long int
	*/
	template<> class iterator_traits<bool>{};
	template<> class iterator_traits<char>{};
	template<> class iterator_traits<char16_t>{};
	template<> class iterator_traits<char32_t>{};
	template<> class iterator_traits<wchar_t>{};
	template<> class iterator_traits<signed char>{};
	template<> class iterator_traits<short int>{};
	template<> class iterator_traits<int>{};
	template<> class iterator_traits<long>{};
	template<> class iterator_traits<long long>{};
	template<> class iterator_traits<unsigned char>{};
	template<> class iterator_traits<unsigned short int>{};
	template<> class iterator_traits<unsigned int>{};
	template<> class iterator_traits<unsigned long>{};
	template<> class iterator_traits<unsigned long long>{};

	/*
	** ********************************************************************
	** Iterator: The base class for the reimplementation of the
	** legacyIterators, it contains 5 defined types.
	** Reimplementations of ft::bidirectionalIterator, ft::randomAccessIterator
	** will inherit from this base class.
	** ********************************************************************
	*/
	template< typename Category,
			typename T,
			typename Distance = ptrdiff_t,
			typename Pointer = T*,
			typename Reference = T& >
	class iterator
	{
		protected:
		typedef T         value_type;
		typedef Distance  difference_type;
		typedef Pointer   pointer;
		typedef Reference reference;
		typedef Category  iterator_category;
	};

	/*
	** ********************************************************************
	** is_iterator:	SFINAE mechanism to decide if a template parameter is an
	**		iterator or not. It will be an iterator if the template
	**		parameter has the typedef iterator_category
	**
	** logic:	If the template parameter has a typedef named 
	**		"iterator_category"	the	member variable value is true.
	**
	** note: Checking directly if we had the typedef "value_type" would be a
	**		mistake as the name itself is pretty common(it is a typedef 
	**		existing in	containers for example).
	**
	** note2: due to immediate context problem, we could not use directly:
	** 			iterator_traits<IsIterator>::iterator_category
	** 		as it would fail when the template parameter is an int.
	** 		we specialised that iterator_traits class to not raise warning on
	** 		int	type parameter.
	**
	** sources:	https://en.wikipedia.org/wiki/Substitution_failure_is_not_an_error
	** 			https://en.cppreference.com/w/cpp/language/variadic_arguments
	**
	** Notes on test(...) function:
	**		In C++, this form is allowed even though the arguments passed to
	**		such function are not accessible, and is commonly used as the
	**		fallback overload in SFINAE, exploiting the lowest priority of the
	**		ellipsis conversion in overload resolution.
	** ********************************************************************
	*/
	template< typename IsIterator>
	struct is_iterator
	{
		typedef char yes[1];
		typedef char no[2]; //different sizes distinguished by sizeof().

		template <typename IsIterator_>
		static yes& test(typename iterator_traits<IsIterator_>::iterator_category* = nullptr);

		template <typename C>
		static no& test(...);

		// If the "sizeof" of the result of calling test<T>(nullptr) is equal to
		// sizeof(yes), the first overload worked and T has a nested type named
		// value_type
		static const bool value = sizeof(test<IsIterator>(nullptr)) == sizeof(yes);
	};

	/*
	** ********************************************************************
	** is_input_iterator:	This second check is done is conjunction with the
	** 		first one (checking that the typedef "iterator_category" exists) so
	** 		that we	can	rule out the output iterator kind which is a specific
	** 		kind of	iterator that do not possess a "value_type" typedef.
	**
	** logic:	If the template parameter has a typedef named "value_type" the
	** 		member variable value is true.
	** ********************************************************************
	*/
	template< typename IsInputIterator>
	struct is_input_iterator
	{
		typedef char yes[1];
		typedef char no[2]; //different sizes distinguished by sizeof().

		template <typename IsInputIterator_>
		static yes& test(typename iterator_traits<IsInputIterator_>::value_type* = nullptr);

		template <typename C>
		static no& test(...);

		static const bool value = sizeof(test<IsInputIterator>(nullptr)) == sizeof(yes);
	};

	/*
	** ********************************************************************
	** Distance: to calculate the distance between two iterators
	** note:using tag dispatching technique
	** ********************************************************************
	*/

	//specialisation for the distance function when we are in the case of
	//a random access iterator
	template <typename InputIterator, typename Distance>
	void	
	distance(InputIterator first, const InputIterator &last, Distance &n, std::random_access_iterator_tag)
	{
		n = 0;
		while (last != first)
		{
			n++;
			++first;
		}
	}

	//specialisation for the other types of iterators.
	template <typename InputIterator, typename Distance>
	void	
	distance(InputIterator first, const InputIterator &last, Distance &n, std::forward_iterator_tag)
	{
		n = 0;
		while (last != first)
		{
			n++;
			++first;
		}
	}

	//specialisation for the other types of iterators.
	template <typename InputIterator, typename Distance>
	void	
	distance(InputIterator first, const InputIterator &last, Distance &n, std::bidirectional_iterator_tag)
	{
		n = 0;
		while (last != first)
		{
			n++;
			++first;
		}
	}

	//specialisation for the other types of iterators.
	template <typename InputIterator, typename Distance>
	void	
	distance(InputIterator first, const InputIterator &last, Distance &n, std::input_iterator_tag)
	{
		n = 0;
		while (last != first)
		{
			n++;
			++first;
		}
	}

	//base function before dispatching to calculate the distance between two
	//iterators
	template <typename InputIterator, typename Distance>
	void
	distance(InputIterator first, const InputIterator &last, Distance &n)
	{
		distance(first, last, n, typename iterator_traits<InputIterator>::iterator_category());
	}

}
#endif
