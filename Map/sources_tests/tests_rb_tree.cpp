/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_rb_tree.cpp                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/09 20:02:01 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/10 16:21:59 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef TESTS_RB_TREE_HPP
# define TESTS_RB_TREE_HPP

#include "functions_tests.hpp"
#include <iterator>
#include <sstream>
#include <map>

void	test_rb_tree_default_constructor(void)
{
	ft::rb_tree<test_class, test_class, std::less<test_class> > ft_cont;	
	assert(ft_cont.size() == 0);
}

void	test_rb_tree_copy_constructor(void)
{
	ft::rb_tree<int, int, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	assert(ft_cont.size() == 2);

	ft::rb_tree<int, int, std::less<int> > ft_cont2;	
	assert(ft_cont2.empty());
	ft_cont = ft_cont2;
	assert(ft_cont.empty());
}

void	test_rb_tree_range_constructor(size_t size)
{
	ft::rb_tree<int, int, std::less<int> > ft_cont;	
	//std::rb_tree<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
		ft_cont.insert_equal(i + 42);	

	ft::rb_tree<int, int, std::less<int> >::iterator ft_it = ft_cont.begin();
	//from start to end;
	ft::rb_tree<int, int, std::less<int> > ft_cont2(false, ft_it, ft_cont.end());

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
	ft::rb_tree<int, int, std::less<int> > ft_cont3(false, ft_it, ft_cont.end());
	assert(ft_cont3.size() == ft_cont.size() - (difference_in_size));
}

void	test_rb_tree_constructors()
{
	test_rb_tree_default_constructor();
	test_rb_tree_copy_constructor();
	test_rb_tree_range_constructor(0);
	test_rb_tree_range_constructor(1);
	test_rb_tree_range_constructor(2);
	test_rb_tree_range_constructor(3);
	test_rb_tree_range_constructor(10);
}

void	output_int_with_4_char(int num)
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
	//*const_it = 12;
	//const_std_it = const_std_cont.begin(); not possible
	//const2_std_it = const_std_it;
	//const_std_it = const2_std_it;
	//std_it = const_std_it;

	////////////////////////////////////////////

	ft::rb_tree<int, int, std::less<int> > ft_cont;	
	ft::rb_tree<const int, const int, std::less<const int> > const_ft_cont;	

	ft::rb_tree<int, int, std::less<int> >::iterator it;
	ft::rb_tree<const int, const int, std::less<const int> >::iterator const2_it;
	ft::rb_tree<int, int, std::less<int> >::const_iterator const_it;
	
	const_it = it;
	const2_it = const_ft_cont.begin();
	const_it = ft_cont.begin();
	//*const_it = 12;
	//const_it = const_ft_cont.begin(); //not possible
	//const2_it = const_it;
	//const_it = const2_it;
	//it = const_it;
} void	test_rb_tree_iteration1(void)
{
	ft::rb_tree<int, int, std::less<int> > ft_cont;	
	ft::rb_tree<int, int, std::less<int> >::iterator it = ft_cont.begin();
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
		ft::rb_tree<int, int, std::less<int> >::iterator tmp = it;
		if (++tmp == ft_cont.end())
			std::cout  << std::endl;
		else
			std::cout << ", ";
	}
}

void	test_rb_tree_iteration2(void)
{
	ft::rb_tree<int, int, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(2);
	ft_cont.insert_equal(3);
	assert(ft_cont.begin() == ft_cont.rend());
	assert(ft_cont.end() == ft_cont.rbegin());
}

void	test_rb_tree_reverse_iteration1(void)
{
	ft::rb_tree<int, int, std::less<int> > ft_cont;	
	ft::rb_tree<int, int, std::less<int> >::reverse_iterator it = ft_cont.rbegin();
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
		ft::rb_tree<int, int, std::less<int> >::reverse_iterator tmp = it;
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
	ft::rb_tree<int, int, std::less<int> > ft_cont;	

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
	ft_cont.insert_equal(8);
	ft_cont.insert_equal(9);
	ft_cont.insert_equal(33);
	ft_cont.insert_equal(34);
	ft_cont.insert_equal(35);
	ft_cont.insert_equal(36);
	ft_cont.rb_tree_debug(output_int_with_4_char);
}


//tests that we can insert multiple elements that have the same key.
void	test_rb_tree_insert_equal(void)
{
	ft::rb_tree<int, int, std::less<int> > ft_cont;	
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(1);
	ft_cont.insert_equal(1);
	assert(ft_cont.size() == 3);
	ft_cont.rb_tree_debug(output_int_with_4_char);
}

//tests that we can insert only unique elements (no two same keys possible!).
void	test_rb_tree_insert_unique(void)
{
	ft::rb_tree<int, int, std::less<int> > ft_cont;	
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

void tests_rb_tree(void)
{	
	test_rb_tree_constructors();
	test_rb_tree_iterator_conversions();
	test_rb_tree_iteration();

	test_rb_tree_insert();
	test_rb_tree_insert_equal();
	test_rb_tree_insert_unique();

	//NOT DONE YET
	/*
	tests_iterator_conversions();
	tests_list_constructors();
	test_reverse_iteration(0);
	test_reverse_iteration(12);
	tests_list_push_back_and_front();
	tests_list_pop_back_and_front();
	tests_front_and_back();
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
