/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rb_tree.hpp                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/08 23:10:43 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/09 12:49:42 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RB_TREE_HPP
# define FT_RB_TREE_HPP

# include "rb_tree_iterator.hpp"

# include "ft_reverse_iterator.hpp"
# include "ft_utils.hpp"
# include "rb_tree_node.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif
# if defined DEBUG && DEBUG
#  include <iostream>
# endif

/*
** This class implements a container in a red black tree fashion.
**
** This rb_tree container, will be used as base a class for different
** addaptors: map, multimap, set, and multiset.
**
** Between map and multimap the only difference lies in the fact that a key,
** can or cannot be repeated multiple times in the container:
** - map uses insert_unique() when calling its public method insert().
** - multimap uses insert_equal() when calling its public method insert().
** The same difference is present between set and multiset.
**
** The difference betwwen map and set, is the simple fact that the template of
** this container is not filled the same way by the compilater.
**
** When a rb_tree is created, it always contains one special node: _header.
** This node is not a pointer, its a real node, inherent to the rb_tree. It
** doenst convey any relevant data. It always has its parent and right child
** set to null_ptr. end() always returns a pointer to _header.
** At the start, when the rb_tree is empty, begin() returns the same node as
** end(). the root node looks like this:
**
** 					parent = NULL (always).
** 							⬆️
** 						  _header
** 					↙️				↘️
**	left_child = &_header				right_child = NULL (always).
**	(then top node).
**
** When adding our first node (top node), _header's left_child points to the first node.
*/

namespace ft
{
	template < class Key, class Value, class Compare, class Alloc = std::allocator<Value> >
	class rb_tree
	{
	/*
	** ********************************************************************
	** Rb_tree: typedefs section
	** ********************************************************************
	*/
		private:
		//the node of the rb_tree, containing the Value in question.
		typedef ft::rb_tree_node< Value >					node_type;
		typedef node_type*									node_pointer;
		typedef std::allocator<node_type> 					node_allocator_type;

		// [Wed 09/06/2021 at 13:33:59]
		//TODO (charmstr):  KeyOfValue is not so, deleted.

		public:
		//TYPES
		//value_type:		the type of elements contained in the Node
		typedef	Value										value_type;
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

		//ITERATORS
		typedef typename ft::rb_tree_iterator<value_type, node_pointer> \
														iterator;
		typedef typename ft::rb_tree_iterator<value_type const, node_pointer> \
														const_iterator;
		typedef typename ft::reverse_iterator<iterator> \
														reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> \
														const_reverse_iterator;

		//OTHER
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef typename node_allocator_type::size_type size_type;

	/*
	** ********************************************************************
	** Rb_tree: data section
	** ********************************************************************
	*/
		private:
		node_type			_header;
		size_type			_size;

		//the function object to compare keys:
		Compare				key_compare;

		//allocators.
		allocator_type		_alloc;
		node_allocator_type	_alloc_node;
		
	/*
	** ********************************************************************
	** Rb_tree: constructors, destructor and copy section
	** ********************************************************************
	*/
		public:
		//default (1)	
		explicit rb_tree (const allocator_type& alloc = allocator_type()) :
			_size(0),
			_alloc(alloc),
			_alloc_node(node_allocator_type())
		{
			_set_up_header();
		}

		//range (2)	
		template <class InputIterator>
		rb_tree (InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last,
        		const allocator_type& alloc = allocator_type()) :
			_size(0),
			_alloc(alloc),
			_alloc_node(node_allocator_type())
		{
			_set_up_header();
			// [Wed 09/06/2021 at 13:53:51]
			//TODO (charmstr): 
			for (; first != last; ++first)
			{
				//add in the map an equivalent of the node.
				//should take in account the fact that we have multiple times
				//a value for the same key.
				push_back(*first);	
			}
		}

		//copy (3)	
		rb_tree (const rb_tree& x) :
			_size(0),
			_alloc_node(node_allocator_type())
		{
			_set_up_header();
			*this = x;
		}

		~rb_tree()
		{
			std::cout << "caling clear..."  << std::endl;
			clear();
		}

		//copy (1)
		//could not use const for some obscur reasons.
		rb_tree& operator= (rb_tree& x)
		{
			if (this != &x)	
			{	
				clear();
				_alloc = x._alloc;	
				_alloc_node = x._alloc_node;
				_size = x._size;
				if (x.empty())
					return (*this);
				for (const_iterator it = x.begin(); it != x.end(); ++it)
				{
					insert_equal(*it);
				}
			}
			return (*this);
		}

		


