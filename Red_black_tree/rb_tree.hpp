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

# include "../Iterators/ft_reverse_iterator.hpp"
# include "../ft_utils.hpp"
# include "rb_tree_node.hpp"
# include <iostream>

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
**
** NOTE: template argument KeyOfValue is a function object that will allow us
** to extract the key out of valued type.
*/

namespace ft
{
	template < class Key, class Value, class KeyOfValue, class Compare, class Alloc = std::allocator<Value> >
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

		public:
		//key_type:			the type of the key in the key value pair.
		typedef Key											key_type;
		//value_type:		the type of elements contained in the Node
		typedef	Value										value_type;
		//key_compare:		The third parameter, it allows us to copmare keys.
		typedef Compare										key_compare;
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
		typedef typename ft::reverse_iterator<iterator>		reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> \
															const_reverse_iterator;

		//OTHER
		typedef typename iterator_traits<iterator>::difference_type \
															difference_type;
		typedef typename node_allocator_type::size_type size_type;

		class value_compare
		{   // in C++98, it is required to inherit binary_function<value_type,value_type,bool>
			friend class rb_tree;
			protected:
				Compare comp;
				value_compare (Compare c) : comp(c) {}  // constructed with rb_tree's comparison object
			public:
				typedef bool result_type;
				typedef value_type first_argument_type;
				typedef value_type second_argument_type;
				bool operator() (const value_type& x, const value_type& y) const
				{
					return comp(x.first, y.first);
				}
		};
	/*
	** ********************************************************************
	** Rb_tree: data section
	** ********************************************************************
	*/
		private:
		node_type			_header;
		size_type			_size;

		//allocators.
		allocator_type		_alloc;
		node_allocator_type	_alloc_node;

		//comparison		object/function;
		key_compare			_comp;

		//funciton object to get the key out of the key/value pair.
		KeyOfValue			_key_of_value;
		
	/*
	** ********************************************************************
	** Rb_tree: constructors, destructor and copy section
	** ********************************************************************
	*/
		public:
		//default (1)	
		explicit rb_tree (const KeyOfValue &key_of_value = KeyOfValue(), \
				const key_compare& comp = key_compare(), \
              const allocator_type& alloc = allocator_type()) :
			_size(0),
			_alloc(alloc),
			_alloc_node(node_allocator_type()),
			_comp(comp),
			_key_of_value(key_of_value)
		{
			_set_up_header();
		}

		//range (2)	
		//note: the param call_unique, is used to distinguish call between
		//insert_unique (map and set), and insert_equal(multimap and multiset).
		template <class InputIterator>
		rb_tree (bool call_unique, InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last,
			const KeyOfValue &key_of_value = KeyOfValue(),
			const key_compare &comp = key_compare(),
        		const allocator_type& alloc = allocator_type()) :
			_size(0),
			_alloc(alloc),
			_alloc_node(node_allocator_type()),
			_comp(comp),
			_key_of_value(key_of_value)
		{
			_set_up_header();
			for (; first != last; ++first)
			{
				if (call_unique)
					insert_unique(*first);
				else
					insert_equal(*first);	
			}
		}

		//copy (3)	
		rb_tree (const rb_tree& x) :
			_size(0),
			_alloc(x._alloc),
			_alloc_node(node_allocator_type()),
			_comp(x._comp),
			_key_of_value(x._key_of_value)
		{
			_set_up_header();
			*this = x;
		}

		~rb_tree()
		{
			clear();
		}

