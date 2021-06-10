/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vector.hpp                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/19 15:14:11 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/08 13:35:06 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VECTOR_HPP
# define VECTOR_HPP

# include "ft_random_access_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "ft_utils.hpp"

# ifndef DEBUG
#  define DEBUG 0
# endif
# if defined DEBUG && DEBUG
#  include <iostream>
# endif

namespace ft
{
	template< class T, class Alloc = std::allocator<T> >
	class vector
	{
		public:
	/*
	** ********************************************************************
	** Vector: typedefs section
	** ********************************************************************
	*/
		//TYPES
		//value_type:		the type of elements contained in the container.
		typedef T value_type;
		//allocator_type:	the allocator used to allocate memory.
		typedef Alloc allocator_type;
		//reference:		the type "reference to value_type"
		typedef typename allocator_type::reference reference; 
		//const_reference:	the type "const reference to value_type"
		typedef typename allocator_type::const_reference const_reference;
		//pointer:			the type "pointer to value_type"
		typedef typename allocator_type::pointer pointer;
		//const_pointer:	the type "const pointer to value_type"
		typedef typename allocator_type::const_pointer const_pointer;	

		//ITERATORS
		typedef typename ft::random_access_iterator<T> iterator;
		typedef typename ft::random_access_iterator<T const> const_iterator;
		typedef typename ft::reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator> const_reverse_iterator;
		
		//OTHER
		typedef typename iterator_traits<iterator>::difference_type difference_type;
		typedef typename allocator_type::size_type size_type;
		
	/*
	** ********************************************************************
	** Vector: data section
	** ********************************************************************
	*/
		private:
			allocator_type	_alloc;
			pointer		_start;
			pointer		_end;
			pointer		_end_of_capacity;

		public:
	/*
	** ********************************************************************
	** Vector: constructors, destructor and copy section
	** ********************************************************************
	*/
		//Constructs a vector, initializing its contents depending on the
		//constructor version used:
		//Constructor default (1)
		explicit vector(const allocator_type& alloc = allocator_type()) :
			_alloc(alloc),
			_start(nullptr),
			_end(nullptr),
			_end_of_capacity(nullptr)
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"default constructor(vector)" <<
				"\033[0m" << std::endl;
		}