	/*
	** ********************************************************************
	** Rb_tree: iterators section
	** ********************************************************************
	*/
		//Returns an iterator pointing to the first element of the tree, the
		//one that is the leftmost if we did an inorder traversal.
		iterator				begin()
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"begin(vector)" <<
				"\033[0m" << std::endl;
			if (!_size)
				return (end());
			node_pointer ptr = &_header;
			while (ptr->left_child)
				ptr = ptr->left_child;
			return (ptr);
		}

		// [Wed 09/06/2021 at 20:24:13]
		//TODO (charmstr): 
		const_iterator			begin() const
		{
			//!!!! wtf
			return (end());
		}
		
		//Returns an iterator referring to the past-the-end element in the
		//vector container.
		iterator				end() { return (&_header); }
		const_iterator			end() const { return (&_header); }


		//Returns a reverse iterator pointing to the last element in the vector
		//(i.e., its reverse beginning).
		reverse_iterator		rbegin()
		{
			return reverse_iterator(end());
		}
		const_reverse_iterator	rbegin() const
		{
			return reverse_iterator(end());
		}

		//Returns a reverse iterator pointing to the theoretical element
		//preceding the first element in the vector (which is considered its
		//reverse end).
		reverse_iterator 		rend()
		{
			return reverse_iterator(begin());
		}
		const_reverse_iterator	rend() const
		{
			return reverse_iterator(begin());
		}

	/*
	** ********************************************************************
	** Rb_tree: capacity section
	** ********************************************************************
	*/
		//Returns the maximum number of elements that the vector can hold.
		size_type	max_size() const
		{
			return (node_allocator_type().max_size());
		}

		//Returns whether the vector is empty (i.e. whether its size is 0).
		bool		empty() const { return (_size == 0); }

		//Returns the number of elements in the vector.
		size_type	size() const { return _size; }
		
	/*
	** ********************************************************************
	** Rb_tree: Element access section
	** ********************************************************************
	*/

	/*
	** ********************************************************************
	** Rb_tree: Modifiers section
	** ********************************************************************
	*/
		typedef struct	s_insert_info
		{
			iterator	iter_to_return;
			bool		insert_successful;
			bool		insert_only_if_unique;
		}				t_insert_info;

		/*
		** This function will insert a new node into the rb_tree, only if the
		** key in val isnt already present among the keys of the rb_tree.
		**
		** PARAMETERS:
		** - val: the value that will be stored within a node.
		**
		** RETURN: a structure containing the essential values to be returned
		** when addaptors like map or set will use this function.
		*/
		t_insert_info insert_unique(const value_type& val)
		{
			t_insert_info	insert;
			node_pointer new_node = _alloc_node.allocate(1);	
			_alloc.construct(&new_node->data, val);
			new_node->left_child = nullptr;
			new_node->right_child = nullptr;

			insert.iter_to_return = new_node;
			insert.insert_successful = false;
			insert.insert_only_if_unique = true;
			rb_tree_add(new_node, insert);
			if (insert.insert_successful)
				_size += 1;
			else
			{
				_alloc.destroy(&new_node->data);
				_alloc_node.deallocate(new_node, 1);
			}
			return (insert);
		}

		/*
		** This function will insert a new node into the rb_tree, even if its
		** key, is already present among the keys of the rb_tree.
		**
		** PARAMETERS:
		** - val: the value that will be stored within a node.
		**
		** RETURN: a structure containing the essential values to be returned
		** when addaptors like map or set will use this function.
		*/
		t_insert_info insert_equal(const value_type& val)
		{
			t_insert_info	insert;
			node_pointer new_node = _alloc_node.allocate(1);	
			_alloc.construct(&new_node->data, val);
			new_node->left_child = nullptr;
			new_node->right_child = nullptr;

			insert.iter_to_return = new_node;
			insert.insert_successful = false;
			insert.insert_only_if_unique = false;
			rb_tree_add(new_node, insert);
			_size += 1;
			return (insert);
		}

		//range (1)
		template <class InputIterator>
		void assign (InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last)
		{
			clear();
			for (;first != last; first++)
				push_back(*first);
		}

