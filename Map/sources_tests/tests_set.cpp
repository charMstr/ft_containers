/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_set.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 02:47:00 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/15 03:12:02 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"
#include <set>

void	test_set_default_constructor1(void)
{
	ft::set<std::string> ft_cont;	
	assert(ft_cont.size() == 0);
}

void	test_set_copy_constructor(void)
{
	ft::set<std::string> ft_cont;	
	ft_cont.insert("aaaaa");
	ft_cont.insert("eeeee123");
	ft_cont.insert("iiiiiii");
	ft_cont.insert("ooooo");
	ft_cont.insert("uuuu");
	assert(ft_cont.size() == 5);
	ft::set<std::string> ft_cont2(ft_cont);
	assert(ft_cont.size() == ft_cont2.size());
//	ft_cont.debug(output_string_with_4_char);
//	ft_cont2.debug(output_string_with_4_char);
}

void	test_set_operator_equal_constructor()
{
	ft::set<std::string> ft_cont;	
	ft_cont.insert("aaaaa");
	ft_cont.insert("eeeee123");
	assert(ft_cont.size() == 2);

	ft::set<std::string> ft_cont2;	
	assert(ft_cont2.empty() == true);
	ft_cont = ft_cont2;
	assert(ft_cont.empty());
}

void	test_set_range_constructor(size_t size)
{
	ft::set<int> ft_cont1;	
	
	for (size_t i = 0; i < size; i++)
		ft_cont1.insert(i);	

	ft::set<int>::iterator ft_it = ft_cont1.begin();

	//from start to end;
	ft::set<int> ft_cont2(ft_it, ft_cont1.end());

	assert(ft_cont2.size() == ft_cont1.size());

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
	ft::set<int> ft_cont3(ft_it, ft_cont1.end());
	assert(ft_cont3.size() == ft_cont1.size() - (difference_in_size));
}

void	tests_set_constructors()
{
	test_set_default_constructor1();
	test_set_copy_constructor();
	test_set_operator_equal_constructor();
	test_set_range_constructor(0);
	test_set_range_constructor(1);
	test_set_range_constructor(2);
	test_set_range_constructor(3);
	test_set_range_constructor(10);
}

void	test_set_insert_single_element(void)
{
	std::pair<ft::set<int>::iterator, bool> result;
	ft::set<int> ft_cont1;	

	result = ft_cont1.insert(1);
	assert(result.second == true);
	assert(result.first == ft_cont1.begin());

	result = ft_cont1.insert(1);
	assert(result.second == false);
	assert(result.first == ft_cont1.begin());

	result = ft_cont1.insert(2);
	assert(result.second == true);
	assert(result.first == ++ft_cont1.begin());
}

void	test_set_insert_range(void)
{
	std::set<int> std_cont;

	//inserting three nodes to the std container
	std_cont.insert(1);

	std_cont.insert(2);

	std_cont.insert(3);

	ft::set<int> ft_cont2;	
	std::set<int> std_cont2;	
	ft_cont2.insert(std_cont.begin(), std_cont.end());
	std_cont2.insert(std_cont.begin(), std_cont.end());
	assert(*ft_cont2.begin() == *std_cont2.begin());
	assert(*(++ft_cont2.begin()) == *(++std_cont2.begin()));
	assert(ft_cont2.size() == std_cont2.size());
	assert(*(--ft_cont2.end()) == *(--std_cont2.end()));
}


void	tests_set_insert(void)
{
	test_set_insert_single_element();
	test_set_insert_range();
}

void	test_set_erase_range1(size_t size)
{
	ft::set<int, std::string> ft_cont1;	

	//inserting three nodes to the std container
	for (size_t i = 0; i < size; i++)
		ft_cont1.insert(i);

	//erase all but last
	assert(ft_cont1.size() == size);
	//ft_cont1.debug(output_int_with_4_char);
	ft_cont1.erase(ft_cont1.begin(), --ft_cont1.end());
	//ft_cont1.debug(output_int_with_4_char);
	if (size)
		assert(ft_cont1.size() == 1);
	//erase last
	ft_cont1.erase(ft_cont1.begin(), ft_cont1.end());
	assert(ft_cont1.empty());
}

void	test_set_erase_range2(size_t size)
{
	ft::set<int, std::string> ft_cont1;	

	//inserting three nodes to the std container
	for (size_t i = 0; i < size; i++)
		ft_cont1.insert(i);

	//erase all but last
	assert(ft_cont1.size() == size);
	//ft_cont1.debug(output_int_with_4_char);
	ft::set<int, std::string>::iterator it = ft_cont1.begin();
	for (size_t j = 0; j < size && j < 5; ++j)
	{
		it++;
	}
	assert(ft_cont1.size() == size);
	//skipping the first one.
	ft_cont1.erase(++ft_cont1.begin(), it);
	if (size <= 5)
		assert(ft_cont1.size() == 1);
	else
		assert(ft_cont1.size() == size - 5 + 1);
	//ft_cont1.debug(output_int_with_4_char);
}

