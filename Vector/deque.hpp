/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   deque.hpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 14:31:36 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/05 23:22:56 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DEQUE_HPP
# define DEQUE_HPP

# include "deque_iterator.hpp"
# include "ft_reverse_iterator.hpp"
# include "ft_utils.hpp"

# define TO_LEFT 0 //used to shif to the left or the right.
# define TO_RIGHT 1

# define NEVER 0 //used when calling the destroy function
# define ALWAYS 1
# define IF_NOT_FIRST 2

# include <iostream>
# ifndef DEBUG
#  define DEBUG 0
# endif

/*
** the deque is implemented with a map of variable size, which contains
** pointers to fixed-size arrays (size = _SIZE_BLOCK). Those fixed-size arrays
** will contain the data (type T = value_type).
** So basically the map is a T** array, each raw contains a T* array of size
** _SIZE_BLOCK.
**
** note on _start and _end:
** 	the _start refers to the first element of the deque, _end refers to the 
** 	one-past-the-end element.
** 	Those two are iterators, they refer to the block they are in (a block is a 
** 	T* pointer within the map, and they give the current position within this
** 	specific block.
**
** 	Those iterators reset themself to a new block using this function:
**		void set_block(map_pointer new_block)
**		{
**			_block = new_block;
**			_first  = *new_block;
**			_last  = _first  + _get_size_block();
**		}
**	Therefor when _end._current reaches _end._last, it sets itself to the next
**	block and tries to dereference this new_block:
**			_first  = *new_block;
**	hence the next block should already be allocated to receive the _end to
**	avoid accessing unauthorized memory.
**	The same does not apply to reverse(begin()) as in my implementation reverse
**	keeps the base iterator, and not one-before-the-start.
*/

namespace ft
{
	
	template< class T, class Alloc = std::allocator<T> >
	class deque 
	{
	/*
	** ********************************************************************
	** Deque: typedefs section
	** ********************************************************************
	*/
		public:
		//TYPES
		typedef T											value_type;
		typedef Alloc										allocator_type;
		typedef typename allocator_type::reference			reference; 
		typedef typename allocator_type::const_reference	const_reference;
		typedef typename allocator_type::pointer			pointer;
		typedef typename allocator_type::const_pointer		const_pointer;	

		//ITERATORS
		typedef typename ft::deque_iterator<T, _SIZE_BLOCK>
			iterator;
		typedef typename ft::deque_iterator<T const, _SIZE_BLOCK>
			const_iterator;
		typedef typename ft::reverse_iterator<iterator>
			reverse_iterator;
		typedef typename ft::reverse_iterator<const_iterator>
			const_reverse_iterator;
		
		//OTHER
		typedef typename iterator_traits<iterator>::difference_type
			difference_type;
		typedef typename allocator_type::size_type
			size_type;

		//PROTECTED:
		protected:
		typedef pointer*									map_pointer;
		typedef std::allocator<pointer>						map_allocator_type;
			
	/*
	** ********************************************************************
	** Deque: data section
	** ********************************************************************
	*/
		private:
		allocator_type		_alloc;
		map_allocator_type	_alloc_block;

		iterator			_start;
		iterator			_end;

		map_pointer			_map;
		difference_type		_map_size;

	/*
	** ********************************************************************
	** Deque: constructors, destructor and copy section
	** ********************************************************************
	*/
		public:
		//default (1)
		explicit deque (const allocator_type& alloc = allocator_type()) :
			_alloc(alloc),
			_alloc_block(map_allocator_type()),
			_start(),
			_end(),
			_map(nullptr),
			_map_size(0)
		{
			if (DEBUG)
				std::cout << "\033[34m" <<
				"default constructor(deque)" <<
				"\033[0m" << std::endl;
		}

		//fill (2)
		explicit deque (size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) :
			_alloc(alloc),
			_alloc_block(map_allocator_type()),
			_start(),
			_end(),
			_map(nullptr),
			_map_size(0)
		{
			if (n == 0)
				return ;	
			//set the _map and _map_size, _start and _end, and builds bocks
			_build_map_and_blocks(n);
			_uninitialized_fill_n(_start, n, val);	
		}
		
