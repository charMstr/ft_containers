/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   queue.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 23:47:21 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/06 00:02:29 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef QUEUE_HPP
# define QUEUE_HPP

# include "deque.hpp" //inheriting from the deque.

# include <iostream>
# ifndef DEBUG
#  define DEBUG 0
# endif

/*
** Queue is implemented as adaptor an of the ft::deque<T> container by default.
*/

namespace ft
{
	template <class T, class Container = ft::deque<T> >
	class queue //: public deque<T>
	{
	/*
	** ********************************************************************
	** Queue: typedefs section
	** ********************************************************************
	*/
		typedef Container	container_type;
		typedef T			value_type;
		typedef size_t		size_type;
	/*
	** ********************************************************************
	** Queue: data section
	** ********************************************************************
	*/
		private:
		container_type _cont;
	/*
	** ********************************************************************
	** Queue: constructors, destructor and copy section
	** ********************************************************************
	*/
		public:
		explicit queue (const container_type& ctnr = container_type()) :
			_cont(ctnr)
		{ }

	/*
	** ********************************************************************
	** Queue: capacity section
	** ********************************************************************
	*/
		bool empty() const { return (_cont.empty()); }

		size_type size() const { return (_cont.size()); }
	/*
	** ********************************************************************
	** Stack: Element access section
	** ********************************************************************
	*/
		/*
		** Returns a reference to the next element in the queue.
		** The next element is the "oldest" element in the queue and the same
		** element that is popped out from the queue when queue::pop is called.
		*/
		value_type& front() { return (_cont.front()); }

		const value_type& front() const { return (_cont.front()); }

		/*
		** Returns a reference to the last element in the queue. This is the
		** "newest" element in the queue (i.e. the last element pushed into the
		** queue).
		**
		** This member function effectively calls member back of the underlying
		** container object.
		*/
		value_type& back() { return (_cont.back()); }

		const value_type& back() const { return (_cont.back()); }


	/*
	** ********************************************************************
	** Stack: Modifiers section
	** ********************************************************************
	*/
		void push (const value_type& val) { _cont.push_back(val); }
		
		void pop() { _cont.pop_front(); }

	/*
	** ********************************************************************
	** Stack: Non-member function overloads section
	** (relational operators)
	** ********************************************************************
	*/
		//(1)
		friend 
		bool operator== (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
		{
			return (lhs._cont == rhs._cont);
		}

		//(3)
		friend
		bool operator<  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
		{
			return (lhs._cont < rhs._cont);	
		}
	};

	//(2)
	template <class T, class Container>
	bool operator!= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	//(4)
	template <class T, class Container>
	bool operator<= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (!operator<(rhs, lhs));
	}
	//(5)
	template <class T, class Container>
	bool operator>  (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (rhs < lhs);
	}
	//(6)
	template <class T, class Container>
	bool operator>= (const queue<T,Container>& lhs, const queue<T,Container>& rhs)
	{
		return (!operator<(lhs, rhs));
	}
}

#endif
