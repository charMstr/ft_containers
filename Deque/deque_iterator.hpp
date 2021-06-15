/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque_iterator.hpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:30:08 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/15 04:30:57 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_ITERATOR_HPP
# define DEQUE_ITERATOR_HPP

# include "../Iterators/ft_iterator.hpp"

//_SIZE_BLOCK is the size of an elementary chunk of memory, all the blocks
//together will make up the map.
//make sure it is a pozer of two for efficiency.
# ifndef _SIZE_BLOCK
#	define _SIZE_BLOCK 4
# endif

/*
** the deque_iterator is of type random access_iterator
*/
namespace ft
{
	/*
	** ********************************************************************
	** deque_iterator: typedefs section
	** ********************************************************************
	*/
	template< typename T , const size_t buff_size = _SIZE_BLOCK>
	class deque_iterator : public ft::iterator<std::random_access_iterator_tag, T>
	{
		protected:
		typedef deque_iterator<T, buff_size>						iterator;
		typedef ft::iterator< std::random_access_iterator_tag , T> base_iterator;

		public:
		/*
		** typedefs to comply to static interface for any iterators from STL
		*/
		typedef typename base_iterator::value_type			value_type;
		typedef typename base_iterator::difference_type		difference_type;
		typedef typename base_iterator::pointer				pointer;
		typedef typename base_iterator::reference			reference;
		typedef typename base_iterator::iterator_category	iterator_category;

		typedef pointer*									map_pointer;
		
	/*
	** ********************************************************************
	** deque_iterator: data section
	** ********************************************************************
	*/	
		protected:
		map_pointer		_block;	// pointer to block of memory of size buff_size
		pointer			_first;	//pointer to first element in block
		pointer			_last; //pointer past the end in the current block
		pointer			_current;	//pointer to current_element in block
		const size_t	_buff_size;
	
	/*
	** ********************************************************************
	** deque_iterator: constructors, destructor and copy section
	** ********************************************************************
	*/	
		
		public:
		//default constructor
		deque_iterator(void) :
			_block(nullptr),
			_first(nullptr),
			_last(nullptr),
			_current(nullptr),
			_buff_size(buff_size)
		{ }

		//constructor by copy
		deque_iterator(const iterator &x) :
			_block(x._block),
			_first(x._first),
			_last(x._last),
			_current(x._current),
			_buff_size(x._buff_size)
		{ }
							
		//copy-assignable
		iterator &operator=(const iterator &rhs) 

		{
			_block = rhs._block;
			_first = rhs._first;
			_last = rhs._last;
			_current = rhs._current;
		//	_buff_size = rhs._buff_size; //no need as it is a const
			return (*this);
		}

		//desctructor
		~deque_iterator(void) { }

		//conversion to another type, in our case the other type is when
		//we instanciate the template with "const" (totally different type
		//from the compiler's perspective).
		operator deque_iterator<const T, buff_size>() const
		{
			return (deque_iterator<const T, buff_size>(*this));
		}

	/*
	** ********************************************************************
	** deque_iterator: legacyInputIterator requirements section
	** ********************************************************************
	*/	
		//dereference operator
		reference operator*() const { return (*_current); }

		//-> operator
		pointer operator->() const { return &(operator*()); }

		friend
		bool operator==(const deque_iterator<T, buff_size> &lhs, const deque_iterator<T, buff_size> &rhs)
		{
			return (lhs._current == rhs._current);
		}

		friend
		bool operator!=(const deque_iterator<T, buff_size> &lhs, const deque_iterator<T, buff_size> &rhs)
		{
			return !(lhs == rhs);
		}

