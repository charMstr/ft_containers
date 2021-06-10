/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_utils.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/25 06:38:55 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/08 13:34:15 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_UTILS_HPP
# define FT_UTILS_HPP

namespace ft
{
	/*
	** ********************************************************************
	** enable_if: if first parameter resolves to true, "::type" is defined.
	** it will allow us to do some static polymorphism (using SFINAE)
	** ********************************************************************
	*/
	template< bool condition, class T = void>
	struct enable_if{}; //nothing defined when false

	template<class T>
	struct enable_if<true, T>
	{
		typedef T type;
	};

	/*
	** ********************************************************************
	** is_same: if both template parameter are the exact same, it resolves to
	** true
	** ********************************************************************
	*/
	//is_same, default to false
	template<typename T = void, typename U = void>
	struct is_same
	{
		static const bool value = false;
	};

	//specialisation of is_same
	template<typename T>
	struct is_same<T,T>  //specialization
	{
		static const bool value = true;
	};

	/*
	** ********************************************************************
	** equal: two iterators have their content compared.
	**
	** Return: false if the content is not the same, or the range is not the
	**	same.
	** ********************************************************************
	*/

	template< class InputIt1, class InputIt2 >
	bool equal(InputIt1 first1, InputIt1 last1, InputIt2 first2, InputIt2 last2)
	{
		for (;first1 != last1 && first2 != last2; first1++)
		{
			if (*first1 != *first2)
				return (false);
			first2++;	
		}
		if (first1 == last1 && first2 != last2)
			return (false);
		if (first1 != last1 && first2 == last2)
			return (false);
		return (true);
	}

	/*
	** ********************************************************************
	** lexicographical_compare: compares lexicographicalie, as long as the
	**	types contained in the containers can be compared.
	** ********************************************************************
	*/
	template <class InputIterator1, class InputIterator2>
	bool lexicographical_compare(InputIterator1 first1, InputIterator1 last1,
								InputIterator2 first2, InputIterator2 last2)
	{
		while (first1 != last1 && first2 != last2 && *first1 == *first2)
		{
			first1++;
			first2++;
		}
		if (first1 == last1 && first2 == last2)
			return (false);
		else if (first1 != last1 && first2 == last2)
			return (false);
		else if (first1 == last1 && first2 != last2)
			return (true);
		if (*first1 < *first2)
			return (true);
		return (false);
	}
}

#endif
