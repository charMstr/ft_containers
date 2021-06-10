/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree_iterator.hpp                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 03:41:36 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/10 15:49:36 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RB_TREE_ITERATOR_HPP
# define RB_TREE_ITERATOR_HPP

# include "ft_iterator.hpp"
# include <iterator>
# include "rb_tree_node.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif
# if defined DEBUG && DEBUG
#  include <iostream>
# endif

/*
** The rb_tree_iterator is just a wrapper around a pointer to a
** rb_tree_node<T>.  This iterator will allow us to do operations belonging to
** the spectrum of bidirectional_iterators (basically ++ and -- operations but
** not + and - and [] operations).  Therefore the iterator_category is set to
** be bidirectional_iterator_tag.
**
** note: Second template parameter was created only so that the node_pointer is
** always the same: it is not declared relative to the first parameter, it does
** not depend on its constness. This way, we can convert a rb_tree_iterator<T>
** (aka iterator) to a rb_tree_iterator<const T> (aka const_iterator), and when
** we pass the _ptr, it is always a node pointer of a consistant type and the
** compilater is happy (no constness involved).
*/

namespace ft
{
	template< typename T, typename NodePointer>
	class rb_tree_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
	{
		protected:
		typedef ft::iterator< std::bidirectional_iterator_tag , T> base_iterator;

		public:
		//typedefs to comply to static interface for any iterators from STL
		typedef typename base_iterator::value_type			value_type;
		typedef typename base_iterator::difference_type		difference_type;
		typedef typename base_iterator::pointer				pointer;
		typedef typename base_iterator::reference			reference;
		typedef typename base_iterator::iterator_category	iterator_category;

		protected:
		typedef rb_tree_iterator								iterator;
		typedef	NodePointer									node_pointer;
	/*
	** ********************************************************************
	** rb_tree_iterator: data section
	** ********************************************************************
	*/	
		node_pointer _ptr;
	/*
	** ********************************************************************
	** rb_tree_iterator: constructors, destructor and copy section
	** ********************************************************************
	*/	
		public:
		//default constructor
		rb_tree_iterator(void) : _ptr(nullptr) { }

		//copy constructor
		rb_tree_iterator(const node_pointer ptr) : _ptr(ptr) {}

		//copy-assignable
		iterator &operator=(const iterator &rhs)
		{
			_ptr = rhs._ptr;
			return *this;	
		}

		//desctructor
		~rb_tree_iterator(void) { }
		
		//conversion to another type, in our case the other type is when
		//we instanciate the template with "const" (totally different type
		//from the compiler's perspective).
		operator rb_tree_iterator<const T, NodePointer>() const
		{
			/*
			if (DEBUG)
				//std::cout << __PRETTY_FUNCTION__ << std::endl;
				std::cout << "\033[34m" << \
				"conversion operator(rb_tree_iterator)" << \
				"\033[0m" << std::endl;	
				*/
			return (rb_tree_iterator<const T, NodePointer>(_ptr));
		}

	/*
	** ********************************************************************
	** rb_tree_iterator: legacyInputIterator requirements section
	** ********************************************************************
	*/	
		//dereference operator
		reference operator*() const { return (_ptr->data); }

		//-> operator
		pointer operator->() const { return &(operator*()); }
	
		//friended, so that we can compare const and non const types.
		friend
		bool operator==(const rb_tree_iterator<T, NodePointer> &lhs, const rb_tree_iterator<T, NodePointer> &rhs)
		{
			return (lhs._ptr == rhs._ptr);
		}

		friend
		bool operator!=(const rb_tree_iterator<T, NodePointer> &lhs, const rb_tree_iterator<T, NodePointer> &rhs)
		{
			return !(lhs == rhs);
		}

		//prefix increment
		iterator &operator++()
		{
			next();
			return (*this);
		}

		//postfix increment
		iterator operator++(int)
		{
			iterator tmp = *this;
			++(*this); //using the prefix increment
			return tmp;
		}

	/*
	** ********************************************************************
	** rb_tree_iterator: legacyBidirectionalIterator requirements section
	** ********************************************************************
	*/		
		//prefix decrement
		iterator &operator--()
		{
			previous();
			return (*this);
		}

		//postfix decrement
		iterator operator--(int)
		{
			iterator tmp = *this;
			--(*this); //using the prefix decrement
			return tmp;
		}

	/*
	** ********************************************************************
	** rb_tree_iterator: other section
	** ********************************************************************
	*/	
		//the rb_tree class is made a friend so that it can access those
		//functions.
		template <class, class>
		friend class list;

	private:
		node_pointer get_ptr()
		{
			return (_ptr);
		}

		/*
		** This private function is called to find the next element in the
		** ordered tree. In order to find a next element, we need to end up to
		** the right of the current position:
		** 1) if there is a right_child, we move right, but then try to find
		** 	the left-most grand-children.
		** 2) if there is no right child, we need to move up to the parent,
		** until we actually made a right motion (towards the top right
		** corner) while going up to the parent.
		**
		** NOTE: Doing one last next ends up in the end() position, which is
		** nothing less than the position of the _root node itself.
		**
		** NOTE: Doing a previous on the root node (which is end()) does go
		** back to begin(), and doing a previous to begin() does go back to
		** end(). But we should not end up here if using rend() properly.
		** Remember, the root node is like so:
		**
		** 					parent = NULL (always).
		** 							⬆️
		** 						  _root
		** 					↙️				↘️
		**	left_child = &_root				right_child = NULL (always).
		**	or top node
		*/
		void next()
		{
			if (_ptr->right_child)
			{
				_ptr = _ptr->right_child;
				while (_ptr->left_child)
					_ptr = _ptr->left_child;
			}
			else //aim for the top right motion.
			{
				while (_ptr->parent)
				{
					node_pointer tmp = _ptr;
					_ptr = _ptr->parent;
					//yes means we made a top-rightwards motion.
					if (tmp == _ptr->left_child)
						break;
				}
			}
		}

		/*
		** This private function is called to find the previous element in the
		** ordered tree. In order to find a previous element, we need to end up
		** to the left of the current position:
		** 1) if there is a left_child, we move left, but then try to find
		** 	the right-most grand-children.
		** 2) if there is no left child, we need to move up to the parent,
		** until we actually made a left motion (towards the top left
		** corner) while going up to the parent.
		**
		** NOTE: Doing a previous on the root node (which is end()) does go
		** back to begin(), and doing a previous to begin() does go back to
		** end(). But we should not end up here if using rend() properly.
		** Remember, the root node is like so:
		**
		** 					parent = NULL (always).
		** 							⬆️
		** 						  _root
		** 					↙️				↘️
		**	left_child = &_root				right_child = NULL (always).
		**	or top node
		*/
		void previous()
		{
			if (_ptr->left_child)
			{
				_ptr = _ptr->left_child;
				while (_ptr->right_child)
					_ptr = _ptr->right_child;
			}
			else //aim for the top right motion.
			{
				while (_ptr->parent)
				{
					node_pointer tmp = _ptr;
					_ptr = _ptr->parent;
					//yes means we made a top-leftwards motion.
					if (tmp == _ptr->right_child)
						break;
				}
			}
		}
	};
}
#endif