		//range (3)
		template <class InputIterator>
		deque (InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last,
				const allocator_type& alloc = allocator_type()) :
			_alloc(alloc),
			_alloc_block(map_allocator_type())
		{
			difference_type size;
			distance(first, last, size);
			if (!size) //if the range is nill we do nothing.
				return;
			//set the _map and _map_size, _start and _end, and builds bocks
			_build_map_and_blocks(size);
			_uninitialized_copy(first, last, _start);
		}

		//copy (4)
		deque (const deque& x)
		{
			*this = x;
		}

		//destructor
		~deque(void)
		{
			clear();
		}
	
		//copy (1)	
		deque& operator= (const deque& x)
		{
			if (this != &x)
			{
				clear();
				if (x.empty()) //no need to reallocate memory.
					return *this;
				//set the _map and _map_size, _start and _end, and builds bocks
				_build_map_and_blocks(x.size());
				_uninitialized_copy(x._start, x._end, _start);
			}
			return *this;
		}

	/*
	** ********************************************************************
	** Deaue: iterators section
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
	** Deque: capacity section
	** ********************************************************************
	*/

		//Returns the maximum number of elements that the vector can hold.
		size_type	max_size() const
		{
			return (allocator_type().max_size());
		}

		//Returns whether the vector is empty (i.e. whether its size is 0).
		bool		empty() const { return (_start == _end); }

		//Returns the number of elements in the vector.
		size_type	size() const { return (_end - _start); }

		void resize (size_type n, value_type val = value_type())
		{
			if (n == size())
				return ;
			if (!size()) //if the resized container is empty.
			{
				*this = deque(n, val);
				return ;
			}
			if (!n) //need to destroy the container
			{
				clear();
				return ;
			}
			if (size() < n) //add val at the end n - size() times.
			{
				size_type nb_elem = n - size();
				difference_type nb_new_blocks = _nb_blocks_to_add(_end, nb_elem);
				if (nb_new_blocks) //need some new blocks
				{
					_try_shift_map(TO_LEFT, nb_new_blocks);
					//if YES => we need to resize the map
					if (nb_new_blocks + _nb_occupied_blocks() > _map_size)
						_upsize_map(nb_new_blocks, TO_RIGHT);
					_build_blocks(_end._block + 1 , nb_new_blocks);
				}	
				// build the new val objects starting at current end.
				_uninitialized_fill_n(_end, nb_elem, val);
				_end += nb_elem;
			}
			else //destroy size() - n elements at the end.
			{
				//never dealloc current block, and dealloc last if not current
				_destroy(_start + n, _end, NEVER, IF_NOT_FIRST);
				_end = _start + n;
			}
		}

	/*
	** ********************************************************************
	** Deque: Element access section
	** ********************************************************************
	*/
		//Returns a reference to the element at position n in the vector
		//container.
		reference		operator[] (size_type n) { return _start[n]; }
		const_reference	operator[] (size_type n) const { return _start[n]; }

		//Returns a reference to the first element in the vector.
		reference		front() { return (*_start); }

		const_reference	front() const { return (*_start); }

		//Returns a reference to the last element in the vector.
		reference		back() { return *(_end - 1); }

		const_reference	back() const { return *(_end - 1); }

		//Returns a reference to the element at position n in the vector.
		reference		at(size_type n)
		{
			if (n >= size())
				throw (std::out_of_range("deque"));
			return (_start[n]);
		}
		const_reference	at(size_type n) const
		{
			if (n >= size())
				throw (std::out_of_range("deque"));
			return (_start[n]);
		}

	/*
	** ********************************************************************
	** Deque: Modifiers section
	** ********************************************************************
	*/
		//range (1)
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last)
		{
			clear();
			difference_type size;
			distance(first, last, size);
			if (!size) //if the range is nill we do nothing.
				return;
			//set the _map and _map_size, _start and _end, and builds bocks
			_build_map_and_blocks(size);
			_uninitialized_copy(first, last, _start);
		}

		//fill (2)
		void assign (size_type n, const value_type& val)
		{
			clear();
			if (n == 0)
				return ;	
			//set the _map and _map_size, _start and _end, and builds bocks
			_build_map_and_blocks(n);
			_uninitialized_fill_n(_start, n, val);	
		}