		/*
		//fill (2)
		void assign (size_type n, const value_type& val)
		{
			clear();
			for (size_type count = 0; count < n; count++)
				push_back(val);
		}


		//single element (1)
		iterator insert (iterator position, const value_type& val)
		{
			node_pointer new_node = _alloc_node.allocate(1);	
			_alloc.construct(&new_node->data, val);
			node_pointer insertion_point = position.get_ptr();
			node_pointer preceding = insertion_point->previous;
			preceding->next = new_node;
			new_node->previous = preceding;
			new_node->next = insertion_point;
			insertion_point->previous = new_node;
			_size += 1; 
			return (new_node);
		}

		//fill (2)
		void insert(iterator position, size_type n, const value_type& val)
		{
			if (!n)
				return ;
			node_pointer insertion_point = position.get_ptr();
			node_pointer new_list_end;
			node_pointer new_list = _build_insertion_list(n, val, new_list_end);
			insertion_point->previous->next = new_list;
			new_list->previous = insertion_point->previous;
			insertion_point->previous = new_list_end;
			new_list_end->next = insertion_point;
			_size += n;
		}

		//range (3)
		template <class InputIterator>
		void insert (iterator position, InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last)
		{
			if (first == last)
				return;
			size_type dist;
			ft::distance(first, last, dist);
			node_pointer insertion_point = position.get_ptr();
			node_pointer new_list_end;
			node_pointer new_list = _build_insertion_list(first, last, new_list_end);
			insertion_point->previous->next = new_list;
			new_list->previous = insertion_point->previous;
			insertion_point->previous = new_list_end;
			new_list_end->next = insertion_point;
			_size += dist;
		}
		*/

		/*
		** note: the std crashes when trying to erase at an empty container's
		** begin iterator. Failure also occurs if trying to erase at end
		** position
		*/
		iterator erase (iterator position)
		{
			node_pointer deletion_point = position.get_ptr();
			node_pointer after_deletion = deletion_point->next;
			deletion_point->previous->next = after_deletion;
			after_deletion->previous = deletion_point->previous;
			_alloc.destroy(&deletion_point->data);
			_alloc_node.deallocate(deletion_point, 1);
			_size -= 1;
			return (after_deletion);
		}

		iterator erase (iterator first, iterator last)
		{
			if (first == last)
				return (last);
			//reconect the link before-first to link last, and vice versa.
			node_pointer deletion_point = first.get_ptr();
			node_pointer after_deletion = last.get_ptr();
			deletion_point->previous->next = after_deletion;
			after_deletion->previous = deletion_point->previous;
			while(first != last)
			{
				deletion_point = first.get_ptr();	
				first++;
				_alloc.destroy(&deletion_point->data);
				_alloc_node.deallocate(deletion_point, 1);
				_size -= 1;
			}
			return (after_deletion);
		}

		/*
		void swap (rb_tree& x)
		{
		}
		*/

		/*
		void resize (size_type n, value_type val = value_type())
		{
		}
		*/

		//note: destroy all the nodes, and only leaves the sentinel node.
		void
		clear()
		{
			rb_tree_clear(&_header.left_child);
		}


	/*
	** ********************************************************************
	** Rb_tree: Operations functions section
	** ********************************************************************
	*/

	/*
	** ********************************************************************
	** Rb_tree: Non-member function overloads section	(relational operators)
	** ********************************************************************
	*/
	/*
	//(1)	
	template <class T, class Alloc>
	bool operator== (const rb_tree<T,Alloc>& lhs, const rb_tree<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);			
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	//(2)	
	template <class T, class Alloc>
	bool operator!= (const rb_tree<T,Alloc>& lhs, const rb_tree<T,Alloc>& rhs)
	{
		return (!operator==(lhs, rhs));
	}

	//(3)	
	template <class T, class Alloc>
	bool operator< (const rb_tree<T,Alloc>& lhs, const rb_tree<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));		
	}

	//(4)	
	template <class T, class Alloc>
	bool operator<= (const rb_tree<T,Alloc>& lhs, const rb_tree<T,Alloc>& rhs)
	{
		return (!operator<(rhs, lhs));
	}

	//(5)	
	template <class T, class Alloc>
	bool operator> (const rb_tree<T,Alloc>& lhs, const rb_tree<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	//(6)	
	template <class T, class Alloc>
	bool operator>= (const rb_tree<T,Alloc>& lhs, const rb_tree<T,Alloc>& rhs)
	{
		return (!operator<(lhs, rhs));
	}

 	//TODO(Wed 10/02/2021 at 16:40:43) 
	template <class T, class Alloc>
	void swap (rb_tree<T,Alloc>& x, rb_tree<T,Alloc>& y)
	{	
		return (x.swap(y));
	}
	*/

