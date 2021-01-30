/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_reverse_iterator.hpp                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/29 15:13:06 by charmstr          #+#    #+#             */
/*   Updated: 2021/01/30 09:13:06 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_REVERSE_RANDOM_ACCESS_ITERATOR_HPP
# define FT_REVERSE_RANDOM_ACCESS_ITERATOR_HPP

# include "ft_iterator.hpp"
# include "ft_random_access_iterator.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif

# if defined DEBUG && DEBUG
#  include <iostream>
# endif

/*
** The fundamental relation between a reverse iterator and its
** corresponding iterator i is established by the identity:
** 			&*(reverse_iterator(i)) == &*(i - 1).
** This mapping is dictated by the fact that while there is always a pointer
** past the end of an array, there might not be a valid pointer before the
** beginning of an array.
**
** note: the reverse iterator should only be used with an input Iterator
** parameter of type BidirectionalIterator, or RandomAccessIterator.
*/

namespace ft
{
	template <class Iterator>
	class reverse_iterator
	{
	/*
	** ********************************************************************
	** reverse_iterator: typedefs section
	** ********************************************************************
	*/
		//added for readability
		private:
		typedef reverse_iterator		r_iterator;
		typedef reverse_iterator<Iterator> self;

		/*
		** typedefs to comply to static interface for any iterators from STL
		*/

		typedef typename ft::iterator_traits<Iterator>::value_type value_type;
		typedef typename ft::iterator_traits<Iterator>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iterator>::pointer pointer;
		typedef typename ft::iterator_traits<Iterator>::reference reference;
		typedef typename ft::iterator_traits<Iterator>::iterator_category iterator_category;

	/*
	** ********************************************************************
	** reverse_iterator: data section
	** ********************************************************************
	*/
		protected:
		Iterator _current;

	/*
	** ********************************************************************
	** reverse_iterator: constructors, destructor and copy section
	** ********************************************************************
	*/	
		public:
		//construct a reverse iterator object, points to fuckall
		reverse_iterator() : _current(nullptr) {}

		//construct a reverse iterator from an randomaccessiterator
		reverse_iterator(Iterator x) : _current(x) {}

		//copy construct from another reverse_iterator
		reverse_iterator(const reverse_iterator<Iterator> &r_it)
			: _current(r_it._current) {}

		//copy-assignable
		reverse_iterator &operator=(const reverse_iterator<Iterator> &rhs)
		{
			_current = rhs._current;
			return (*this);
		}

		//conversion to another type, in our case the other type is when
		//we instanciate the template with "const" (totally different type
		//from the compiler's perspective).
		//operator reverse_iterator<Iterator>() const
		//
		//note: need to specify a new template parameter, and need to replace
		// "Iterator" by the full name: //"ft::random_access_iterator<const T>"
		//so that the compiler can distinguish this is a specific route, when 
		//trying to convert from a non const Iterator to a const Iterator.
		template <typename T>
		operator
		reverse_iterator<ft::random_access_iterator<const T> >() const
		{
			if (DEBUG)
				//std::cout << __PRETTY_FUNCTION__ << std::endl;
				std::cout << "\033[34m" << \
				"conversion operator(reverse_iterator)" << \
				"\033[0m" << std::endl;	
			return (reverse_iterator<ft::random_access_iterator<const T> >(_current));
		}

		//destructor
		virtual ~reverse_iterator() {}

	/*
	** ********************************************************************
	** reverse_iterator: requirements section
	** ********************************************************************
	*/	
		//returns the used randomaccessiterator kept as a data member
		Iterator base() { return _current; }

		//return a reference to the original's iterator position - 1;
		reference operator*() const
		{
			Iterator tmp = _current;
			return *--tmp;
		}

		//preincrement. note that the original iterator is decremented.
		self& operator++()
		{
			--_current;
			return *this;
		}

		//post increment
		self operator++(int)
		{
			self tmp = *this;
			--_current;
			return tmp;
		}

		//pre decrement, (the original is incremented as it is in reverse
		self& operator--()
		{
			++_current;
			return *this;
		}

		//post decrement (the original is incremented, as it is a reverse)
		self operator--(int)
		{
			self tmp = *this;
			++_current;
			return tmp;
		}
		
		//+ operator, returns a copy of type reverse_iterator
		self operator+(difference_type n) const
		{
			return self(_current - n);
		}

		self& operator+=(difference_type n)
		{
			_current -= n;
			return *this;
		}

		self operator-(difference_type n) const
		{
			return self(_current + n);
		}

		self& operator-=(difference_type n)
		{
			_current += n;
			return *this;
		}

		pointer operator->() const
		{
			return &(operator*());
		}

		reference operator[](difference_type n)
		{
			return *(*this + n);
		}

	/*
	** ********************************************************************
	** reverse_iterator: friend functions section
	** ********************************************************************
	*/	
		friend bool
		operator==(const self& lhs, const self& rhs)
		{
			return (lhs._current == rhs._current);
		}

		friend bool
		operator!=(const self& lhs, const self& rhs)
		{
			return !(lhs._current == rhs._current);
		}

		friend bool
		operator<(const self& lhs, const self& rhs)
		{
			return (lhs._current > rhs._current);
		}

		friend bool
		operator<=(const self& lhs, const self& rhs)
		{
			return (lhs._current >= rhs._current);
		}

		friend bool
		operator>(const self& lhs, const self& rhs)
		{
			return (lhs._current < rhs._current);
		}

		friend bool
		operator>=(const self& lhs, const self& rhs)
		{
			return (lhs._current <= rhs._current);
		}

		friend difference_type
		operator-(const self& lhs, const self& rhs)
		{
			return (rhs._current - lhs._current);
		}

		friend self //type reverse_iterator<Iterator>
		operator+(difference_type n, const self& rhs)
		{
			return (self(rhs + n));	
		}
	};
}
#endif
