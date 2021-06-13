/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_rb_tree.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 20:02:01 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/13 08:28:53 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_RB_TREE_HPP
# define TESTS_RB_TREE_HPP

#include "functions_tests.hpp"
#include <iterator>
#include <sstream>
#include <map>

template <typename T>
class identity
{
	public:
	T&operator()(T& t) const
	{
		return (t);
	}
};

template <class _Pair>
struct _Select1st : public std::unary_function<_Pair,
                      typename _Pair::first_type>
{
  typename _Pair::first_type&
  operator()(_Pair& __x) const
  { return __x.first; }

  const typename _Pair::first_type&
  operator()(const _Pair& __x) const
  { return __x.first; }
};

void	output_int_with_4_char(const int &num)
{
	size_t i = 0;
	std::stringstream ss;
	std::string str;
	ss << num;
	ss >> str;

	while (i < (SIZE_LEAF_DEBUG - 2) && i < str.length())
	{
		std::cout << str.c_str()[i];
		i++;
	}
	while (i++ < SIZE_LEAF_DEBUG - 2)
		std::cout << " ";
}

void	output_string_with_4_char(const std::string &str)
{
	size_t i = 0;
	while (i < (SIZE_LEAF_DEBUG - 2) && i < str.length())
	{
		std::cout << str.c_str()[i];
		i++;
	}
	while (i++ < SIZE_LEAF_DEBUG - 2)
		std::cout << " ";
}

void	test_rb_tree_default_constructor1(void)
{
	ft::rb_tree<test_class, test_class, identity<test_class >, std::less<test_class> > ft_cont;	
	assert(ft_cont.size() == 0);
}

void	test_rb_tree_default_constructor2(void)
{
	ft::rb_tree<std::string, std::pair<std::string, int>, _Select1st<std::pair<std::string, int> >, std::less<std::string> > ft_cont;
	std::pair<std::string, int> pair("hey", 2);
	std::pair<std::string, int> pair2("hoy", 3);
	ft_cont.insert_equal(pair);
	ft_cont.insert_equal(pair);
	ft_cont.insert_equal(pair2);
	//ft_cont.print_first_of();
	assert(ft_cont.count("hey") == 2);
	assert(ft_cont.count("hoy") == 1);	
	assert(ft_cont.count("") == 0);	
	assert(ft_cont.count("heyy") == 0);	
	ft_cont.rb_tree_debug(output_string_with_4_char);
}

void	test_rb_tree_copy_constructor(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	ft_cont.insert_equal(3);
	ft_cont.insert_equal(4);
	ft_cont.insert_equal(5);
	assert(ft_cont.size() == 5);
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont2(ft_cont);
	assert(ft_cont.size() == ft_cont2.size());
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont2.rb_tree_debug(output_int_with_4_char);
}

void	test_rb_tree_operator_equal_constructor()
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	assert(ft_cont.size() == 2);

	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont2;	
	assert(ft_cont2.empty());
	ft_cont = ft_cont2;
	assert(ft_cont.empty());
}

void	test_rb_tree_range_constructor(size_t size)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	//std::rb_tree<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
		ft_cont.insert_equal(i + 42);	

	ft::rb_tree<int, int, identity<int>, std::less<int> >::iterator ft_it = ft_cont.begin();
	//from start to end;
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont2(false, ft_it, ft_cont.end());

	assert(ft_cont2.size() == ft_cont.size());

	int difference_in_size = 0;
	if (size >= 1)
	{
		difference_in_size = 1;
		ft_it++;
	}
	if (size >= 2)
	{
		difference_in_size = 2;
		ft_it++;
	}
	//from non start to end
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont3(false, ft_it, ft_cont.end());
	assert(ft_cont3.size() == ft_cont.size() - (difference_in_size));
}

void	test_rb_tree_constructors()
{
	test_rb_tree_default_constructor1();
	test_rb_tree_default_constructor2();
	/*
	test_rb_tree_operator_equal_constructor();
	test_rb_tree_copy_constructor();
	test_rb_tree_range_constructor(0);
	test_rb_tree_range_constructor(1);
	test_rb_tree_range_constructor(2);
	test_rb_tree_range_constructor(3);
	test_rb_tree_range_constructor(10);
	*/
}