		void push_back (const value_type& val)
		{	
			if (empty()) //we start with a map of 2.
			{
				_build_map_and_blocks(1);
				_uninitialized_fill_n(_start, 1, val);	
				return ;
			}	
			difference_type nb_new_blocks = _nb_blocks_to_add(_end, 1);
			if (nb_new_blocks) //need some new blocks
			{
				_try_shift_map(TO_LEFT, nb_new_blocks);
				//YES = we need to resize the map
				if (nb_new_blocks + _nb_occupied_blocks() > _map_size)
					_upsize_map(nb_new_blocks, TO_RIGHT);
				_build_blocks(_end._block + 1 , nb_new_blocks);
			}	
			_alloc.construct(_end._current, val);
			_end++;
		}

		void push_front (const value_type& val)
		{
			if (empty()) //we start with a map of 2.
			{
				_build_map_and_blocks(1);
				_uninitialized_fill_n(_start, 1, val);	
				return ;
			}		
			difference_type nb_new_blocks = _nb_blocks_to_add(_start, 1);
			if (nb_new_blocks) //need some new blocks
			{
				_try_shift_map(TO_RIGHT, nb_new_blocks);
				//YES = we need to resize the map
				if (nb_new_blocks + _nb_occupied_blocks() > _map_size)
					_upsize_map(nb_new_blocks, TO_LEFT);
				_build_blocks(_start._block - nb_new_blocks , nb_new_blocks);
			}	
			//fill data from _end , n times
			_start--;
			_alloc.construct(_start._current, val);
		}

		/*
		** destroys the last object, also deallocates block if not used anymore
		** deallocated _map if empty.
		** nb: in the gcc implementation, pop_front and pop_back when the
		** container is empty() produces UB.
		*/
		void pop_back()
		{
			if (empty())
				return;
			iterator tmp = _end;
			_end--;
			_alloc.destroy(_end._current);
			if (_end._block != tmp._block)
				_alloc.deallocate(tmp._first, _SIZE_BLOCK);
			if (empty())
			{
				_alloc.deallocate(_end._first, _SIZE_BLOCK);
				_alloc_block.deallocate(_map, _map_size);
			}
		}

		/*
		** destroys the first object, also deallocates block if not used
		** anymore deallocated _map if empty.
		*/
		void pop_front()
		{
			if (empty())
				return;
			iterator tmp = _start;
			_alloc.destroy(_start._current);
			_start++;
			if (_start._block != tmp._block)
				_alloc.deallocate(tmp._first, _SIZE_BLOCK);
			if (empty())
			{
				_alloc.deallocate(_end._first, _SIZE_BLOCK);
				_alloc_block.deallocate(_map, _map_size);
			}
		}

		//single element (1)
		iterator insert (iterator position, const value_type& val)
		{
			return (_insert_n_aux(position, 1, val));
		}

		//fill (2)
		void insert (iterator position, size_type n, const value_type& val)
		{
			_insert_n_aux(position, n, val);
		}

		//range (3)
		template <class InputIterator>
		void insert (iterator position, InputIterator first,
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last)
		{
			size_type n;
			distance(first, last, n);
			if (!n) // nothing to do
				return ;
			if (empty()) //we start with a map of 2.
			{
				_build_map_and_blocks(n);
				_uninitialized_copy(first, last, _start);
				return ;
			}	
			//saving the distance from _start to position.
			difference_type startToPosition;
			distance(_start, position, startToPosition);
			_make_space_for_insertion(n);
			//reset postion in case it got invalidated when upsizing the map.
			position = _start + startToPosition;
			if (position + n < _end)
			{
				_uninitialized_copy(_end - n, _end, _end);
				_copy_backwards(position, _end - n, _end);
				_initialized_copy(first, last, position);
			}	
			else
			{	
				difference_type endToLast = position + n - _end;
				_uninitialized_copy(position, _end, position + n);
				_initialized_copy(first, last - endToLast, position);
				_uninitialized_copy(last - endToLast, last, _end);
			}
			_end += n;
		}

		//Removes from the deque container a single element (position)
		iterator erase (iterator position)
		{
			_initialized_copy(position + 1, end(), position);
			_alloc.destroy(_end - 1);
			_end--;
			return (position);
		}

		//Removes from the deque container a range of elements ([first,last))
		//elements are removed(and destroyed) from first included, not last.
		iterator erase (iterator first, iterator last)
		{
			difference_type size_last_to_end;
			difference_type size_erase;
			distance(last, end(), size_last_to_end);
			distance(first, last, size_erase);
			_initialized_copy(last, end(), first);
			_destroy(first + size_last_to_end, _end, NEVER, IF_NOT_FIRST);
			_end = _end - size_erase;
			return (first);
		}

