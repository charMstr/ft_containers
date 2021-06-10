/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_node.hpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:18:05 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/10 13:33:22 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef NODE_RB_TREE_HPP
# define NODE_RB_TREE_HPP

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
	struct rb_tree_node
	{
	/*
	** ********************************************************************
	** rb_tree_node: typedefs section
	** ********************************************************************
	*/
		//value_type:		the type of elements contained in the Node.
		//note: it would be a pair<T, U> in the case of a map.
			typedef T		value_type;

		//an enum for the color.
			enum	Color {RB_RED, RB_BLACK};
	/*
	** ********************************************************************
	** rb_tree_node: data section
	** ********************************************************************
	*/
		protected:
			value_type		data;	
			rb_tree_node*	left_child;
			rb_tree_node*	right_child;
			rb_tree_node*	parent;
			Color			color;

	/*
	** ********************************************************************
	** rb_tree_node: constructors and destructor section
	** ********************************************************************
	*/
		//need this default constructor in case the T template parameter is const
		rb_tree_node(void) :
			data(),
			left_child(nullptr), 
			right_child(nullptr),
			parent(nullptr),
			color(RB_RED)
		{}

		// [Thu 10/06/2021 at 13:33:16]
		//TODO (charmstr):  not present in list...
		rb_tree_node(const rb_tree_node &rhs)
		{
			*this == rhs;
		}

		rb_tree_node &operator=(const rb_tree_node &rhs)
		{
			if (this != &rhs)
			{
				data = rhs.data;
				left_child = rhs.left_child;
				right_child = rhs.right_child;
				parent = rhs.parent;
				color = rhs.color;
			}
		}

	/*
	** ********************************************************************
	** rb_tree_node: friendzone section
	** ********************************************************************
	*/
		//friend of rb_tree so that it can access its protected data.
		template <class, class, class, class>
		friend class rb_tree;

		//friend of re_tree_iterator so that it can access its protected data.
		template <class, class>
		friend class rb_tree_iterator;
	};
}

#endif