void	test_rb_tree_iterator_conversions(void)
{
	std::map<int, int>							std_cont;
	std::map<const int, const int>				const_std_cont;

	std::map<int, int>::iterator				std_it;
	std::map<const int, const int>::iterator	const2_std_it;
	std::map<int, int>::const_iterator			const_std_it;

	const_std_it = std_it;
	const2_std_it = const_std_cont.begin();
	const_std_it = std_cont.begin();
	// *const_it = 12;
	//const_std_it = const_std_cont.begin(); not possible
	//const2_std_it = const_std_it;
	//const_std_it = const2_std_it;
	//std_it = const_std_it;

	////////////////////////////////////////////

	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft::rb_tree<const int, const int, identity<const int>, std::less<const int> > const_ft_cont;	

	ft::rb_tree<int, int, identity<int>, std::less<int> >::iterator it;
	ft::rb_tree<const int, const int,  identity<const int>, std::less<const int> >::iterator const2_it;
	ft::rb_tree<int, int, identity<int>, std::less<int> >::const_iterator const_it;
	
	const_it = it;
	const2_it = const_ft_cont.begin();
	const_it = ft_cont.begin();
	// *const_it = 12;
	//const_it = const_ft_cont.begin(); //not possible
	//const2_it = const_it;
	//const_it = const2_it;
	//it = const_it;
}

void	test_rb_tree_iteration1(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft::rb_tree<int, int, identity<int>, std::less<int> >::iterator it = ft_cont.begin();
	assert(it == ft_cont.end());
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	ft_cont.insert_equal(4);
	ft_cont.insert_equal(5);
	ft_cont.insert_equal(3);
	ft_cont.insert_equal(-1);
	ft_cont.insert_equal(-2);
	ft_cont.insert_equal(0);
	it = ft_cont.begin();
	for (; it != ft_cont.end(); ++it)
	{
		std::cout << *it;
		ft::rb_tree<int, int, identity<int>, std::less<int> >::iterator tmp = it;
		if (++tmp == ft_cont.end())
			std::cout  << std::endl;
		else
			std::cout << ", ";
	}
}

void	test_rb_tree_iteration2(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	ft_cont.insert_equal(3);
	assert(ft_cont.begin() == ft_cont.rend());
	assert(ft_cont.end() == ft_cont.rbegin());
}

void	test_rb_tree_reverse_iteration1(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft::rb_tree<int, int, identity<int>, std::less<int> >::reverse_iterator it = ft_cont.rbegin();
	assert(it == ft_cont.end());
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	ft_cont.insert_equal(4);
	ft_cont.insert_equal(5);
	ft_cont.insert_equal(3);
	ft_cont.insert_equal(-1);
	ft_cont.insert_equal(-2);
	ft_cont.insert_equal(0);
	it = ft_cont.rbegin();
	for (; it != ft_cont.rend(); ++it)
	{
		std::cout << *it;
		ft::rb_tree<int, int, identity<int>, std::less<int> >::reverse_iterator tmp = it;
		if (++tmp == ft_cont.rend())
			std::cout  << std::endl;
		else
			std::cout << ", ";
	}
}

void	test_rb_tree_iteration(void)
{
	test_rb_tree_iteration1();
	test_rb_tree_iteration2();
	test_rb_tree_reverse_iteration1();
}

void test_rb_tree_insert(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	

	ft_cont.insert_equal(3);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(10);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(11);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(12);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(20);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(6);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont.size() == 6);
	ft_cont.insert_equal(7);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(8);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(9);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(33);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(34);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(35);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(36);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(37);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(38);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(39);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(40);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	ft_cont.insert_equal(41);
	ft_cont.rb_tree_debug(output_int_with_4_char);
}


//tests that we can insert multiple elements that have the same key.
void	test_rb_tree_insert_equal(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(1);
	assert(ft_cont.size() == 3);
	ft_cont.rb_tree_debug(output_int_with_4_char);
}

//tests that we can insert only unique elements (no two same keys possible!).
void	test_rb_tree_insert_unique(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft_cont.insert_unique(1);
	ft_cont.insert_unique(1);
	ft_cont.insert_unique(1);
	assert(ft_cont.size() == 1);
	ft_cont.insert_unique(2);
	ft_cont.insert_unique(1);
	assert(ft_cont.size() == 2);
	ft_cont.insert_unique(3);
	ft_cont.insert_unique(2);
	assert(ft_cont.size() == 3);
	ft_cont.insert_unique(4);
	ft_cont.insert_unique(1);
	ft_cont.insert_unique(2);
	ft_cont.insert_unique(3);
	assert(ft_cont.size() == 4);
	ft_cont.rb_tree_debug(output_int_with_4_char);
}

