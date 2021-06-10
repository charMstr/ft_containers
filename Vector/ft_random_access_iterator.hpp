/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_random_access_iterator.hpp                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/22 00:16:32 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/08 12:55:39 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_RANDOM_ACCESS_ITERATOR_HPP
# define FT_RANDOM_ACCESS_ITERATOR_HPP

# include "ft_iterator.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif

# include <iostream>
# if defined DEBUG && DEBUG
#  include <iostream>
# endif

namespace ft
{
	/*
	** the random access iterator class inherits theoreticaly from the iterator
	** base class
	**
	** @param1: the first template parameter is there so that we can provide
	**			the value_type to the base classe, and more generally the
	**			value_type "pointed to" by our iterator.
	*/

	template <typename T> 
	class random_access_iterator : ft::iterator<std::random_access_iterator_tag , T>
	{
	/*
	** ********************************************************************
	** random_access_iterator: typedefs section
	** ********************************************************************
	*/
		//added for readability
		private:
		typedef random_access_iterator<T> r_a_iterator;
		typedef ft::iterator< std::random_access_iterator_tag , T> base_iterator;

		public:
		/*
		** typedefs to comply to static interface for any iterators from STL
		*/
		typedef typename base_iterator::value_type value_type;
		typedef typename base_iterator::difference_type difference_type;
		typedef typename base_iterator::pointer pointer;
		typedef typename base_iterator::reference reference;
		typedef typename base_iterator::iterator_category iterator_category;

	/*
	** ********************************************************************
	** random_access_iterator: data section
	** ********************************************************************
	*/
		private:
			pointer _ptrToElem;

	/*
	** ********************************************************************
	** random_access_iterator: constructors, destructor and copy section
	** ********************************************************************
	*/	
		public:
		//default constructor
		random_access_iterator(void) : _ptrToElem(nullptr)
		{
			if (DEBUG)
				//std::cout << __PRETTY_FUNCTION__ << std::endl;
				std::cout << "\033[34m" << \
				"default constructor(random_access_iterator)" << \
				"\033[0m" << std::endl;	
		}

		//copy constructor from a raw pointer: private
		random_access_iterator(const pointer ptr) : _ptrToElem(ptr)
		{
			if (DEBUG)
				//std::cout << __PRETTY_FUNCTION__ << std::endl;
				std::cout << "\033[34m" << \
				"copy constructor(random_access_iterator) (pointer arg)" << \
				"\033[0m" << std::endl;	
		}

		//conversion to another type, in our case the other type is when
		//we instanciate the template with "const" (totally different type
		//from the compiler's perspective).
		operator random_access_iterator<T const>() const
		{
			if (DEBUG)
				//std::cout << __PRETTY_FUNCTION__ << std::endl;
				std::cout << "\033[34m" << \
				"conversion operator(random_access_iterator)" << \
				"\033[0m" << std::endl;	
			return (random_access_iterator<const T>(_ptrToElem));
		}

		//copy-assignable
		r_a_iterator &operator=(const r_a_iterator &rhs)
		{
			_ptrToElem = rhs._ptrToElem;
			return (*this);
		}
		//desctructor
		~random_access_iterator(void) { }

	/*
	** ********************************************************************
	** random_access_iterator: legacyInputIterator requirements section
	** ********************************************************************
	*/	
		//dereference operator
		reference operator*() const { return (*_ptrToElem); }

		//-> operator
		pointer operator->() const { return &(operator*()); }

		/*
		** functions are marked friend so that they are actually defined in the
		** namespace ft, rather than in the current location: ft::vector<T>
		** 1) reason it exists:
		** 	In the case the left hand side is a non constant value whereas the
		** 	right hand side is a constant value, if we used a member function,
		** 	the template instantiation would be vector<T> and not
		** 	vector<const T>. Those would be considered two totally different
		** 	types by the compiler and there should be no way to translate from
		** 	a const type to a non const type. We then need to declare the
		** 	function as non member, being able to take two "totally" different
		** 	instanciations of vector<T> (const and non const).
		** 2) reason it is a friend and not just external:
		**	the friend function can
		**	access private and protected members.
		*/
		friend
		bool operator==(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
		{
			return (lhs._ptrToElem == rhs._ptrToElem);
		}

		friend
		bool operator!=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
		{
			return (lhs._ptrToElem != rhs._ptrToElem);
		}

		//postfix increment
		r_a_iterator operator++(int)
		{
			r_a_iterator tmp = *this;
			_ptrToElem++;
			return tmp;
		}

		//prefix increment
		r_a_iterator &operator++()
		{
			++_ptrToElem;	
			return (*this);
		}

		//returns the actual pointer to the element
		pointer base(void) const
		{
			return (_ptrToElem);
		}
	/*
	** ********************************************************************
	** random_access_iterator: legacyBidirectionalIterator requirements section
	** ********************************************************************
	*/		
		//postfix decrement
		r_a_iterator operator--(int)
		{
			r_a_iterator tmp = *this;
			_ptrToElem--;
			return tmp;
		}

		//prefix decrement
		r_a_iterator &operator--()
		{
			--_ptrToElem;	
			return (*this);
		}
	/*
	** ********************************************************************
	** random_access_iterator: requirements section
	** ********************************************************************
	*/	
		//+= operator
		r_a_iterator &operator+=(const difference_type n)
		{
			_ptrToElem += n;
			return *this;
		}

		//-= operator
		r_a_iterator &operator-=(const difference_type n)
		{
			_ptrToElem -= n;
			return *this;
		}

		//+ operator when the size_t n is on the right hand side
		r_a_iterator operator+(const difference_type n) const
		{
			return _ptrToElem + n;
		}

		//overloading the '+' operator, when lhs is size_t and rhs is r_a_iterator
		//note: no need to implement the same for the '-' operator
		friend
		ft::random_access_iterator<T> operator+(size_t n, \
				const ft::random_access_iterator<T> &rhs)
		{
			return rhs._ptrToElem + n;
		}

		//- operator when the size_t n is on the right hand side
		r_a_iterator operator-(const difference_type n) const
		{
			return _ptrToElem - n;
		}

		//- operator when another r_a_iterator is on the right hand side
		//note the return type: difference_type
		friend
		typename random_access_iterator<T>::difference_type operator-(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
		{
			return lhs._ptrToElem - rhs._ptrToElem;
		}

		//"lesser than" operator
		friend
		bool operator<(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
		{
			return lhs._ptrToElem < rhs._ptrToElem;	
		}

		//"greater than" operator
		friend
		bool operator>(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
		{
			return lhs._ptrToElem > rhs._ptrToElem;	
		}

		//"greater than/equal" operator
		friend
		bool operator>=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
		{
			return (lhs._ptrToElem >= rhs._ptrToElem);
		}

		//"lesser than/equal" operator
		friend
		bool operator<=(const random_access_iterator<T> &lhs, const random_access_iterator<T> &rhs)
		{
			return (lhs._ptrToElem <= rhs._ptrToElem);
		}

		reference operator[](size_t n)
		{
			return (*(_ptrToElem + n));
		}
	};
}
#endif