		//Constructor fill (2)	
		explicit vector(size_type n, const value_type& val = value_type(),
				const allocator_type& alloc = allocator_type()) :
			_alloc(alloc)
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"fill constructor(vector)" <<
				"\033[0m" << std::endl;
			_start = _alloc.allocate(n); //should throw if failure
			_end = _start + n;
			_end_of_capacity = _end;
			while (n > 0)
				_alloc.construct(_start + --n, val);
		}

		//Constructor range (3)	
		template <typename InputIterator>
        vector (InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last,
			const allocator_type& alloc = allocator_type()) :
				_alloc(alloc)
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"range constructor(vector)" <<
				"\033[0m" << std::endl;
			difference_type size;
			distance(first, last, size);
			_start = _alloc.allocate(size);
			_end = _uninitialized_copy(first, last, _start);
			_end_of_capacity = _end;
		}

		public:
		//Constructor copy (4)	
		vector (const vector& x)
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"copy constructor(vector)" <<
				"\033[0m" << std::endl;
			size_type dist;
			distance(x.begin(), x.end(), dist);
			_start = _alloc.allocate(x.end() - x.begin());
			_end = _uninitialized_copy(x.begin(), x.end(), _start);
			_end_of_capacity = _end;
			_alloc = x._alloc;
		}

		//Destructor
		~vector ()
		{
			if (DEBUG)
				std::cout << "\033[31m[~]\033[34m" <<
				"destructor(vector)" <<
				"\033[0m" << std::endl;
			clear();
			_alloc.deallocate(_start, capacity());
		}

		//Copy: Assigns new contents to the container, replacing its current
		//contents, and modifying its size accordingly.
		//note: the capacity stays the same if the new size is smaller.
		vector& operator=(const vector& x)
		{
			if (this != &x)	
			{
				_destroy(_start, _end);
				if (x.size() <= capacity())
					_end = _uninitialized_copy(x.begin(), x.end(), _start);
				else
				{
					pointer tmp = _start;
					_start = _alloc.allocate(x.size());
					_alloc.deallocate(tmp, capacity());
					_end = _uninitialized_copy(x.begin(), x.end(), _start);
					_end_of_capacity = _start + x.size();
				}
			}
			return (*this);
		}

	/*
	** ********************************************************************
	** Vector: iterators section
	** ********************************************************************
	*/
		//Returns an iterator pointing to the first element in the vector.
		iterator				begin()
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"begin(vector)" <<
				"\033[0m" << std::endl;
			return (_start);
		}
		const_iterator			begin() const
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"begin(vector) const" <<
				"\033[0m" << std::endl;
			return (_start);
		}
		
		//Returns an iterator referring to the past-the-end element in the
		//vector container.
		iterator				end() { return (_end); }
		const_iterator			end() const { return (_end); }
 
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
	** Vector: capacity section
	** ********************************************************************
	*/
		//Returns the number of elements in the vector.
		size_type	size() const { return (_end - _start); }

		//Returns the maximum number of elements that the vector can hold.
		size_type	max_size() const
		{
			return (allocator_type().max_size());
		}

		//Resizes the container so that it contains n elements.
		//if n < current size. some objects are destroyed.
		//if n > current size, some copies of val are added.
		//note: if n > capacity, some allocation is done.
		void		resize (size_type n, value_type val = value_type())
		{	
			if (n == size())
				return ;
			if (n < size())
			{
				_destroy(_start + n, _end);
				_end = _start + n;
			}
			else
			{
				if (n > capacity())
				{
					if (n <= capacity() * 2)
						reserve(capacity() * 2);
					else
						reserve(n);
				}
				_uninitialized_fill_n(_end, n - size(), val);
				_end = _start + n;
			}
		}

		//Returns the size of the storage space currently allocated for the 
		//vector, expressed in terms of elements.
		size_type	capacity() const { return (_end_of_capacity - _start); }

		//Returns whether the vector is empty (i.e. whether its size is 0).
		bool		empty() const { return !(_start - _end); }

		//Requests that the vector capacity be at least enough to contain n
		//elements.
		//note: This function has no effect on the vector size and cannot alter
		//		its elements.
		void		reserve (size_type n)
		{
			if (n > capacity())
			{
				pointer tmp;
				tmp = _alloc.allocate(n);
				_uninitialized_copy(begin(), end(), tmp);
				_destroy(_start, _end);
				_alloc.deallocate(_start, capacity());
				_end = tmp + size();
				_start = tmp;
				_end_of_capacity = _start + n;
			}
		}

	/*
	** ********************************************************************
	** Vector: Element access section
	** ********************************************************************
	*/
		//Returns a reference to the element at position n in the vector
		//container.
		reference		operator[] (size_type n) { return _start[n]; }
		const_reference	operator[] (size_type n) const { return _start[n]; }

		//Returns a reference to the element at position n in the vector.
		reference		at(size_type n)
		{
			if (n >= size())
				throw (std::out_of_range("vector"));
			return (_start[n]);
		}
		const_reference	at(size_type n) const
		{
			if (n >= size())
				throw (std::out_of_range("vector"));
			return (_start[n]);
		}

		//Returns a reference to the first element in the vector.
		reference		front() { return (*_start); }

		const_reference	front() const { return (*_start); }

		//Returns a reference to the last element in the vector.
		reference		back() { return *(_end - 1); }

		const_reference	back() const { return *(_end - 1); }

	/*
	** ********************************************************************
	** Vector: Modifiers section
	** ********************************************************************
	*/

		//Assigns new contents to the vector, replacing its current contents,
		//and modifying its size accordingly.
		//range (1)
		//note: need to copy backwards in case the range is taken from self
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			size_type n;
			distance(first, last, n);
			if (n > capacity()) //need to realocate
			{
				_destroy(_start, _end); //destroy all existing objects.
				_alloc.deallocate(_start, capacity());
				_start = _alloc.allocate(n);
				_uninitialized_copy(first, last, _start);
				_end = _start + n;
				_end_of_capacity = _end;
			}
			//checking if the range is from self
			else if (first >= _start && first < _end)
			{
				vector<T> tmp(*this);	 //make a copy.
				size_type start_to_first;
				size_type start_to_last;
				distance(begin(), first, start_to_first);
				distance(begin(), last, start_to_last);
				_destroy(_start, _end); //destroy all existing objects.
				_uninitialized_copy(tmp.begin() + start_to_first, tmp.begin() + start_to_last, _start);
				_end = _start + n;
			}
			//we know the capacity is ok (no reallocation), and we copy from
			//something different from self
			else
			{
				_destroy(_start, _end); //destroy all existing objects.
				_uninitialized_copy(first, last, _start);
				_end = _start + n;
			}
		}

		//fill (2)
		void assign (size_type n, const value_type& val)
		{
			_destroy(_start, _end); //destroy all existing objects.
			if (n <= capacity()) // no need to reallocatte.
			{
				_uninitialized_fill_n(_start, n, val);
				_end = _start + n;
			}
			else //need to reallocate.
			{
				_alloc.deallocate(_start, capacity());
				_start = _alloc.allocate(n);
				_uninitialized_fill_n(_start, n, val);
				_end = _start + n;
				_end_of_capacity = _end;
			}
		}
	
		//Adds a new element at the end of the vector, after its current last
		//element. The content of val is copied (or moved) to the new element.
		void		push_back (const value_type& val)
		{
			if (_end == _end_of_capacity) //needs to grow;
				_grow_bigger();		
			_alloc.construct(_end, val);
			_end++;
		}

		//Removes the last element in the vector, effectively reducing the
		//container size by one.
		void		pop_back()
		{
			if (size())		
			{
				_alloc.destroy(_end - 1);
				_end--;
			}
		}

		//The vector is extended by inserting new elements before the element
		//at the specified position, effectively increasing the container size
		//by the number of elements inserted.
		//single element (1)
		iterator	insert(iterator position, const value_type& val)
		{		
			//position wont be valid anymore if we have to resize the vector.
			size_t offset_begin;

			distance(begin(), position, offset_begin);
			if (size() == capacity())
			{
				_grow_bigger();	
				//reseting position in case it got invalidated
				position = _start + offset_begin;
			}
			if (empty())
			{
				_alloc.construct(_start, val);
				_end++;
				return (_start);
			}
			pointer last_obj = _end - 1;
			_alloc.construct(_end, *last_obj);
			while (last_obj != _start + offset_begin)
			{
				_alloc.destroy(last_obj);
				_alloc.construct(last_obj, *(last_obj - 1));
				--last_obj;
			}
			if (!empty())
				_alloc.destroy(_start + offset_begin);
			_alloc.construct(_start + offset_begin, val);
			_end++;
			return (position);
		}

		//fill (2)
		void		insert(iterator position, size_t n, const value_type& val)
		{
			//position wont be valid anymore if we have to resize the vector.
			size_t offset_begin;

			if (!n) // nothing to do
				return ;
			distance(begin(), position, offset_begin);
			if (size() + n > capacity())
			{
				size_type len = size() + std::max(n, size());
				pointer futur_start = _alloc.allocate(len);
				pointer tmp;
				tmp  = _uninitialized_copy(begin(), position, futur_start);
				_uninitialized_fill_n(tmp, n, val);
				tmp = _uninitialized_copy(position, end(), tmp + n);
				_destroy(_start, _end);
				_alloc.deallocate(_start, capacity());
				_start = futur_start;
				_end = tmp;
				_end_of_capacity = _start + len;
			}
			else
			{
				//if the n elements to add at position will fit before _end.
				if (position + n < _end)
				{
					_uninitialized_copy(end() - n, end(), end());
					//HERE maybe, position, end() - n, end() ?
					_copy_backwards(position, position + n, end());
					_initialized_fill_n(position.base(), n, val);
					_end += n;
				}	
				else
				{	
					_uninitialized_copy(position, end(), position + n);
					_initialized_fill_n(position.base(), end() - position, val);
					_uninitialized_fill_n(_end, n - (end() - position), val);
					_end += n;
				}
			}
		}

		//range (3)
		//first and last are of the same type, represented by InputIterator. We
		//make sure they are iterators, and that they are inputerators.
		//
		//note: the second and third parameter should not come from *this !
		template <class InputIterator>
		void		insert(iterator position, InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last)
		{
			size_type n;
			distance(first, last, n);

			if (!n) //do nothing if first == last
				return ;
			if (n + size() > capacity())
			{
				size_type len = capacity() + std::max(n, capacity());
				pointer futur_start = _alloc.allocate(len);
				pointer tmp;
				tmp  = _uninitialized_copy(begin(), position, futur_start);
				tmp = _uninitialized_copy(first, last, tmp);
				tmp = _uninitialized_copy(position, end(), tmp);
				_destroy(_start, _end);
				_alloc.deallocate(_start, capacity());
				_start = futur_start;
				_end = tmp;
				_end_of_capacity = _start + len;
			}
			else
			{
				//if the n elements to add at position will fit before _end.
				if (position + n < _end)
				{
					_uninitialized_copy(end() - n, end(), end());
					_copy_backwards(position, position + n, end());
					_initialized_copy(first, last, position);
					_end = _end + n;
				}	
				else
				{
					_uninitialized_copy(position, end(), position + n);
					_initialized_copy(first, first + (end() - position), position);
					_uninitialized_copy(first + (end() - position), last, end());	
					_end = _end + n;
				}
			}	
		}

		//Removes from the vector either a single element (position).
		iterator	erase(iterator position)
		{
			_initialized_copy(position + 1, end(), position);
			_alloc.destroy(_end - 1);
			_end--;
			return (position);
		}

		//Removes from the vector  a range of elements ([first,last)).
		iterator	erase(iterator first, iterator last)
		{
			size_type size_last_to_end;
			size_type size_start_to_first;
			size_type size_first_to_last;
			distance(last, end(), size_last_to_end);
			distance(begin(), first, size_start_to_first);
			distance(first, last, size_first_to_last);
			_initialized_copy(last, end(), first);
			_destroy(_start + size_start_to_first + size_last_to_end, _end);
			_end = _end - size_first_to_last;
			return (first);
		}

		//Exchanges the content of the container by the content of x, which is
		//another vector object of the same type. Sizes may differ.
		void swap (vector& x)
		{
			pointer tmp;
			allocator_type tmp_alloc;
			//swap _alloc;
			tmp_alloc = _alloc;
			_alloc = x._alloc;
			x._alloc = tmp_alloc;
			//swap _end;
			tmp = _end;
			_end = x._end;
			x._end = tmp;
			//swap _start;
			tmp = _start;
			_start = x._start;
			x._start = tmp;
			//swap _end_of_capacity
			tmp = _end_of_capacity;
			_end_of_capacity = x._end_of_capacity;
			x._end_of_capacity = tmp;	
		}
		
		//Removes all elements from the vector (which are destroyed), leaving
		//the container with a size of 0.
		void clear()
		{
			while (_end != _start)
			{
				--_end;	//_end == _start when we destroy the last time.
				_alloc.destroy(_end);
			}	
		}

	/*
	** ********************************************************************
	** Vector: private helper functions section
	** ********************************************************************
	*/
		private:

		/*
		** this private function will make sure there will be some space for
		** the next appended object
		** note: the parameter to_add is defaulted to zero. In this case we
		** always increase the capacity by a factor 2. Otherwise we check if
		** to add is bigger than the actual capacity, if not we increase by
		** factor two again.
		*/
		void
		_grow_bigger(size_t to_add = 0)
		{
			if (capacity() == 0 && (to_add <= 1))
				reserve(1);
			else if (to_add > capacity())
				reserve(capacity() + to_add);
			else
				reserve(capacity() * 2);
		}

		/*
		** this private function will fill with val, on n occurences, a memory
		** chunk starting at start pointer in memory.
		*/
		void
		_uninitialized_fill_n(pointer start, size_type n, const value_type &val)
		{
			for (size_type i = 0; i < n; i++)
			{		
				_alloc.construct(start, val);
				start++;
			}
		}	

		/*
		** this private function will fill with val on n occurence a memory
		** chunk that is already initialized (need to destroy before
		** constructing).
		*/
		void
		_initialized_fill_n(pointer start, size_type n, const value_type &val)
		{
			for (size_type i = 0; i < n; i++)
			{		
				_alloc.destroy(start);
				_alloc.construct(start, val);
				start++;
			}
		}	

		/*
		** this private function will copy the elements found between the begin
		** and end input iterators, starting at the start location.
		**
		** return: the element past the last element copied, or start if first
		** and last parameter were equal at the beginning.
		**
		** note: the memory does not need destruction as it is uninitialized.
		*/
		template <typename InputIterator>
		pointer
		_uninitialized_copy(InputIterator begin, InputIterator end, iterator start)
		{
			while (begin != end)	
			{
				_alloc.construct(start++.base(), *begin++);
			}
			return (start.base());
		}

		/*
		** this private function will copy the elements found between the begin
		** and end input iterators (range).
		**
		** return: the element past the last element copied, or start if first
		** and last parameter were equal at the beginning.
		**
		** note: the memory does need destruction as it is initialized.
		*/
		template <typename InputIterator>
		iterator
		_initialized_copy(InputIterator begin, InputIterator end, iterator start)
		{
			while (begin != end)	
			{
				_alloc.destroy(&(*start));
				*start++ = *begin++;
			}
			return (start);
		}


		/*
		** this private function will copy elements between [first, last(,
		** starting at the end - 1 location.
		** In the destination places, we know that there is already objects
		** constructed.
		**
		** note: the copy starts from the end of the range first-last
		*/
		void
		_copy_backwards(iterator first, iterator last, iterator end)
		{
			while (last > first)
			{
				--last;
				--end;
				_alloc.destroy(end.base());
				_alloc.construct(end.base(), *last);
			}
		}
		
		/*
		** this private fuction will destruct objects between a range of
		** pointers
		*/
		void
		_destroy(pointer first, pointer last)
		{
			for (;first != last; ++first)
				_alloc.destroy(first);
		}
	};

/*
** ********************************************************************
** Vector: Non-member function overloads section
** (relational operators)
** ********************************************************************
*/
	//(1)	
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() != rhs.size())
			return (false);			
		return (ft::equal(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));
	}

	//(2)	
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!operator==(lhs, rhs));
	}

	//(3)	
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (ft::lexicographical_compare(lhs.begin(), lhs.end(), rhs.begin(), rhs.end()));		
	}

	//(4)	
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!operator<(rhs, lhs));
	}

	//(5)	
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	//(6)	
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!operator<(lhs, rhs));
	}

	//swap function overload
	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}
}
#endif