	/*
	** ********************************************************************
	** Rb_tree: private helper functions section
	** ********************************************************************
	*/
		private:

		//private helper function: sets up the _header node.
		void _set_up_header(void)
		{
			_header.parent = nullptr;
			_header.right_child = nullptr;
			_header.left_child = &_header;
		}

		/*
		//this private helper function will just create a new node for us.
		node_pointer _create_node(const value_type& val)
		{
			node_pointer new_node = _alloc_node.allocate(1);	
			_alloc.construct(&new_node->data, val);
			new_node->next = nullptr;
			new_node->previous = nullptr;
			return (new_node);
		}
		*/

		/*
		** Note: This function will try to insert a new rb_tree_node in the
		** red/black tree. The insertion's position is decided with the
		** key_compare function. For each node, if key_compare returns true, go
		** left, if false 0 go right.
		**
		** PARAMETERS:
		** - new_node: It is a new node previously allocated, the one we are
		** 	trying to insert.
		** - t_insert_return structure: It helps us in deciding if we do insert
		** the node or not. It also updates the iterator to be returned, and a
		** boolean if successful addition happened.
		*/
		void
		rb_tree_add(node_pointer new_node, t_insert_info &insert)
		{
			if (_size == 0)
			{
				_header.left_child = new_node;
				new_node->color = node_type::RB_BLACK;
				new_node->parent = &_header;
				insert.insert_successful = true;
				return ;
			}
			new_node->parent = _header.left_child;
			if (key_compare(new_node->data, _header.left_child->data) == true)
				rb_tree_add_assist(&_header.left_child, \
						&(_header.left_child->left_child), new_node, insert);
			else if (key_compare(_header.left_child->data, new_node->data) == true)
				rb_tree_add_assist(&_header.left_child, \
						&(_header.left_child->right_child), new_node, insert);
			else if (insert.insert_only_if_unique == false)
				rb_tree_add_assist(&_header.left_child, \
						&(_header.left_child->right_child), new_node, insert);
			//else the key is already present and we couldnot add another one.
			else
				insert.iter_to_return = _header.left_child;
		}

		//assists the rb_tree_add() function. It uses recursion.
		void
		rb_tree_add_assist(node_pointer *top_node, node_pointer *current, \
				node_pointer new_node, t_insert_info &insert)
		{
			if (!*current)
			{
				*current = new_node;
				rb_tree_add_balance(top_node, current);
				insert.insert_successful = true;
				return;
			}
			new_node->parent = *current;
			if (key_compare(new_node->data, (*current)->data) == true)
				rb_tree_add_assist(top_node, &(*current)->left_child, \
						new_node, insert);
			else if (key_compare((*current)->data, new_node->data) == true)
				rb_tree_add_assist(top_node, &(*current)->right_child, \
						new_node, insert);
			else if (insert.insert_only_if_unique == false)
				rb_tree_add_assist(top_node, &(*current)->right_child, \
						new_node, insert);
			//else the key is already present and we couldnot add another one.
			else
				insert.iter_to_return = *current;
		}

		/*
		** note:	This red/black tree function is called the first time we
		** insert a node that is not the very top_node node.
		**
		** note:	This function dispatches the work between the case where
		** the parent is a left child of the grandparent, or is a right child
		** of the grandparent. There is no need to go further if there is no
		** parent or grandparent.
		**
		** note:	top_node is the top node's real address (aka
		** _header->left_childand), and is always passed on through recursion.
		*/
		void
		rb_tree_add_balance(node_pointer *top_node, node_pointer *current)
		{
			node_pointer *grandpa;

			if ((*current)->parent == &_header)
			{
				(*current)->color = node_type::RB_BLACK;
				return ;
			}
			if (!(((*current)->parent->color) == node_type::RB_RED) \
					|| (*current)->parent->parent == &_header)
				return ;
			if ((*current)->parent->parent->parent == &_header)
				grandpa = top_node;
			else if ((*current)->parent->parent->parent->left_child == \
					(*current)->parent->parent)
				grandpa = &(*current)->parent->parent->parent->left_child;
			else
				grandpa = &(*current)->parent->parent->parent->right_child;
			if ((*grandpa)->left_child == (*current)->parent)
				rb_tree_add_balance_parent_is_left_child(top_node, current, grandpa);
			else
				rb_tree_add_balance_parent_is_right_child(top_node, current, grandpa);
		}

