/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_iterator.hpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 14:13:33 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/10 22:19:42 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LIST_ITERATOR_HPP
# define LIST_ITERATOR_HPP

# include "ft_iterator.hpp"
# include <iterator>
# include "Node_list.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif
# if defined DEBUG && DEBUG
#  include <iostream>
# endif

/*
** The list_iterator is just a wrapper around a pointer to a Node_list<T>. This
** iterator will allow us to do operations belonging to the spectrum of
** bidirectional_iterators (basically ++ and -- operations but not + and - and
** [] operations).
** Therefor the iterator_category is set to be bidirectional_iterator_tag.
*/

namespace ft
{
	template< typename T >
	class list_iterator : public ft::iterator<std::bidirectional_iterator_tag, T>
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
		typedef list_iterator								iterator;
		typedef ft::Node_list<T>							node_type;
		typedef node_type*									node_pointer;
	/*
	** ********************************************************************
	** list_iterator: data section
	** ********************************************************************
	*/	
		node_pointer _ptr;
	/*
	** ********************************************************************
	** list_iterator: constructors, destructor and copy section
	** ********************************************************************
	*/	
		public:
		//default constructor
		list_iterator(void) : _ptr(nullptr) { }

		//copy constructor
		list_iterator(const node_pointer ptr) : _ptr(ptr) {}

		//copy-assignable
		iterator &operator=(const iterator &rhs)
		{
			_ptr = rhs._ptr;
			return *this;	
		}

		//desctructor
		~list_iterator(void) { }
		
		//conversion to another type, in our case the other type is when
		//we instanciate the template with "const" (totally different type
		//from the compiler's perspective).
		operator list_iterator<const T>() const
		{
			/*
			if (DEBUG)
				//std::cout << __PRETTY_FUNCTION__ << std::endl;
				std::cout << "\033[34m" << \
				"conversion operator(list_iterator)" << \
				"\033[0m" << std::endl;	
				*/
			return (list_iterator<const T>(_ptr));
		}
	/*
	** ********************************************************************
	** list_iterator: legacyInputIterator requirements section
	** ********************************************************************
	*/	
		//dereference operator
		reference operator*() const { return (_ptr->data); }

		//-> operator
		pointer operator->() const { return &(operator*()); }
	
		//friended, so that we can compare const and non const types.
		friend
		bool operator==(const list_iterator<T> &lhs, const list_iterator<T> &rhs)
		{
			return (lhs._ptr == rhs._ptr);
		}

		friend
		bool operator!=(const list_iterator<T> &lhs, const list_iterator<T> &rhs)
		{
			return !(lhs == rhs);
		}

		//prefix increment
		iterator &operator++()
		{
			_ptr = _ptr->next;
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
	** list_iterator: legacyBidirectionalIterator requirements section
	** ********************************************************************
	*/		
		//prefix decrement
		iterator &operator--()
		{
			_ptr = _ptr->previous;
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
	** list_iterator: other section
	** ********************************************************************
	*/	
		//the list class is made a friend so that the get_ptr function can be
		//accessed without exposing it to the outside.
		template <class, class>
		friend class list;

		private:
		node_pointer get_ptr()
		{
			return (_ptr);
		}
	};
}
#endif