		//swaps the content the deques refers to.
		void swap (deque& x)
		{
			map_pointer tmp_map = _map;
			_map = x._map;
			x._map = tmp_map;
			size_type tmp_map_size = _map_size;
			_map_size = x._map_size;
			x._map_size = tmp_map_size;
			iterator tmp = _start;
			_start = x._start;
			x._start = tmp;
			tmp = _end;
			_end = x._end;
			x._end = tmp;
			map_allocator_type tmp_map_alloc = _alloc_block;
			_alloc_block = x._alloc_block;
			x._alloc_block = tmp_map_alloc;
			allocator_type tmp_alloc = _alloc;
			_alloc - x._alloc;
			x._alloc = tmp_alloc;
		}

		//Removes all elements from the deque (which are destroyed), leaving
		//the container with a size of 0.
		void clear()
		{
			if (empty())
				return ;
			//dealloc current and last blocks ALWAYS
			_destroy(_start, _end, ALWAYS, ALWAYS);
			_start = _end;
			_alloc_block.deallocate(_map, _map_size);
		}

	/*
	** ********************************************************************
	** Deque: private helper functions section
	** ********************************************************************
	*/
		private:

		/*
		** this private function will fill with val, on n occurences, a memory
		** chunk starting at start pointer in memory.
		*/
		void
		_uninitialized_fill_n(iterator start, size_type n, const value_type &val)
		{
			for (size_type i = 0; i < n; i++)
			{		
				_alloc.construct(start._current, val);
				start++;
			}
		}	

		/*
		** this private function will fill with val on n occurence a memory
		** chunk that is already initialized (need to destroy before
		** constructing).
		*/
		void
		_initialized_fill_n(iterator start, size_type n, const value_type &val)
		{
			for (size_type i = 0; i < n; i++)
			{		
				_alloc.destroy(start._current);
				_alloc.construct(start._current, val);
				start++;
			}
		}	

		/*
		** This private function will copy the elements found between the begin
		** and end input iterators, starting at the start location.
		** return: the element past the last element copied, or start if first
		**	and last parameter were equal at the beginning.
		** note: unitialized area, the memory does NOT need destruction.
		*/
		template <typename InputIterator>
		iterator
		_uninitialized_copy(InputIterator begin, InputIterator end, iterator start)
		{
			int i = 0;
			while (begin != end)	
			{
				_alloc.construct(start++._current, *begin++);
				i++;
			}
			return (start);
		}

		/*
		** This function will copy the elements found between the begin and end
		** input iterators (range).
		**
		** return: the element past the last element copied, or start if first
		**	and last parameter were equal at the beginning.
		** note: initialized area, the memory does need destruction. 
		*/
		template <typename InputIterator>
		InputIterator
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
		** starting at the (reverse_start - 1) location.
		** In the destination places, we know that there is already objects
		** constructed. So we destroy them as we go.
		**
		** note: the copy starts from the end of the range [first,last]
		*/
		void
		_copy_backwards(iterator first, iterator last, iterator reverse_start)
		{
			while (last > first)
			{
				--last;
				--reverse_start;
				_alloc.destroy(reverse_start._current);
				_alloc.construct(reverse_start._current, *last);
			}
		}


		/*
		** this helper function will create a new map, build the necessary
		** blocks inside it and assign the correct values to _start and _end
		** iterators.
		*/
		void	_build_map_and_blocks(size_type n)
		{
			size_type nb_new_blocks	= _nb_blocks_to_add(_start, n);
			if (nb_new_blocks % 2)
				_map_size = nb_new_blocks + 1; //always even
			else
				_map_size = nb_new_blocks;
			_map = _alloc_block.allocate(_map_size);
			_build_blocks(_map, nb_new_blocks);
			_start.set_block(_map);
			_start._current = _start._first;
			_end.set_block(_map + nb_new_blocks - 1);
			_end._current = _end._first + n % _SIZE_BLOCK;	
		}