void	tests_set_erase(void)
{
	test_set_erase_range1(0);
	test_set_erase_range1(1);
	test_set_erase_range1(2);
	test_set_erase_range1(3);
	test_set_erase_range1(4);
	test_set_erase_range1(14);
	test_set_erase_range1(15);
	test_set_erase_range2(4); 
	test_set_erase_range2(5); 
	test_set_erase_range2(6); 
	test_set_erase_range2(8); 
	test_set_erase_range2(9); 
}
void	test_set_swap(void)
{	

	ft::set<int, std::string> ft_cont1;	
	//inserting 20 nodes to the std container
	for (size_t i = 0; i < 20; i++)
		ft_cont1.insert(i);

	ft::set<int, std::string> ft_cont2;	
	//inserting 12 nodes to the std container
	for (size_t i = 42; i < 12 + 42; i++)
	{
		ft_cont2.insert(i);
	}

	ft_cont1.swap(ft_cont2);

	assert(ft_cont1.size() == 12);
	assert(*ft_cont1.begin() == 42);
	assert(ft_cont2.size() == 20);
	assert(*ft_cont2.begin() == 0);
}

void	test_set_find(size_t size, int to_add)
{
	ft::set<int> ft_cont1;	
	//inserting "size" nodes to the std container
	for (size_t i = 0; i < size; i++)
	{
		ft_cont1.insert(i);
	}
	assert(ft_cont1.size() == size);
	ft_cont1.insert(to_add);
	assert(ft_cont1.find(to_add) != ft_cont1.end());
	assert(*ft_cont1.find(to_add) == to_add);
	//ft_cont1.debug(output_int_with_4_char); //OK
}

void tests_set_find(void)
{
	test_set_find(0, 1);
	test_set_find(3, 1);
	test_set_find(3, 4);
}

void	test_set_count(void)
{
	ft::set<int, std::string> ft_cont1;	
	//inserting "size" nodes to the std container
	for (size_t i = 0; i < 42; i++)
	{
		ft_cont1.insert(i);
	}
	assert(ft_cont1.size() == 42);
	assert(ft_cont1.count(10) == 1);
	assert(ft_cont1.count(43) == 0);
	//try to insert a key that already exists.
	ft_cont1.insert(10);
	assert(ft_cont1.size() == 42);
}

void	test_set_lower_bound(void)
{	
	ft::set<int, std::string> ft_cont;	
	for (size_t i = 1; i <= 5; i++)
	{	
		ft_cont.insert(i);	
	}
	assert(*ft_cont.lower_bound(3) == 3);
	assert(ft_cont.lower_bound(0) == ft_cont.find(1));
	assert(ft_cont.lower_bound(-1) == ft_cont.find(1));
	assert(ft_cont.lower_bound(2) == ft_cont.find(2));
	assert(ft_cont.lower_bound(6) == ft_cont.end());
}

void	test_set_upper_bound(void)
{
	ft::set<int, std::string> ft_cont;	
	for (size_t i = 1; i <= 5; i++)
	{	
		ft_cont.insert(i);	
	}
	assert(ft_cont.upper_bound(-1) == ft_cont.find(1));
	assert(ft_cont.upper_bound(0) == ft_cont.find(1));
	assert(ft_cont.upper_bound(1) == ft_cont.find(2));
	assert(ft_cont.upper_bound(2) == ft_cont.find(3));
	assert(ft_cont.upper_bound(4) == ft_cont.find(5));
	assert(ft_cont.upper_bound(5) == ft_cont.end());
	assert(ft_cont.upper_bound(6) == ft_cont.end());
}

void	tests_set_tree_equal_range(void)
{
	typedef ft::set<int, std::string>::iterator it;
	ft::set<int, std::string> ft_cont;	
	for (size_t i = 1; i <= 6; i++)
	{	
		ft_cont.insert(i);	
	}

	std::pair<it, it> my_pair1 = ft_cont.equal_range(4);
	assert(*my_pair1.first == 4);
	assert(*my_pair1.second == 5);

	my_pair1 = ft_cont.equal_range(5);
	assert(*my_pair1.first == 5);
	assert(*my_pair1.second == 6);

	my_pair1 = ft_cont.equal_range(6);
	assert(*my_pair1.first == 6);
	assert(my_pair1.second == ft_cont.end());

	my_pair1 = ft_cont.equal_range(7);
	assert(my_pair1.first == ft_cont.end());
	assert(my_pair1.second == ft_cont.end());

	my_pair1 = ft_cont.equal_range(-1);
	assert(my_pair1.first == ft_cont.begin());
	assert(my_pair1.second == ft_cont.find(1));
}

void tests_set(void)
{
	tests_set_constructors();
	tests_set_insert();
	tests_set_erase();
	test_set_swap();
	tests_set_find();
	test_set_count();
	test_set_lower_bound();
	test_set_upper_bound();
	tests_set_tree_equal_range();
}
