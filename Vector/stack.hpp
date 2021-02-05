/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   stack.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/04 19:37:39 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/05 23:49:38 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STACK_HPP
# define STACK_HPP

# include "deque.hpp" //inheriting from the deque.

# include <iostream>
# ifndef DEBUG
#  define DEBUG 0
# endif

/*
** Stack is implemented as adaptor an of the ft::deque<T> container by default.
*/

namespace ft
{
	template <class T, class Container = ft::deque<T> >
	class stack 
	{
	/*
	** ********************************************************************
	** Stack: typedefs section
	** ********************************************************************
	*/
		typedef Container	container_type;
		typedef T			value_type;
		typedef size_t		size_type;
	/*
	** ********************************************************************
	** Stack: data section
	** ********************************************************************
	*/
		private:
		container_type _cont;
	/*
	** ********************************************************************
	** Stack: constructors, destructor and copy section
	** ********************************************************************
	*/
		public:
		explicit stack (const container_type& ctnr = container_type()) :
			_cont(ctnr)
		{ }

	/*
	** ********************************************************************
	** Stack: capacity section
	** ********************************************************************
	*/
		bool empty() const { return (_cont.empty()); }

		size_type size() const { return (_cont.size()); }

	/*
	** ********************************************************************
	** Stack: Element access section
	** ********************************************************************
	*/
		value_type& top() { return (_cont.back()); }

		const value_type& top() const { return (_cont.back()); }

	/*
	** ********************************************************************
	** Stack: Modifiers section
	** ********************************************************************
	*/
		void push (const value_type& val) { _cont.push_back(val); }
		
		void pop() { _cont.pop_back(); }

	/*
	** ********************************************************************
	** Stack: Non-member function overloads section
	** (relational operators)
	** ********************************************************************
	*/
		//(1)
		friend 
		bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._cont == rhs._cont);
		}

		//(3)
		friend
		bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
		{
			return (lhs._cont < rhs._cont);	
		}

	};

	//(2)
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return !(lhs == rhs);
	}

	//(4)
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!operator<(rhs, lhs));
	}
	//(5)
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (rhs < lhs);
	}
	//(6)
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (!operator<(lhs, rhs));
	}
}

#endif