		/*
		** this private fuction will destruct objects between a range of
		** pointers, [first, last).
		**
		** note: the 3nd parameter is an option, so that we control the 
		** 	deallocation of the first current block we are working on.
		** 	If set to one, we deallocate the first bloc	when done with it.
		**
		** note: the 4th parameter is used to decide if we deallocate the last
		** block. either:
		** 	- never (default)
		** 	- always (when clearing the container)
		** 	- or last block != first block(when resizing...).
		*/
		void
		_destroy(iterator first, iterator last, \
			int dealloc_first_block = NEVER, int dealloc_last_block = NEVER)
		{
			iterator cur = first;
			map_pointer tmp;
			int is_first = 1;
			while (cur != last)
			{
				tmp = cur._block;
				_alloc.destroy(cur._current);
				cur++;
				if (cur._block != tmp && (!is_first || dealloc_first_block))
					_alloc.deallocate(*tmp, _SIZE_BLOCK);
				//reset is_first to zero when changing to a new block.
				if (cur._block != tmp)
					is_first = 0;
			}
			if ((dealloc_last_block == IF_NOT_FIRST \
					&& cur._block != first._block) \
					|| dealloc_last_block == ALWAYS)
				_alloc.deallocate(last._first, _SIZE_BLOCK);
		}

		/*
		** This helper function will upsize the map by n blocks, and copy the
		** current blocks in the new map.
		*/
		void _upsize_map(difference_type nb_new_blocks, int left_right)
		{
			if (nb_new_blocks % 2)
				nb_new_blocks++; //make the number even.
			difference_type new_size = nb_new_blocks + _nb_occupied_blocks();
			map_pointer tmp = _alloc_block.allocate(new_size);
			difference_type offset;
			if (left_right == TO_RIGHT)	//add the new blocks to the end.
				offset = 0;
			else
				offset = nb_new_blocks;	
			for (difference_type n = 0; n < _map_size; n++)
			{
				tmp[n + offset] = _map[n];	
				if (_start._block == _map + n)
					_start._block = tmp + offset  + n;
				if (_end._block == _map + n)
					_end._block = tmp + offset + n;
			}
			_alloc_block.deallocate(_map, _map_size);
			_map = tmp;
			_map_size = new_size;
		}

		/*
		** this helper function will help balance the map, so that the unused
		** blocks are shifted to the left or to the right before they are
		** actually allocated and used to store data.
		**
		** exemple with 4 blocks:
		**		[unused][data..][data..][data..]
		**	if we add data to the back, the used blocks will be shifted to the
		**	left if needed (this is the case in this example). And the last
		**	block will be malloced and used.
		*/

		void _try_shift_map(int left_right, difference_type blocks_to_add)
		{
			//shift everything to the left, empty blocks end up on the right.
			if (left_right == TO_LEFT) 
			{
				difference_type distToStart = _start._block - _map;
				difference_type shift = std::min(blocks_to_add, distToStart);
				for (difference_type n = 0; n + shift < _map_size; n++)
				{
					pointer tmp = _map[n];
					_map[n] = _map[n + shift];
					_map[n + shift] = tmp;
				}
				_start._block -= shift; 
				_end._block -= shift;	
			}
			//shift everything to the right. empty blocks appear at the start
			else
			{
				difference_type distToEnd = _map + _map_size - 1 - _end._block;
				difference_type shift = std::min(blocks_to_add, distToEnd);
				for (difference_type n = _map_size - 1; n - shift >= 0; n--)
				{
					pointer tmp = _map[n];
					_map[n] = _map[n - shift];
					_map[n - shift] = tmp;
				}
				_start._block += shift; 
				_end._block += shift;
			}
		}

		/*
		** this helper function will malloc as many blocks as necessary
		** starting at the block_ptr location, n times.
		*/
		void _build_blocks(map_pointer block_ptr, difference_type nb_new_blocks)
		{
			for (difference_type n = 0; n < nb_new_blocks; n++)
				*(block_ptr + n)= _alloc.allocate(_SIZE_BLOCK);
		}
			