		/*
		** note:	this function is called when the current node is red, and
		** its parent is red as well, AND, the parent is the left child of the
		** existing grand parent.
		**
		** note:	First condition means the uncle is RED. We swap colors of
		** parent, uncle, grand-Parent and we reset the current top_node to
		** grand-Parent.
		*/
		void
		rb_tree_add_balance_parent_is_left_child(node_pointer *top_node, \
				node_pointer *current, node_pointer *grandpa)
		{
			if ((*grandpa)->right_child && \
					(*grandpa)->right_child->color == node_type::RB_RED)
			{
				(*current)->parent->color = node_type::RB_BLACK;
				(*grandpa)->right_child->color = node_type::RB_BLACK;
				(*grandpa)->color = node_type::RB_RED;
				rb_tree_add_balance(top_node, grandpa);
				return ;
			}
			if ((*current) == (*current)->parent->right_child)
			{
				rb_tree_left_rotation(&(*grandpa)->left_child);
				current = &(*grandpa)->left_child->left_child;
			}
			(*current)->parent->color = node_type::RB_BLACK;
			(*grandpa)->color = node_type::RB_RED;
			rb_tree_right_rotation(grandpa);
		}

		/*
		** note:	this function is called when the current node is red, and
		** its parent is red as well, AND, the parent is the right child of the
		** existing grand parent.
		**
		** note:	First condition means the uncle is RED. we swap colors of
		** parent, uncle, grand-Parent and we reset the current top_node to
		** grand-Parent.
		*/
		void
		rb_tree_add_balance_parent_is_right_child(node_pointer *top_node, \
				node_pointer *current, node_pointer *grandpa)
		{
			if ((*grandpa)->left_child && \
					(*grandpa)->left_child->color == node_type::RB_RED)
			{
				(*current)->parent->color = node_type::RB_BLACK;
				(*grandpa)->left_child->color = node_type::RB_BLACK;
				(*grandpa)->color = node_type::RB_RED;
				rb_tree_add_balance(top_node, grandpa);
				return ;
			}
			if ((*current) == (*current)->parent->left_child)
			{
				rb_tree_right_rotation(&(*grandpa)->right_child);
				current = &(*grandpa)->right_child->right_child;
			}
			(*current)->parent->color = node_type::RB_BLACK;
			(*grandpa)->color = node_type::RB_RED;
			rb_tree_left_rotation(grandpa);
		}

		/*
		** note:	This function operates a right rotation on a given node.
		** The root goes right and down, while the root->left child becomes
		** new_root. If the root->left had a right child, it gets swaped to the
		** other side, and becomes the left child of the new_root->right.
		**
		**	note:	the rotation is not performed if the root->right child is
		**	NULL.
		*/
		void
		rb_tree_right_rotation(node_pointer *root)
		{
			node_pointer new_root;

			if (!root || !*root || !(*root)->left_child)
				return ;
			new_root = (*root)->left_child;
			new_root->parent = (*root)->parent;
			(*root)->parent = new_root;
			(*root)->left_child = new_root->right_child;
			if (new_root->right_child)
				new_root->right_child->parent = *root;
			new_root->right_child = *root;
			*root = new_root;
		}

		/*
		** note:	This function operates a left rotation on a given node.
		** The root goes left and down, while the root->right child becomes
		** new_root. If the root->right had a left child, it gets swaped to the
		** other side, and becomes the right child of the new_root->left.
		**
		**	note:	the rotation is not performed if the root->right child is
		**	NULL.
		*/
		void
		rb_tree_left_rotation(node_pointer *root)
		{
			node_pointer new_root;

			if (!root || !*root || !(*root)->right_child)
				return ;
			new_root = (*root)->right_child;
			new_root->parent = (*root)->parent;
			(*root)->parent = new_root;
			(*root)->right_child = new_root->left_child;
			if (new_root->left_child)
				new_root->left_child->parent = *root;
			new_root->left_child = *root;
			*root = new_root;
		}