void	test_rb_tree_count(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(1);
	assert(ft_cont.size() == 3);
	assert(ft_cont.count(1) == 3);
	assert(ft_cont.count(2) == 0);

	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont2;	
	ft_cont2.insert_unique(1);
	ft_cont2.insert_unique(2);
	ft_cont2.insert_unique(2);
	ft_cont2.insert_unique(1);
	assert(ft_cont2.count(0) == 0);
	assert(ft_cont2.count(1) == 1);
	assert(ft_cont2.count(2) == 1);
	assert(ft_cont2.count(3) == 0);
}
void	test_rb_tree_find(void)
{	
	// ---- non const ----
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	ft_cont.insert_equal(3);
	ft_cont.insert_equal(4);
	ft_cont.insert_equal(5);
	ft_cont.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont.find(0) == ft_cont.end());
	assert(ft_cont.find(1) != ft_cont.end());
	assert(ft_cont.find(2) != ft_cont.end());
	assert(ft_cont.find(3) != ft_cont.end());
	assert(ft_cont.find(4) != ft_cont.end());
	assert(ft_cont.find(5) != ft_cont.end());
	assert(ft_cont.find(6) == ft_cont.end());

	// ---- const test ----
	ft::rb_tree<const int, const int, identity<const int>, std::less<const int> > const_ft_cont;
	const_ft_cont.insert_equal(1);
	const_ft_cont.insert_equal(2);
	const_ft_cont.insert_equal(3);
	const_ft_cont.insert_equal(4);
	const_ft_cont.insert_equal(5);
	//const_ft_cont.rb_tree_debug(output_int_with_4_char);
	assert(const_ft_cont.find(0) == const_ft_cont.end());
	assert(const_ft_cont.find(1) != const_ft_cont.end());
	assert(const_ft_cont.find(2) != const_ft_cont.end());
	assert(const_ft_cont.find(3) != const_ft_cont.end());
	assert(const_ft_cont.find(4) != const_ft_cont.end());
	assert(const_ft_cont.find(5) != const_ft_cont.end());
	assert(const_ft_cont.find(6) == const_ft_cont.end());
}

void	test_rb_tree_lower_bound(void)
{	
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	ft_cont.insert_equal(3);
	ft_cont.insert_equal(4);
	ft_cont.insert_equal(5);
	assert(*ft_cont.lower_bound(3) == 3);
	assert(ft_cont.lower_bound(0) == ft_cont.find(1));
	assert(ft_cont.lower_bound(-1) == ft_cont.find(1));
	assert(ft_cont.lower_bound(2) == ft_cont.find(2));
	assert(ft_cont.lower_bound(6) == ft_cont.end());
}

void	test_rb_tree_upper_bound(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	ft_cont.insert_equal(3);
	ft_cont.insert_equal(4);
	ft_cont.insert_equal(4);
	ft_cont.insert_equal(4);
	ft_cont.insert_equal(5);
	assert(ft_cont.upper_bound(-1) == ft_cont.find(1));
	assert(ft_cont.upper_bound(0) == ft_cont.find(1));
	assert(ft_cont.upper_bound(1) == ft_cont.find(2));
	assert(ft_cont.upper_bound(2) == ft_cont.find(3));
	assert(ft_cont.upper_bound(4) == ft_cont.find(5));
	assert(ft_cont.upper_bound(5) == ft_cont.end());
	assert(ft_cont.upper_bound(6) == ft_cont.end());
}

void	tests_rb_tree_bound(void)
{
	test_rb_tree_lower_bound();
	test_rb_tree_upper_bound();
}

void	tests_rb_tree_equal_range(void)
{
	typedef ft::rb_tree<int, int, identity<int>, std::less<int> >::iterator it;
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont;
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	ft_cont.insert_equal(3);
	ft_cont.insert_equal(4);
	ft_cont.insert_equal(5);
	ft_cont.insert_equal(5);
	ft_cont.insert_equal(5);
	ft_cont.insert_equal(6);
	std::pair<it, it> my_pair1 = ft_cont.equal_range(4);
	assert(*(my_pair1.first) == 4);
	assert(*(my_pair1.second) == 5);
	std::pair<it, it> my_pair2 = ft_cont.equal_range(5);
	assert(my_pair2.first == ft_cont.find(5));
	assert(my_pair2.second == ft_cont.find(6));
	assert(*(my_pair2.second) == 6);
	std::pair<it, it> my_pair3 = ft_cont.equal_range(6);
	assert(my_pair3.first == ft_cont.find(6));
	assert(my_pair3.second == ft_cont.end());
	std::pair<it, it> my_pair4 = ft_cont.equal_range(7);
	assert(my_pair4.first == ft_cont.end());
	assert(my_pair4.second == ft_cont.end());
	std::pair<it, it> my_pair5 = ft_cont.equal_range(-1);
	assert(my_pair5.first == ft_cont.begin());
	assert(my_pair5.second == ft_cont.find(1));
}