		/*
		** this helper function will calculate the number of blocks that we
		** will have to add on top of the existing ones to fit n new elements
		** at position.
		**
		** depending on the position if its equal to _start, the deque will
		** grow towards "the left" (_start._current is decreasing), otherwise
		** (any insertion other than at the _start._current) the deque will
		** grow towards "the right".
		**
		** note: if iterator _end is increased and reaches _end._last, it
		** automatically goes to the next block and tries to dereference it to
		** fill its "_first" field. So to avoid segfault, we will need to
		** allocate the memory for the next chunk (therefore create a new
		** block).
		**
		** note2: it doesnt apply to _start, as the reverse iterator if
		** fictive.
		*/
		difference_type _nb_blocks_to_add(iterator position, size_type n)
		{	
			if (empty())
				return (n / _SIZE_BLOCK + 1);
			//if _start will decrease as we will push to front.
			if (position == _start) 
			{
				difference_type offset = n - (_start._current - _start._first);
				//insertion before start but in same block.
				if (offset <= 0)
					return (0);
				else
					return (offset - 1) / _SIZE_BLOCK + 1;
			}
			else //_end will increase.
			{
				difference_type offset = n + (position._current - position._first);
				if (offset < _SIZE_BLOCK) //insertion in same block
					return (0);
				else
					return offset / _SIZE_BLOCK;
			}
		}

		/*
		** This helper function will take care of the insertion of n elements
		** If the current deque is not empty, we will first make sure all the
		** blocks are shifted to the left, and that the necessary space is
		** allocated before hand.
		** Then we will move the existing objects, and finally fill insertion
		** zone with n times value "val".
		*/
		iterator _insert_n_aux(iterator position, size_t n, const value_type& val)
		{
			if (empty()) //we start a new map
			{
				_build_map_and_blocks(n);
				_uninitialized_fill_n(_start, n, val);	
				return (begin());
			}	
			//saving the distance from _start to position.
			difference_type startToPosition;
			distance(_start, position, startToPosition);
			_make_space_for_insertion(n);
			//reset postion in case it got invalidated when upsizing the map.
			position = _start + startToPosition;
			if (position + n < _end)
			{
				_uninitialized_copy(_end - n, _end, _end);
				_copy_backwards(position, _end - n, _end);
				_initialized_fill_n(position, n, val);
			}	
			else
			{	
				_uninitialized_copy(position, _end, position + n);
				_initialized_fill_n(position, _end - position, val);
				_uninitialized_fill_n(_end, n - (_end - position), val);
			}
			_end += n;
			return (position);
		}

		/*
		** This helper function will calculate how many new blocks we will need
		** to increase the container's content by nb_elem new elements.
		** Then if will shift the blocks to the left if necessary, then it will
		** upsize the _map if neccessary, and allocate the memory of the new
		** blocks.
		*/
		void _make_space_for_insertion(size_type nb_elem)
		{
			difference_type nb_new_blocks = _nb_blocks_to_add(_end, nb_elem);
			if (nb_new_blocks) //need some new blocks
			{
				_try_shift_map(TO_LEFT, nb_new_blocks);
				if (nb_new_blocks + _nb_occupied_blocks() > _map_size)
					_upsize_map(nb_new_blocks, TO_RIGHT);
				_build_blocks(_end._block + 1 , nb_new_blocks);
			}	
		}
	
		/*
		** this private function returns the total number of blocks being
		** occupied right now by the data between _start and _end gauges.
		** 
		** note: if totally empty, we return 0.
		*/
		difference_type _nb_occupied_blocks(void)
		{
			if (empty())
				return (0);
			return (_end._block - _start._block + 1);
		}

		/*
		** ********************************************************************
		** Deque: Non-member function overloads section	(relational operators)
		** ********************************************************************
		*/
		//(1)	
		friend
		bool operator== (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
		{
			if (lhs.size() != rhs.size())
				return (false);			
			return (ft::equal(lhs._start, lhs._end, rhs._start));
		}

		//(3)	
		friend
		bool operator< (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
		{
			return (ft::lexicographical_compare(lhs._start, lhs._end, \
						rhs._start, rhs._end));		
		}
	};

	//(2)	
	template <class T, class Alloc>
	bool operator!= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		return (!operator==(lhs, rhs));
	}

	//(4)	
	template <class T, class Alloc>
	bool operator<= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		return (!operator<(rhs, lhs));
	}

	//(5)	
	template <class T, class Alloc>
	bool operator> (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}

	//(6)	
	template <class T, class Alloc>
	bool operator>= (const deque<T,Alloc>& lhs, const deque<T,Alloc>& rhs)
	{
		return (!operator<(lhs, rhs));
	}

	//swap function overload
	template <class T, class Alloc>
	void swap (deque<T,Alloc>& x, deque<T,Alloc>& y)
	{
		x.swap(y);
	}
}

#endif
