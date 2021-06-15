/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   multiset.hpp                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:10:25 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/15 03:11:16 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MULTISET_HPP
# define MULTISET_HPP

#include "ft_utils.hpp"
#include <functional> //for std::less , it covers also std::pair
# include "rb_tree.hpp"

/*
** The class multiset, is inheriting from the class rb_tree.
** Among the rb_tree's template parameters, a special function object is given 
** in place of KeyOfValue (3rd template parameter). It allows the rb_tree class
** to extract the element required by the function objet Compare, out of the
** "value_type" (a pair in map and multimap, a single element in set and
** multiset). This allows genericity. The same base class (rb_tree) can be used
** for map, multimap, set and multiset.
**
** In the case of map and multimap, the function _Select1st extracts the
** first_type out of an std::pair<first_type, second_type>. In the case of set
** and multiset, the function object std::identity<type> will give the
** parameter type itself.
*/

namespace ft
{
	template<	class T, \
				class Compare = std::less<T>, \
				class Alloc = std::allocator<T> >
	class multiset
	{
	/*
	** ********************************************************************
	** Map: typedefs section
	** ********************************************************************
	*/
		private:
		//the node of the rb_tree, containing the Value in question.
		typedef ft::rb_tree_node< std::pair<const T, T> >	node_type;
		typedef node_type*									node_pointer;
		typedef std::allocator<node_type> 					node_allocator_type;

		public:
		//key_type:			the type of the key in the key value pair.
		typedef T											key_type;
		//value_type:		the type of elements contained in the Node
		typedef	T											value_type;

		//the underlying tree storing the data.
		private:
		typedef ft::identity<value_type>					KeyOfValue;
		typedef ft::rb_tree< key_type, value_type, KeyOfValue, Compare, Alloc> \
															multiset_tree;

		public:
		//value_compare:	a function object that allows to compare 2 value_type
		typedef Compare										value_compare;
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
		typedef typename multiset_tree::const_iterator			iterator;
		typedef typename multiset_tree::const_iterator			const_iterator;
		typedef typename multiset_tree::reverse_iterator		reverse_iterator;
		typedef typename multiset_tree::const_reverse_iterator	const_reverse_iterator;

		//OTHER
		typedef typename iterator_traits<iterator>::difference_type \
															difference_type;
		typedef typename node_allocator_type::size_type		size_type;
	/*
	** ********************************************************************
	** Map: data section
	** ********************************************************************
	*/
		private:
		multiset_tree tree;

	/*
	** ********************************************************************
	** Map: constructors, destructor and copy section
	** ********************************************************************
	*/
		public:
		//CONSTRUCTORS
		//empty (1)
		explicit multiset (const key_compare& comp = key_compare(),
				const allocator_type& alloc = allocator_type())
		{
			tree = multiset_tree(KeyOfValue(), comp, alloc);
		}

		//range (2)
		template <class InputIterator>
		multiset (InputIterator first, InputIterator last,
					const key_compare& comp = key_compare(),
					const allocator_type& alloc = allocator_type())
		{
			tree = multiset_tree(true, first, last, KeyOfValue(), comp, alloc);
		}

		//copy (3)
		multiset (const multiset& x)
		{
			tree = multiset_tree(x.tree);
		}

		//operator = (1)
		 multiset& operator= (const multiset& x)
		 {
			if (&tree != &x.tree)
				tree = x.tree;
			return (*this);
		 }

		 //destructor
		~multiset()
		{
		}

	/*
	** ********************************************************************
	** Map: iterators section
	** ********************************************************************
	*/
		//Returns an iterator pointing to the first element of the tree, the
		//one that is the leftmost if we did an inorder traversal.
		iterator				begin() { return (tree.begin()); }
		const_iterator			begin() const { return (tree.begin()); }
		
		//Returns an iterator referring to the past-the-end element in the
		//vector container.
		iterator				end() { return tree.end(); }
		const_iterator			end() const { return tree.end(); }

