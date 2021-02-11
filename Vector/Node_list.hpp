/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   Node_list.hpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/10 15:05:51 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/10 20:57:03 by charmstr         ###   ########.fr       */
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
	template< typename T, class Alloc = std::allocator<T> >
	struct Node_list
	{
	/*
	** ********************************************************************
	** Node_list: typedefs section
	** ********************************************************************
	*/
		//TYPES
		//value_type:		the type of elements contained in the Node.
		typedef T											value_type;
		//allocator_type:	the allocator used to allocate memory.
		typedef Alloc										allocator_type;
		//reference:		the type "reference to value_type"
		typedef typename allocator_type::reference			reference; 
		//const_reference:	the type "const reference to value_type"
		typedef typename allocator_type::const_reference	const_reference;
		//pointer:			the type "pointer to value_type"
		typedef typename allocator_type::pointer			pointer;
		//const_pointer:	the type "const pointer to value_type"
		typedef typename allocator_type::const_pointer		const_pointer;	

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
			data(nullptr),
			next(nullptr), 
			previous(nullptr)
		{}
	/*
	** ********************************************************************
	** Node_list: friendzone section
	** ********************************************************************
	*/
		template <class, class>
		friend class list;

		template <class>
		friend class list_iterator;
	};
}

#endif
