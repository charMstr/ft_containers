/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list.hpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/08 16:30:10 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/11 01:56:39 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_HPP
# define LIST_HPP

# include "list_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "ft_utils.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif
# if defined DEBUG && DEBUG
#  include <iostream>
# endif

/*
** The doubly linked list is made circular, it closes itself on the "sentinel"
** node, which is found at the past-the-end and before-the-start position.
** At the very begining when the list is empty, only the sentinel node exists
** therefore its next and previous fields both points on itself.
**
** note: the iterator is nothing but an abstraction over the node_pointer. It
**	will add to it capabilities like ++ and -- operations.
*/

namespace ft
{
	template < class T, class Alloc = std::allocator<T> >
	class list
	{
	/*
	** ********************************************************************
	** List: typedefs section
	** ********************************************************************
	*/
		private:
		//the node of the list, containing the type in question.
		typedef ft::Node_list<T, Alloc>						node_type;
		typedef node_type*									node_pointer;
		typedef std::allocator<node_type> 					node_allocator_type;

		public:
		//TYPES
		//value_type:		the type of elements contained in the Node
		typedef	T											value_type;
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
		typedef typename ft::list_iterator<T> iterator;
		typedef typename ft::list_iterator<const T> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;

		//OTHER
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef typename node_allocator_type::size_type size_type;

	/*
	** ********************************************************************
	** List: data section
	** ********************************************************************
	*/
		private:
		node_pointer		_sentinel;
		size_type			_size;
		allocator_type		_alloc;
		node_allocator_type	_alloc_node;
		
	/*
	** ********************************************************************
	** List: constructors, destructor and copy section
	** ********************************************************************
	*/
		public:
		//default (1)	
		explicit list (const allocator_type& alloc = allocator_type()) :
			_size(0),
			_alloc(alloc),
			_alloc_node(node_allocator_type())
		{
			_build_sentinel();
		}
		//fill (2)	
		explicit list (size_type n, const value_type& val = value_type(),
                const allocator_type& alloc = allocator_type()) :
			_size(0),
			_alloc(alloc),
			_alloc_node(node_allocator_type())
		{
			_build_sentinel();		
			for (size_type i = 0; i < n; i++)
				push_back(val);	
		}

		//range (3)	
		template <class InputIterator>
		list (InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last,
        		const allocator_type& alloc = allocator_type()) :
			_size(0),
			_alloc(alloc),
			_alloc_node(node_allocator_type())
		{
			_build_sentinel();	
			for (; first != last; ++first)
			{
				push_back(*first);	
			}
		}

		//copy (4)	
		list (const list& x)
		{
			*this = x;
		}

		//destructor
		~list()
		{
			clear();
			_alloc.destroy(&_sentinel->data);
			_alloc_node.deallocate(_sentinel, 1);
		}

		//copy (1)
		list& operator= (const list& x)
		{
			if (this != &x)	
			{	
				_alloc = x._alloc;	
				_alloc_node = x._alloc_node;
				_size = 0;
				_build_sentinel();	
				node_pointer tmp = x._sentinel->next;
				for (; tmp != x._sentinel; tmp = tmp->next)
				{
					push_back(tmp->data);	
				}
			}
			return (*this);
		}

	/*
	** ********************************************************************
	** Deque: iterators section
	** ********************************************************************
	*/
		//Returns an iterator pointing to the first element in the vector.
		iterator				begin()
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"begin(vector)" <<
				"\033[0m" << std::endl;
			return (_sentinel->next);
		}