		//prefix increment
		iterator &operator++()
		{
			_current++;
			if (_current == _last)
			{	
				set_block(_block + 1);
				_current = _first;
			}
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
	** deque_iterator: legacyBidirectionalIterator requirements section
	** ********************************************************************
	*/		
		//prefix decrement
		iterator &operator--()
		{
			if (_current == _first)
			{	
				set_block(_block - 1);
				_current = _last;
			}
			_current--;
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
	** deque_iterator: requirements section
	** ********************************************************************
	*/	

		//+= operator
		iterator &operator+=(const difference_type n) //n can be negative
		{
			//get the offset compared to the start of the block
			difference_type offset = n + (_current - _first);
			//if the result is in the same block
			if (offset >= 0 && offset < difference_type(_get_size_block()))
				_current += n;
			else
			{
				//move forward in a different block
				if (offset > 0)
				{
					difference_type jump = offset / _get_size_block();
					set_block(_block + jump);
					_current = _first + offset - jump * _get_size_block();
				}
				//move backward in a different block (offset is negative).
				else
				{
					difference_type jump = (-offset - 1) / _get_size_block() + 1;
					set_block(_block - jump);
					_current = _first + jump * _get_size_block() + offset;
				}
			}
			return *this;
		}

		//-= operator
		iterator &operator-=(const difference_type n)
		{
			return *this += (-n); //reusing the += operator
		}

		//+ operator
		iterator operator+(const difference_type n)
		{
			iterator tmp = *this;
			return (tmp += n);
		}

		//- operator
		iterator operator-(const difference_type n)
		{
			iterator tmp = *this;
			return (tmp -= n);
		}

		//overloading the '+' operator, when lhs is size_t and rhs is iterator
		//note: no need to implement the same for the '-' operator
		friend
		deque_iterator operator+(size_t n, \
				const ft::deque_iterator<T, buff_size> &rhs)
		{
			return rhs + n;
		}
		
		//- operator when another deque_iterator is on the right hand side
		//note the return type: difference_type
		friend
		difference_type operator-(const deque_iterator<T, buff_size> &lhs, const deque_iterator<T, buff_size> &rhs)
		{
			return ((lhs._block - rhs._block) * lhs._get_size_block() \
					+ (lhs._current - lhs._first) \
					- (rhs._current - rhs._first));
		}

		//"lesser than" operator
		friend
		bool operator<(const deque_iterator<T, buff_size> &lhs, const deque_iterator<T, buff_size> &rhs)
		{
			return ((lhs._block < rhs._block) || \
				 (lhs._block == rhs._block && lhs._current < rhs._current));
		}

		//"greater than" operator
		friend
		bool operator>(const deque_iterator<T, buff_size> &lhs, const deque_iterator<T, buff_size> &rhs)
		{
			return rhs < lhs;	//reusing the < operator
		}

		//"greater than/equal" operator
		friend
		bool operator>=(const deque_iterator<T, buff_size> &lhs, const deque_iterator<T, buff_size> &rhs)
		{
			return !(lhs < rhs);
		}

		//"lesser than/equal" operator
		friend
		bool operator<=(const deque_iterator<T, buff_size> &lhs, const deque_iterator<T, buff_size> &rhs)
		{
			return !(rhs < lhs);
		}

		reference operator[](size_t n)
		{
			return (*(*this + n)); //recycling the + operator
		}

	/*
	** ********************************************************************
	** deque_iterator: private functions section
	** ********************************************************************
	*/	
		//making the deque a friend so it can acces those functions
		template <class, class>
		friend class deque;

		private:
		//this private function will return the fixed size of a block.
		//in other words it gives the size of a chunk of memory. A chunk of
		//memory can contain _buff_size elements of type value_type.
		//remember that all those chunks of memory are stored into an array of
		//pointers to chunks of memory.
		size_t _get_size_block(void) const
		{	
			return (_buff_size);
		}

		//this private function will reset the _block pointer to another one
		//and set _first and _last accordingly
		void set_block(const map_pointer &new_block)
		{
			_block = new_block;
			_first  = *new_block;
			_last  = _first  + _get_size_block();
		}
	};
}

#endif