		//Returns a reverse iterator pointing to the last element in the vector
		//(i.e., its reverse beginning).
		reverse_iterator		rbegin() { return tree.rbegin(); }
		const_reverse_iterator	rbegin() const { return tree.rbegin(); }

		//Returns a reverse iterator pointing to the theoretical element
		//preceding the first element in the vector (which is considered its
		//reverse end).
		reverse_iterator 		rend() { return tree.rend(); }
		const_reverse_iterator	rend() const { return tree.rend(); }

	/*
	** ********************************************************************
	** Map: capacity section
	** ********************************************************************
	*/
		//Returns the maximum number of elements that the vector can hold.
		size_type	max_size() const { return tree.max_size(); }

		//Returns whether the vector is empty (i.e. whether its size is 0).
		bool		empty() const { return tree.empty(); }

		//Returns the number of elements in the vector.
		size_type	size() const { return tree.size(); }

	/*
	** ********************************************************************
	** Map: Modifiers section
	** ********************************************************************
	*/
		//single element (1)
		std::pair<iterator,bool> insert (const value_type& val)
		{
			typename multiset_tree::t_insert_info info;	
			info = tree.insert_unique(val);
			return (std::pair<iterator, bool>(info.iter_to_return, info.insert_successful));
		}

		//with hint (2)
		iterator insert (iterator position, const value_type& val)
		{
			//fuck the hint	
			(void)position;
			typename multiset_tree::t_insert_info info;	
			info = tree.insert_unique(val);
			return (info.iter_to_return);
		}

		//range (3)
		template <class InputIterator>
		void insert (InputIterator first,  \
			typename ft::enable_if< is_iterator<InputIterator>::value &&
			is_input_iterator<InputIterator>::value, InputIterator>::type last)
		{
			typename multiset_tree::t_insert_info info;	
			for (;first != last; ++first)
				info = tree.insert_unique(*first);
		}

		//(1)
		void erase (iterator position) { tree.erase(position); }
		//(2)
		size_type erase (const key_type& k) { return (tree.erase(k)); }
		//(3)
		void erase (iterator first, iterator last) { tree.erase(first, last); }

		void swap (multiset& x)
		{
			tree.swap(x.tree);
		}

		//clear
		void clear() { tree.clear(); }

	/*
	** ********************************************************************
	** Map: Observers section
	** ********************************************************************
	*/
		key_compare key_comp() const { return (tree.key_comp()); }

		value_compare value_comp() const { return (tree.value_comp()); }

	/*
	** ********************************************************************
	** Map: Operations functions section
	** ********************************************************************
	*/
		iterator find (const key_type& k) { return tree.find(k); }

		const_iterator find (const key_type& k) const { return tree.find(k); }

		size_type count (const key_type& k) const { return tree.count(k); }

		//lowe_bound
		iterator lower_bound (const key_type& k) { return tree.lower_bound(k); }

		const_iterator lower_bound (const key_type& k) const
		{
			return tree.lower_bound(k);
		}

		//upper_bound
		iterator upper_bound (const key_type& k) { return tree.upper_bound(k); }

		const_iterator upper_bound (const key_type& k) const
		{
			return tree.upper_bound(k);
		}

		//equal_range
		std::pair<const_iterator,const_iterator>
		equal_range (const key_type& k) const { return tree.equal_range(k); }

		std::pair<iterator,iterator>      
		equal_range (const key_type& k) { return tree.equal_range(k); }

	/*
	** ********************************************************************
	** Map: public helper functions section, DEBUGGING section.
	** ********************************************************************
	*/
		// [Mon 14/06/2021 at 19:48:25]
		//TODO (charmstr): remove at the END, or leave it for peer correction
		/*
		void debug(void (*display)(const key_type&))
		{
			return (tree.rb_tree_debug(display));	
		}
		*/
	};
}

#endif