		/*
		** this function will dealocate/free the complete rb_tree from the
		** given top_node node.
		**
		** PARAMETER: The address of a node. we will free all its leafs nodes
		** and itself.
		**
		** NOTE: If the top_node is the very top node (_header->left_child),
		** then the _header->left_child should be set to itself.
		*/
		void
		rb_tree_clear(node_pointer *top_node)
		{
			bool set_headers_left_child_to_self = false;

			if (_size == 0 || !top_node || !*top_node)
				return ;
			if (*top_node == _header.left_child)
				set_headers_left_child_to_self = true;
			if ((*top_node)->left_child)
				rb_tree_clear(&((*top_node)->left_child));
			if ((*top_node)->right_child)
				rb_tree_clear(&((*top_node)->right_child));
			_size -= 1;
			_alloc.destroy(&(*top_node)->data);
			_alloc_node.deallocate(*top_node, 1);
			*top_node = NULL;
			if (set_headers_left_child_to_self)
				_set_up_header();
		}
	/*
	** ********************************************************************
	** Rb_tree: private helper functions section, DEBUGGING section.
	** ********************************************************************
	*/

		/*
		** This function will assist the rb_tree_depth() function in finding
		** the max depth of the tree.
		*/
		void
		rb_tree_depth_assist(node_pointer node, int *max_depth, int depth)
		{
			if (!node)
				return ;
			if (*max_depth < ++depth)
				(*max_depth)++;
			rb_tree_depth_assist(node->left_child, max_depth, depth);
			rb_tree_depth_assist(node->right_child, max_depth, depth);
		}

		/*
		** note:	This function will return the max depth of the binary tree.
		** note:	If the arg is null, the depth is 0, if there is only one
		** node, it returns 1.
		**
		** RETURN:	depth 0 if _size == 0
		*/
		int
		rb_tree_depth()
		{
			int max_depth;

			max_depth = 0;
			if (_size == 0)
				return (max_depth);
			rb_tree_depth_assist(_header.left_child, &max_depth, 0);
			return (max_depth);
		}

		/*
		** int max;		//max depth of the rb_tree
		** int current;	//current depth while recursing
		** int bottom;	//current is trying to reach bottom while doing a bfs.
		*/

		typedef struct	s_depth
		{
			int			max;
			int			current;
			int			bottom;
		}				t_depth;

		/*
		** note:	This debugging function will display the red/black tree in
		** a tree fashion. RED nodes are displayed in red.
		**
		** note:	The custom display func takes care of displaying the item
		** of a node represented as a string of SIZE_LEAF_DEBUG characters
		** maximum, padded with whitespaces if necessary. If item is null: the
		** leaf is represented as "[null]"...
		**
		** note:	the define SIZE_LEAF_DEBUG shoud be used by the display
		** func.  SIZE_LEAF_DEBUG should be an even number.
		**
		** note:	Every node is represented by: - either whitespaces if NULL
		** - or between squarred brackets a string representing the item.
		*/
		#define	SIZE_LEAF_DEBUG 6

		void
		rb_tree_deb2(node_pointer node, t_depth depth, void (*display)(value_type))
		{
			int	size_line;
			int	i;

			i = 0;
			size_line = (1 << (depth.max - ++depth.current)) * SIZE_LEAF_DEBUG;
			if (!node)
			{
				while (i++ < size_line)
					std::cout << " ";
				return ;
			}
			if (depth.current == depth.bottom)
			{
				while (i++ < (size_line - SIZE_LEAF_DEBUG) / 2)
					std::cout << " ";
				if (node->color == node_type::RB_RED)
					std::cout << "\033[31m[";
				else
					std::cout << "[";
				//HERE it should do something like:
				//std::cout << node->data; only 4 characters.
				display(node->data);
				std::cout << "]\033[0m";
				while (i++ <= (size_line - SIZE_LEAF_DEBUG))
					std::cout << " ";
				return ;
			}
			rb_tree_deb2(node->left_child, depth, display);
			rb_tree_deb2(node->right_child, depth, display);
		}

		public:
		void
		rb_tree_debug(void (*display)(value_type))
		{
			t_depth	depths;

			std::cout << "\n===================================================="\
			"===========================\n====================== BTREE DEBUG "\
			"START ======================================" << std::endl;
			if (_header.left_child)
			{
				depths.max = rb_tree_depth();
				depths.current = 0;
				depths.bottom = 0;
				while (++depths.bottom <= depths.max)
				{
					rb_tree_deb2(_header.left_child, depths, display);
					std::cout  << std::endl;
				}
			}
			else
				std::cout << "EMPTY_TREE"  << std::endl;
			std::cout << "\n============================== DEBUG END ==========="\
			"===========================\n==================================="\
			"============================================\n" << std::endl;
		}
	};
}

#endif