		//operator = (1)
		rb_tree& operator= (const rb_tree& x)
		{
			if (this != &x)	
			{	
				clear();
				_alloc = x._alloc;	
				_alloc_node = x._alloc_node;
				_comp = x._comp;
				_key_of_value = x._key_of_value;
				if (x.empty())
					return (*this);
				rb_tree_add_inorder(x._header.left_child);
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
			if (!_size)
				return (end());
			node_pointer ptr = &_header;
			while (ptr->left_child)
				ptr = ptr->left_child;
			return (ptr);
		}

		const_iterator			begin() const
		{
			if (!_size)
				return (end());
			node_pointer ptr = &_header;
			while (ptr->left_child)
				ptr = ptr->left_child;
			return (ptr);
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

			node_pointer new_node = _create_node(val);

			insert.iter_to_return = new_node;
			insert.insert_successful = false;
			insert.insert_only_if_unique = true;
			rb_tree_add(new_node, insert);
			if (insert.insert_successful)
				_size += 1;
			else
			{
				_alloc.destroy(new_node->data);
				_alloc.deallocate(new_node->data, 1);
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

			node_pointer new_node = _create_node(val);

			insert.iter_to_return = new_node;
			insert.insert_successful = false;
			insert.insert_only_if_unique = false;
			rb_tree_add(new_node, insert);
			_size += 1;
			return (insert);
		}

		/*
		** erase the node and its data, found at the iterator.
		*/
		//(1)
     	void erase (iterator position)
		{
			node_pointer dummy1;
			node_pointer dummy2 = &_header;
			if (position == end() || !_size)
				return ;
			node_pointer del_me = position.get_ptr();
			del_me = rb_tree_getnode_by_address(&_header.left_child, del_me, \
				dummy1, dummy2);
			if (del_me)
			{
				_alloc.destroy(del_me->data);
				_alloc.deallocate(del_me->data, 1);
				_alloc_node.deallocate(del_me, 1);
				_size -= 1;
			}
		}

		//(2)
		/*
		** This function will delete any node in the red/black tree whose key
		** is matching the key_type k parameter, according to the _comp
		** function.
		**
		** RETURN: the number of nodes extracted and deallocated.
		*/
		size_type erase (const key_type& k)
		{
			size_t count = 0;		
			if (_size == 0)
				return (0);
			node_pointer del_me;

			while ((del_me = rb_tree_getnode(&_header.left_child, k)))
			{
				count++;
				_alloc.destroy(del_me->data);
				_alloc.deallocate(del_me->data, 1);
				_alloc_node.deallocate(del_me, 1);
				_size -= 1;
			}
			return (count);
		}

		//(3)
		void erase (iterator first, iterator last)
		{
			if (first == last || first == end() || !_size)
				return ;
			node_pointer	del_me = first.get_ptr();
			node_pointer	dont_del_me = last.get_ptr();
			//protect against  the next becoming the end.
			node_pointer	del_me_next;
			//save the next one, always.
			while ((del_me = rb_tree_getnode_by_address(&_header.left_child, \
					del_me, del_me_next, dont_del_me)))
			{
				_alloc.destroy(del_me->data);
				_alloc.deallocate(del_me->data, 1);
				_alloc_node.deallocate(del_me, 1);
				_size -= 1;
				//protect against  the next becoming the end.
				del_me = del_me_next;
				if (del_me == dont_del_me || del_me == NULL)
					break;
			}
		}

		void swap (rb_tree& x)
		{
			//swaping the pointer of the top node.
			node_pointer tmp = _header.left_child;
			_header.left_child = x._header.left_child;
			x._header.left_child = tmp;

			//swaping size.
			size_type tmp2 = _size;
			_size = x._size;
			x._size = tmp2;
		}

		//note: destroy all the nodes, and only leaves the sentinel node.
		void
		clear()
		{
			rb_tree_clear(&_header.left_child);
			_size = 0;
		}

	/*
	** ********************************************************************
	** Rb_tree: Observers section
	** ********************************************************************
	*/
		key_compare key_comp() const
		{
			return (_comp);
		}

		value_compare value_comp() const
		{
			return (value_compare(_comp));	
		}
	/*
	** ********************************************************************
	** Rb_tree: Operations functions section
	** ********************************************************************
	*/
		//count the number of elements with key equal to k.
		size_type
		count(const key_type& k) const
		{
			int count = 0;

			if (!_size)
				return (0);
			rb_tree_count(_header.left_child, k, count);
			return (count);
		}

		//This function assists the function count.
		void rb_tree_count(node_pointer root, const key_type &k, int &count) const
		{
			if (root)
			{
				rb_tree_count(root->left_child, k, count);
				if (_comp(_key_of_value(*(root->data)), k) == false && \
					_comp(k, _key_of_value(*(root->data))) == false)
					count++;
				rb_tree_count(root->right_child, k, count);
			}
		}

		// Searches the container for an element with a key equivalent to k and
		//returns an iterator to it if found, otherwise it returns an iterator
		//to map::end.
		iterator find (const key_type& k)
		{
			if (!_size)
				return (end());
			node_pointer n_p = find_assist(_header.left_child, k);
			if (n_p == nullptr)
				return (end());
			else
				return (n_p);
		}

		//const qualified version of find()
		const_iterator find (const key_type& k) const
		{
			if (!_size)
				return (end());
			node_pointer n_p = find_assist(_header.left_child, k);
			if (n_p == nullptr)
				return (end());
			else
				return (n_p);
		}

		/*
		** This function will assist find() function.
		** This function will return the adress of the first node that has a key
		** matching with the k parameter. It is recursive, if there was no
		** match at all, NULL pointer is returned.
		*/
		node_pointer 
		find_assist(node_pointer root, const key_type &k)
		{
			node_pointer res;

			if (!root)
				return (NULL);
			if ((res = find_assist(root->left_child, k)))
				return (res);
			if (_comp(k, _key_of_value(*(root->data))) == false && \
					_comp(_key_of_value(*(root->data)), k) == false)
				return (root);
			return (find_assist(root->right_child, k));
		}

		/*
		** Returns an iterator pointing to the first element in the container
		** whose key is not considered to go before k (i.e., either it is
		** equivalent or goes after).
		*/
		iterator
		lower_bound (const key_type& k)
		{
			if (!_size)
				return (end());
			node_pointer n_p = lower_bound_assist(_header.left_child, k);
			if (n_p == nullptr)
				return (end());
			else
				return (n_p);
		}

		const_iterator
		lower_bound (const key_type& k) const
		{
			if (!_size)
				return (end());
			node_pointer n_p = lower_bound_assist(_header.left_child, k);
			if (n_p == nullptr)
				return (end());
			else
				return (n_p);
		}

		/*
		** This function will assist lower_bound() function.
		** This function will return the adress of the first node that has a
		** key for which _comp function returns false. It is recursive, if
		** there was no match at all, NULL pointer is returned.
		*/
		node_pointer 
		lower_bound_assist(node_pointer root, const key_type &k)
		{
			node_pointer res;

			if (!root)
				return (NULL);
			if ((res = lower_bound_assist(root->left_child, k)))
				return (res);
			if (_comp(_key_of_value(*(root->data)), k) == false)
				return (root);
			return (lower_bound_assist(root->right_child, k));
		}

		iterator
		upper_bound (const key_type& k)
		{
			if (!_size)
				return (end());
			node_pointer n_p = upper_bound_assist(_header.left_child, k);
			if (n_p == nullptr)
				return (end());
			else
				return (n_p);
		}

		const_iterator
		upper_bound (const key_type& k) const
		{
			if (!_size)
				return (end());
			node_pointer n_p = upper_bound_assist(_header.left_child, k);
			if (n_p == nullptr)
				return (end());
			else
				return (n_p);
		}

		/*
		** This function will assist upper_bound() function.  This function
		** will return the adress of the first node, that follows the last node
		** to be reflexively equal to k. It is recursive, if there was no match
		** at all, NULL pointer is returned.
		**
		** PARAMETER:
		** - root: the node_pointer we are currently pointing at. (root at
		** first, then its root's child, etc, as we go deeper in the
		** recursions).
		** - k: the key we are comparing with.
		**
		** RETURN:
		** - NULL: if we went through the tree without success, or if only the
		** very last node (inorder traversal) returned false with call to
		** _comp().
		*/
		node_pointer 
		upper_bound_assist(node_pointer root, const key_type &k)
		{
			node_pointer res;

			if (!root)
				return (NULL);
			if ((res = upper_bound_assist(root->left_child, k)))
				return (res);
			if (_comp(_key_of_value(*(root->data)), k) == false && \
					_comp(k, _key_of_value(*(root->data))) == true)
				return (root);
			return(upper_bound_assist(root->right_child, k));
		}

		std::pair<const_iterator,const_iterator>
		equal_range (const key_type& k) const
		{
			if (!_size)
			{
				std::pair<const_iterator, const_iterator> res(end(), end());
				return (res);
			}
			node_pointer lower_bound = lower_bound_assist(_header.left_child, k);
			node_pointer upper_bound = upper_bound_assist(_header.left_child, k);
			std::pair<const_iterator, const_iterator> res(lower_bound, upper_bound);
			return (res);
		}

		std::pair<iterator,iterator>
		equal_range (const key_type& k)
		{
			if (!_size)
			{
				std::pair<iterator, iterator> res(end(), end());
				return (res);
			}
			node_pointer lower_bound = lower_bound_assist(_header.left_child, k);
			node_pointer upper_bound = upper_bound_assist(_header.left_child, k);
			if (!lower_bound)
			{
				std::pair<iterator, iterator> res(end(), end());
				return (res);
			}
			else if (!upper_bound)
			{
				std::pair<iterator, iterator> res(lower_bound, end());
				return (res);
			}
			std::pair<iterator, iterator> res(lower_bound, upper_bound);
			return (res);
		}

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

		//this private helper function will just create a new node for us.
		node_pointer _create_node(const value_type& val)
		{
			node_pointer new_node = _alloc_node.allocate(1);	
			try
			{
				new_node->data = _alloc.allocate(1);
			}
			catch (const std::exception &e)
			{
				_alloc_node.deallocate(new_node, 1);
				throw e;
			}
			_alloc.construct(new_node->data, val);

			new_node->right_child = nullptr;
			new_node->left_child = nullptr;
			new_node->color = node_type::RB_RED;

			return (new_node);
		}

		/*
		** Note: This function will try to insert a new rb_tree_node in the
		** red/black tree. The insertion's position is decided with the _comp
		** function. For each node, if _comp returns true, go left, if false 0
		** go right.
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
			if (_comp(_key_of_value(*(new_node->data)), \
						_key_of_value(*(_header.left_child->data))) == true)
				rb_tree_add_assist(&_header.left_child, \
						&(_header.left_child->left_child), new_node, insert);
			else if (_comp(_key_of_value(*(_header.left_child->data)), \
						_key_of_value(*(new_node->data))) == true)
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
			if (_comp(_key_of_value(*(new_node->data)), \
						_key_of_value(*((*current)->data))) == true)
				rb_tree_add_assist(top_node, &(*current)->left_child, \
						new_node, insert);
			else if (_comp(_key_of_value(*((*current)->data)), \
						_key_of_value(*(new_node->data))) == true)
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
			_alloc.destroy((*top_node)->data);
			_alloc.deallocate((*top_node)->data, 1);
			_alloc_node.deallocate(*top_node, 1);
			*top_node = NULL;
			if (set_headers_left_child_to_self)
				_set_up_header();
		}

		/*
		** This function will apply insert_equal() to every node of the given
		** tree. Browsing is inorder(first is LEFT, then ROOT, then RIGHT).
		**
		** RETURN: void
		**
		** Note: This function can throw an exception if allocation failed.
		*/

		void	rb_tree_add_inorder(node_pointer root)
		{
			if (root)
			{
				rb_tree_add_inorder(root->left_child);
				insert_equal(*(root->data));
				rb_tree_add_inorder(root->right_child);
			}
		}

		/*
		** This private function is called to find the next element in the
		** ordered tree. In order to find a next element, we need to end up to
		** the right of the given ptr:
		** 1) if there is a right_child, we move right, but then try to find
		** 	the left-most grand-children.
		** 2) if there is no right child, we need to move up to the parent,
		** until we actually made a right motion (towards the top right
		** corner) while going up to the parent.
		**
		** NOTE: Doing one last next ends up in the end() position, which is
		** nothing less than the position of the _root node itself.
		**
		** Remember, the root node is like so:
		**
		** 					parent = NULL (always).
		** 							⬆️
		** 						  _root
		** 					↙️				↘️
		**	left_child = &_root				right_child = NULL (always).
		**	or top node
		*/
		node_pointer
		find_next(node_pointer ptr)
		{
			if (ptr->right_child)
			{
				ptr = ptr->right_child;
				while (ptr->left_child)
					ptr = ptr->left_child;
			}
			else //aim for the top right motion.
			{
				while (ptr->parent)
				{
					node_pointer tmp = ptr;
					ptr = ptr->parent;
					//yes means we made a top-rightwards motion.
					if (tmp == ptr->left_child)
						break;
				}
			}
			return (ptr);
		}

		/*
		** This function will extract any node in the red/black tree whose key
		** is matching the k parameter, according to the _comp function.
		**
		** PARAMETERS:
		** - root: consider it to be the top node of the tree (it is basically
		**  &(_header.left_child). To not be confused with &_header.
		** - k: the reference key we are comparing our nodes's key with.
		**
		** note:	the nodes->color is reset to red. and all its relatives to
		** NULL.
		**
		** RETURN:
		** - node_pointer the node to be deleted/deallocated.
		** - NULL if there was no match.
		*/
		node_pointer
		rb_tree_getnode(node_pointer *root, const key_type& k)
		{
			node_pointer extracted;

			if (!root || !*root)
				return (NULL);
			extracted = rb_tree_getnode_assist(root, *root, k);
			if (extracted)
			{
				extracted->color = node_type::RB_RED;
				extracted->parent = NULL;
				extracted->left_child = NULL;
				extracted->right_child = NULL;
			}
			return (extracted);
		}

		/*
		** This function is there so that we can recurse without never
		** modifying the address of root
		*/
		node_pointer
		rb_tree_getnode_assist(node_pointer *root, node_pointer current, \
				const key_type  &k)
		{
			node_pointer res;

			if (!*root || !current)
				return (NULL);
			if (_comp(_key_of_value(*(current->data)), k) == false && \
				_comp(k, _key_of_value(*(current->data))) == false)
			{
				res = current;
				if (current->left_child && current->right_child)
					res = rb_tree_getnode_two_child(root, current);
				else if (current->color == node_type::RB_RED \
						|| current->right_child || current->left_child)
					rb_tree_getnode_either_is_red(root, current);
				else if (current->parent == &_header)
					*root = NULL;
				else
					rb_tree_get_balance(root, current, 1);
				return (res);
			}
			if (!(res = rb_tree_getnode_assist(root, current->left_child, k)))
				res = rb_tree_getnode_assist(root, current->right_child, k);
			return (res);
		}

		/*
		** note:	this function is called in the case: either the node to be
		** extracted is red, or its children is red.
		*/
		void
		rb_tree_getnode_either_is_red(node_pointer *root, node_pointer current)
		{
			node_pointer red_child;

			red_child = current->left_child;
			if (!red_child)
				red_child = current->right_child;
			if (current == *root)
				*root = red_child;
			if (current->parent && current->parent->right_child == current)
				current->parent->right_child = red_child;
			else if (current->parent && current->parent->left_child == current)
				current->parent->left_child = red_child;
			if (red_child)
			{
				red_child->parent = current->parent;
				red_child->color = node_type::RB_BLACK;
			}
		}

		/*
		** note:	this function is called when we need to get a node that has
		** two children. That node is not extracted effectively, its data is
		** first swapped with another data. The new data is found in the
		** left-most node from the right branch. That node is then extracted
		** effectively (now containing the data we wanted to delete).
		*/
		node_pointer
		rb_tree_getnode_two_child(node_pointer *root, node_pointer current)
		{
			value_type	*get_me_data;
			node_pointer get_me_node;

			get_me_node = current;
			get_me_data = current->data;
			get_me_node = get_me_node->right_child;
			while (get_me_node->left_child)
				get_me_node = get_me_node->left_child;

			current->data = get_me_node->data;
			get_me_node->data = get_me_data;
			if (get_me_node->color == node_type::RB_RED \
					|| get_me_node->right_child \
					|| get_me_node->left_child)
				rb_tree_getnode_either_is_red(root, get_me_node);
			else
				rb_tree_get_balance(root, get_me_node, 1);
			return (get_me_node);
		}


		/*
		** This function will extract any node in the red/black tree which has
		** the same address as the addr parameter.
		**
		** PARAMETERS:
		** - root: It is the top_node of the rb_tree (it is basically
		**		&(_header.left_child)).
		** - addr: This is the address of the node we want to "remove", note
		** 	that we might swap nodes content, therefore delete another node.
		** - next_addr: This is only used if we are calling the erase(first,
		**	last) version of erase(). It will be filled with the address of the
		**	next node to be deleted, until we meet last. It is important to
		**	update it as we go as nodes can be "swaped" in the process of
		**	deletion.
		** - dont_del_me: It represents the pointer to the node of "last"
		**	argument in the version of erase() using two iterators: erase(first,
		**	last). It must be updated when nodes are "swaped".
		**
		** RETURN:
		** - node_pointer the node to be deleted/deallocated.
		** - NULL if there was no match.
		*/
		node_pointer
		rb_tree_getnode_by_address(node_pointer *root, const node_pointer addr,
			node_pointer &next_addr, node_pointer &dont_del_me)
		{
			if (!root || !*root || addr == &_header)
				return (NULL);
			return (rb_tree_getnode_by_address_assist(root, *root, addr, \
				next_addr, dont_del_me));
		}

		/*
		** This function is there to assist rb_tree_get_node_by_address(), so
		** that we can recurse without never modifying the address of root.
		**
		** PARAMETERS:
		** - root: It is the top_node of the rb_tree (it is basically
		**		&(_header.left_child)).
		** - addr: This is the address of the node we want to "remove", note
		** 	that we might swap nodes content, therefore delete another node.
		** - next_addr: This is only used if we are calling the erase(first,
		**	last) version of erase(). It will be filled with the address of the
		**	next node to be deleted, until we meet last. It is important to
		**	update it as we go as nodes can be "swaped" in the process of
		**	deletion.
		** - dont_del_me: It represents the pointer to the node of "last"
		**	argument in the version of erase() using two iterators: erase(first,
		**	last). It must be updated when nodes are "swaped".
		**
		** RETURN:
		** - node_pointer the node to be deleted/deallocated.
		** - NULL if there was no match.
		*/
		node_pointer
		rb_tree_getnode_by_address_assist(node_pointer *root,\
				node_pointer current, const node_pointer addr, \
				node_pointer &next_addr, \
				node_pointer &dont_del_me)
		{
			node_pointer to_del;

			if (!*root || !current)
				return (NULL);
			if (current == addr)
			{
				to_del = current;
				next_addr = find_next(to_del);
				if (current->left_child && current->right_child)
				{
					to_del = rb_tree_getnode_two_child(root, current);
					next_addr = current;	
					if (to_del == dont_del_me)
						dont_del_me = current;
				}
				else if (current->color == node_type::RB_RED \
						|| current->right_child || current->left_child)
					rb_tree_getnode_either_is_red(root, current);
				else if (current->parent == &_header)
					*root = NULL;
				else
					rb_tree_get_balance(root, current, 1);
				return (to_del);
			}
			if (!(to_del = rb_tree_getnode_by_address_assist(root, \
							current->left_child, addr, next_addr, dont_del_me)))
				to_del = rb_tree_getnode_by_address_assist(root, \
						current->right_child, addr, next_addr, dont_del_me);
			return (to_del);
		}

		typedef struct	s_balance
		{
			node_pointer	parent;
			node_pointer	sibling;
			node_pointer	*rotation_address;
			int			is_left_child;
		}				t_balance;

		/*
		** note:	this function is called when assisting with extraction of a
		** node and should stay a private function. It will balance the trees
		** in the situation when the extraction leads to the appearance of a
		** "double black" node. It will try the six possible sequential
		** scenarios.
		*/
		void 
		rb_tree_get_balance(node_pointer *root, node_pointer current, \
				int first_time)
		{
			t_balance	balance;

			balance.is_left_child = 0;
			if (current == *root)
				return ;
			balance.sibling = current->parent->left_child;
			if (current->parent->left_child == current)
			{
				balance.is_left_child = 1;
				balance.sibling = current->parent->right_child;
			}
			if (first_time && balance.is_left_child)
				current->parent->left_child = NULL;
			else if (first_time)
				current->parent->right_child = NULL;
			balance.parent = current->parent;
			if (current->parent == *root)
				balance.rotation_address = root;
			else if (current->parent->parent->right_child == current->parent)
				balance.rotation_address = &current->parent->parent->right_child;
			else
				balance.rotation_address = &current->parent->parent->left_child;
			rb_tree_get_balance_case2(root, &balance);
		}

		/*
		** note:	After checking that the current node was not the root node.
		** We know from this point that the node has a parent and a sibling.
		**
		** note:	We first treat the case when the sibling is red (case 2):
		** we swap the color between parent and sibling. and rotate parent in
		** the opposite direction of sibling (sibling goes up).
		**
		** note:	Then we check the scenarios when parent, sibling and
		** sibling's children are all black. If yes, we swap colors between
		** parent, and we move the problem up onto parent, recursing from the
		** case1.  Else we move onto case 4.
		*/
		void
		rb_tree_get_balance_case2(node_pointer *root, t_balance *balance)
		{
			if (balance->sibling->color == node_type::RB_RED)
			{
				balance->parent->color = node_type::RB_RED;
				balance->sibling->color = node_type::RB_BLACK;
				if (balance->is_left_child)
				{
					balance->sibling = balance->sibling->left_child;
					rb_tree_left_rotation(balance->rotation_address);
					balance->rotation_address = &balance->parent->parent->left_child;
				}
				else
				{
					balance->sibling = balance->sibling->right_child;
					rb_tree_right_rotation(balance->rotation_address);
					balance->rotation_address = &balance->parent->parent->right_child;
				}
				if (balance->parent == *root)
					*root = balance->sibling;
			}
			rb_tree_get_balance_case3_4(root, balance);
		}

		/*
		** note:	this function takes care of the case when the parent is
		** red, the sibling and its children are all black. If its the case, we
		** swap colors between parent and sibling and then it is over with
		** balancing. Otherwise, we move on to case 5.
		*/
		void
		rb_tree_get_balance_case3_4(node_pointer *root, t_balance *balance)
		{
			if (balance->parent->color == node_type::RB_BLACK \
				&& balance->sibling->color == node_type::RB_BLACK
				&& (!balance->sibling->right_child \
					|| balance->sibling->right_child->color \
						== node_type::RB_BLACK)\
				&& (!balance->sibling->left_child \
					|| balance->sibling->left_child->color \
						== node_type::RB_BLACK))
			{
				balance->sibling->color = node_type::RB_RED;
				return (rb_tree_get_balance(root, balance->parent, 0));
			}
			if ((!balance->sibling->right_child \
				|| balance->sibling->right_child->color == node_type::RB_BLACK) \
				&& (!balance->sibling->left_child \
				|| balance->sibling->left_child->color == node_type::RB_BLACK) \
				&& balance->parent->color == node_type::RB_RED)
			{
				balance->parent->color = node_type::RB_BLACK;
				balance->sibling->color = node_type::RB_RED;
				return ;
			}
			rb_tree_get_balance_case5(balance);
		}

		/*
		** note:	this function tries the scenario when sibling is black and
		** closest nephew is red, whereas furthest nephew is black. And parent
		** doesnt not matter.  If this is the case, we swap color between
		** closest sibling(becomes black) and sibling (becomes red). and then
		** do a rotation on sibling that moves up closest sibling.  Then move
		** on to case 6 anyway.
		*/
		void
		rb_tree_get_balance_case5(t_balance *balance)
		{
			if (balance->is_left_child \
				&& balance->sibling->color == node_type::RB_BLACK \
				&& (!balance->sibling->right_child \
					|| balance->sibling->right_child->color \
						== node_type::RB_BLACK) \
				&& balance->sibling->left_child \
				&& balance->sibling->left_child->color == node_type::RB_RED)
			{
				balance->sibling->color = node_type::RB_RED;
				balance->sibling->left_child->color = node_type::RB_BLACK;
				balance->sibling = balance->sibling->left_child;
				rb_tree_right_rotation(&balance->parent->right_child);
			}
			else if (!balance->is_left_child \
				&& balance->sibling->color == node_type::RB_BLACK \
				&& (!balance->sibling->left_child \
					|| balance->sibling->left_child->color \
						== node_type::RB_BLACK) \
				&& balance->sibling->right_child \
				&& balance->sibling->right_child->color == node_type::RB_RED)
			{
				balance->sibling->color = node_type::RB_RED;
				balance->sibling->right_child->color = node_type::RB_BLACK;
				balance->sibling = balance->sibling->right_child;
				rb_tree_left_rotation(&balance->parent->left_child);
			}
			rb_tree_get_balance_case6(balance);
		}

		/*
		** note:	this is the final case of rebalancing tree while extracting
		** a node.  It occurs when sibling is black. and furthest nephew is
		** red.  This case is terminating.  Furthest nephew becomes red.
		** Whatever parent's color, it is swapped with sibling's color. then a
		** rotation is done on parent so that sibling goes up.
		*/
		void
		rb_tree_get_balance_case6(t_balance *balance)
		{
			if (balance->sibling->color == node_type::RB_BLACK \
				&& ((!balance->is_left_child && balance->sibling->left_child \
					&& balance->sibling->left_child->color == node_type::RB_RED)\
					|| (balance->is_left_child && balance->sibling->right_child \
					&& balance->sibling->right_child->color == node_type::RB_RED)))
			{
				typename node_type::Color tmp;
				tmp = balance->parent->color;
				balance->parent->color = balance->sibling->color;
				balance->sibling->color = tmp;
				if (balance->is_left_child)
				{
					balance->sibling->right_child->color = node_type::RB_BLACK;
					rb_tree_left_rotation(balance->rotation_address);
				}
				else
				{
					balance->sibling->left_child->color = node_type::RB_BLACK;
					rb_tree_right_rotation(balance->rotation_address);
				}
			}
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
		rb_tree_deb2(node_pointer node, t_depth depth, void (*display)(const key_type&))
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
				display(_key_of_value(*(node->data)));
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
		rb_tree_debug(void (*display)(const key_type&))
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