void	test_rb_tree_swap(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont1;
	ft_cont1.insert_equal(1);
	ft_cont1.insert_equal(2);
	ft_cont1.insert_equal(3);
	ft_cont1.insert_equal(4);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(6);
	//asserts to be reused
	assert(ft_cont1.size() == 8);
	assert(*ft_cont1.begin() == 1);
	assert(*(--ft_cont1.end()) == 6);

	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont2;
	ft_cont2.insert_equal(10);
	ft_cont2.insert_equal(12);
	ft_cont2.insert_equal(13);
	ft_cont2.insert_equal(14);
	ft_cont2.insert_equal(15);
	ft_cont2.insert_equal(16);
	//asserts to be reused
	assert(ft_cont2.size() == 6);
	assert(*ft_cont2.begin() == 10);
	assert(*(--ft_cont2.end()) == 16);

	//swap
	ft_cont1.swap(ft_cont2);

	assert(ft_cont1.size() == 6);
	assert(*ft_cont1.begin() == 10);
	assert(*(--ft_cont1.end()) == 16);

	assert(ft_cont2.size() == 8);
	assert(*ft_cont2.begin() == 1);
	assert(*(--ft_cont2.end()) == 6);
}

void	test_rb_tree_erase2(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont1;
	ft_cont1.insert_equal(1);
	ft_cont1.insert_equal(2);
	ft_cont1.insert_equal(3);
	ft_cont1.insert_equal(4);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(6);
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	//asserts to be reused
	assert(ft_cont1.size() == 12);

	size_t res;
	res = ft_cont1.erase(2);
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(res == 1);
	assert(ft_cont1.size() == 11);

	res = ft_cont1.erase(5);
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(res == 7);
	assert(ft_cont1.size() == 4);
}

void	test_rb_tree_erase1(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont1;
	ft_cont1.insert_equal(1);
	ft_cont1.insert_equal(2);
	ft_cont1.insert_equal(3);
	ft_cont1.insert_equal(4);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(6);
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 8);
	ft_cont1.erase(ft_cont1.find(5));
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 7);
	ft_cont1.erase(ft_cont1.find(5));
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 6);
	ft_cont1.erase(ft_cont1.find(5));
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 5);
	ft_cont1.erase(ft_cont1.find(5));
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 5);
}

void	test_rb_tree_erase3(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont1;
	ft_cont1.insert_equal(1);
	ft_cont1.insert_equal(2);
	ft_cont1.insert_equal(3);
	ft_cont1.insert_equal(4);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(6);
	ft_cont1.insert_equal(7);

	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 9);

	ft_cont1.erase(ft_cont1.find(2), ft_cont1.find(6));
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 3);
}

void	test_rb_tree_erase4(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont1;
	ft_cont1.insert_equal(1);
	ft_cont1.insert_equal(2);
	ft_cont1.insert_equal(3);
	ft_cont1.insert_equal(4);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(6);
	ft_cont1.insert_equal(7);

	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 9);

	ft_cont1.erase(ft_cont1.find(2), ft_cont1.lower_bound(5));
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 6);
}

void	test_rb_tree_erase5(void)
{
	ft::rb_tree<int, int, identity<int>, std::less<int> > ft_cont1;
	ft_cont1.insert_equal(1);
	ft_cont1.insert_equal(1);
	ft_cont1.insert_equal(1);
	ft_cont1.insert_equal(1);
	ft_cont1.insert_equal(2);
	ft_cont1.insert_equal(3);
	ft_cont1.insert_equal(4);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(5);
	ft_cont1.insert_equal(6);
	ft_cont1.insert_equal(7);
	ft_cont1.insert_equal(7);
	ft_cont1.insert_equal(7);
	ft_cont1.insert_equal(7);

	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 15);

	ft_cont1.erase(ft_cont1.find(1), ft_cont1.lower_bound(3));
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 10);

	//should do nothing
	ft_cont1.erase(ft_cont1.find(1), ft_cont1.lower_bound(3));
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 10);

	ft_cont1.erase(ft_cont1.find(6), ft_cont1.upper_bound(7));
	ft_cont1.rb_tree_debug(output_int_with_4_char);
	assert(ft_cont1.size() == 5);
}


void	tests_rb_tree_erase(void)
{
	test_rb_tree_erase2();	
	test_rb_tree_erase1();	
	//
	test_rb_tree_erase3();
	test_rb_tree_erase4();
	test_rb_tree_erase5();
}

void tests_rb_tree(void)
{	
	test_rb_tree_constructors();
	test_rb_tree_iterator_conversions();
	test_rb_tree_iteration();

	test_rb_tree_insert();
	test_rb_tree_insert_equal();
	test_rb_tree_insert_unique();
	test_rb_tree_count();
	test_rb_tree_find();
	tests_rb_tree_bound();
	tests_rb_tree_equal_range();
	test_rb_tree_swap();
	tests_rb_tree_erase();

	//NOT DONE YET
	/*
	tests_assign();
	tests_insert_if();
	tests_erase();
	tests_swap();
	tests_resize();
	tests_splice();
	tests_remove();
	tests_list_reverse();
	tests_list_sort();
	tests_unique();
	tests_list_merge();
	list_test_relational_operators(12);
	*/

	std::cout << "\033[32m [ OK ]\033[m" << std::endl;	
}

#endif
