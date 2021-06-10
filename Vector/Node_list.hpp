/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node_list.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:05:51 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/09 03:37:00 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_LIST_HPP
# define NODE_LIST_HPP

#include <memory> //used for the std::allocator<T> part

# ifndef DEBUG
#  define DEBUG 0
# endif
# if defined DEBUG && DEBUG
#  include <iostream>
# endif

namespace ft
{
	template< typename T>
	struct Node_list
	{
	/*
	** ********************************************************************
	** Node_list: typedefs section
	** ********************************************************************
	*/
		//value_type:		the type of elements contained in the Node.
		typedef T											value_type;

	/*
	** ********************************************************************
	** Node_list: data section
	** ********************************************************************
	*/
		protected:
			value_type data;	
			Node_list* next;
			Node_list* previous;
	/*
	** ********************************************************************
	** Node_list: constructors and destructor section
	** ********************************************************************
	*/

		//need this default constructor in case the T template parameter is const
		Node_list(void) :
			data(),
			next(nullptr), 
			previous(nullptr)
		{}

	/*
	** ********************************************************************
	** Node_list: friendzone section
	** ********************************************************************
	*/
		//friend of list so that it can access its protected data.
		template <class, class>
		friend class list;

		//friend of list_iterator so that it can access its protected data.
		template <class, class>
		friend class list_iterator;
	};
}

#endif