		const_iterator			begin() const
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"begin(vector) const" <<
				"\033[0m" << std::endl;
			return (_sentinel->next);
		}
		
		//Returns an iterator referring to the past-the-end element in the
		//vector container.
		iterator				end() { return (_sentinel); }
		const_iterator			end() const { return (_sentinel); }


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
	** List: capacity section
	** ********************************************************************
	*/
		//Returns the maximum number of elements that the vector can hold.
		size_type	max_size() const
		{
			return (node_allocator_type().max_size());
		}

		//Returns whether the vector is empty (i.e. whether its size is 0).
		bool		empty() const { return (_sentinel->next == _sentinel); }

		//Returns the number of elements in the vector.
		size_type	size() const { return _size; }
		
	/*
	** ********************************************************************
	** List: Element access section
	** ********************************************************************
	*/

		reference front()
		{
			return (_sentinel->next->data);
		}

		const_reference front() const
		{
			return (_sentinel->next->data);
		}

		reference back()
		{
			return (_sentinel->previous->data);
		}

		const_reference back() const
		{
			return (_sentinel->previous->data);
		}

	/*
	** ********************************************************************
	** List: Modifiers section
	** ********************************************************************
	*/
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

		//fill (2)
		void assign (size_type n, const value_type& val)
		{
			clear();
			for (size_type count = 0; count < n; count++)
				push_back(val);
		}

		void push_front (const value_type& val)
		{
			node_pointer new_node = _alloc_node.allocate(1);
			_alloc.construct(&new_node->data, val);	

			_sentinel->next->previous = new_node;
			new_node->next = _sentinel->next;
			new_node->previous = _sentinel;
			_sentinel->next = new_node;
			_size += 1;
		}

		void pop_front()
		{
			if (empty())
				return ;
			node_pointer remove = _sentinel->next;
			_sentinel->next = remove->next;
			remove->next->previous = _sentinel;
			_alloc.destroy(&remove->data);
			_alloc_node.deallocate(remove, 1);
			_size -= 1;
		}

		void push_back (const value_type& val)
		{
			node_pointer new_node = _alloc_node.allocate(1);
			_alloc.construct(&new_node->data, val);	

			_sentinel->previous->next = new_node;
			new_node->previous = _sentinel->previous;
			new_node->next = _sentinel;
			_sentinel->previous = new_node;
			_size += 1;
		}

		void pop_back()
		{
			if (empty())
				return ;
			node_pointer remove = _sentinel->previous;
			_sentinel->previous = remove->previous;
			remove->previous->next = _sentinel;
			_alloc.destroy(&remove->data);
			_alloc_node.deallocate(remove, 1);
			_size -= 1;
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

		void swap (list& x)
		{
			node_pointer tmp = _sentinel;
			_sentinel = x._sentinel;
			x._sentinel = tmp;
			size_type tmp2 = _size;
			_size = x._size;
			x._size = tmp2;
		}

		void resize (size_type n, value_type val = value_type())
		{
			if (n == _size) //no need to resize
				return ;
			if (n > _size) //if we will need to add new nodes.
			{
				n = n - _size; //how many we need to add
				node_pointer new_list_end;
				node_pointer new_list = _build_insertion_list(n, val, new_list_end);
				_sentinel->previous->next = new_list;
				new_list->previous = _sentinel->previous;
				new_list_end->next = _sentinel;
				_sentinel->previous =  new_list_end;
				_size += n;
				return ;
			}
			// getting here means that: n < _size
			_size = n;
			node_pointer start_del = _sentinel->next; //the first node to go
			while (n > 0)
			{
				start_del = start_del->next;
				n--;
			}
			start_del->previous->next = _sentinel;
			_sentinel->previous = start_del->previous;	
			node_pointer tmp;
			while (start_del != _sentinel)
			{
				tmp = start_del;
				start_del = start_del->next;
				_alloc.destroy(&tmp->data);
				_alloc_node.deallocate(tmp, 1);
			}
		}

		//note: destroy all the nodes, and only leaves the sentinel node.
		void clear()
		{
			node_pointer current = _sentinel->next;
			node_pointer next_one;
			while (current != _sentinel)
			{
				next_one = current->next;
				_alloc.destroy(&current->data);
				_alloc_node.deallocate(current, 1);
				current = next_one;
			}
			_sentinel->next = _sentinel;
			_sentinel->previous = _sentinel;
			_size = 0;
		}

	/*
	** ********************************************************************
	** List: Operations functions section
	** ********************************************************************
	*/
 //TODO(Wed 10/02/2021 at 16:40:43) 
		//entire list (1)	
		void splice (iterator position, list& x);
 //TODO(Wed 10/02/2021 at 16:40:43) 
		//single element (2)	
		void splice (iterator position, list& x, iterator i);
 //TODO(Wed 10/02/2021 at 16:40:43) 
		//element range (3)	
		void splice (iterator position, list& x, iterator first, iterator last);

 //TODO(Wed 10/02/2021 at 16:40:43) 
		void remove (const value_type& val);

 //TODO(Wed 10/02/2021 at 16:40:43) 
		template <class Predicate>
		void remove_if (Predicate pred);

 //TODO(Wed 10/02/2021 at 16:40:43) 
		//(1)
		void unique();
 //TODO(Wed 10/02/2021 at 16:40:43) 
		//(2)
		template <class BinaryPredicate>
		void unique (BinaryPredicate binary_pred);

 //TODO(Wed 10/02/2021 at 16:40:43) 
		//(1)
		void merge (list& x);
 //TODO(Wed 10/02/2021 at 16:40:43) 
		//(2)
		template <class Compare>
		void merge (list& x, Compare comp);
		
 //TODO(Wed 10/02/2021 at 16:40:43) 
		//(1)
		void sort();
 //TODO(Wed 10/02/2021 at 16:40:43) 
		//(2)
		template <class Compare>
		void sort (Compare comp);

 //TODO(Wed 10/02/2021 at 16:40:43) 
		void reverse();
	/*
	** ********************************************************************
	** List: private helper functions section
	** ********************************************************************
	*/
		private:

		//private helper function: builds the sentinel node
		void _build_sentinel(void)
		{
			_sentinel = _alloc_node.allocate(1);
			_sentinel->next = _sentinel;
			_alloc.construct(&_sentinel->data, value_type());
			_sentinel->previous = _sentinel;
		}

		/*
		** this private helper function will build a new list, and update a ref
		** that will store the end of the newly created list
		** note:	The head->previous of the list points to nullptr, so does
		**			ref_new_list_end->previous.
		** return: the start of the newly created list
		*/
		node_pointer _build_insertion_list(size_type n, const value_type& val,\
				node_pointer &ref_new_list_end)
		{
			node_pointer current_end = nullptr;
			node_pointer start = nullptr;
			node_pointer new_node;
			for (size_type i = 0; i < n; i++)
			{
				new_node = _create_node(val);
				if (start == nullptr)
					start = new_node;
				else
				{
					current_end->next = new_node;	
					new_node->previous = current_end;
				}
				current_end = new_node;
				//should catch a trow and free the build list here.
			}
			ref_new_list_end = new_node;
			return (start);
		}

		//this private helper function will just create a new node for us.
		node_pointer _create_node(const value_type& val)
		{
			node_pointer new_node = _alloc_node.allocate(1);	
			_alloc.construct(&new_node->data, val);
			new_node->next = nullptr;
			new_node->previous = nullptr;
			return (new_node);
		}

		/*
		** This private helper function will create a new list from the
		** [first,last) range. The last parameter: ref_new_list_end will be 
		** updated so that we know the end of the newly created list.
		** note:	The head->previous of the list points to nullptr, so does
		**			ref_new_list_end->previous.
		** 
		** return: the head of the new_list.
		*/
		template <class InputIterator>
		node_pointer _build_insertion_list(InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last,
				node_pointer &ref_new_list_end)
		{
			node_pointer current_end = nullptr;
			node_pointer start = nullptr;
			node_pointer new_node;
			for (; first != last; first++)
			{
				new_node = _create_node(*first);
				if (start == nullptr)
					start = new_node;
				else
				{
					current_end->next = new_node;	
					new_node->previous = current_end;
				}
				current_end = new_node;
				//should catch a trow and free the build list here.
			}
			ref_new_list_end = new_node;
			return (start);
		}
	};	
	/*
	** ********************************************************************
	** List: Non-member function overloads section	(relational operators)
	** ********************************************************************
	*/
 	//TODO(Wed 10/02/2021 at 16:40:43) 

 	//TODO(Wed 10/02/2021 at 16:40:43) 
	template <class T, class Alloc>
	void swap (list<T,Alloc>& x, list<T,Alloc>& y);
}

#endif
