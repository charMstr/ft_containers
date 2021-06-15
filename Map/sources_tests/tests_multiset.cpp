/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_multiset.cpp                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/15 03:12:36 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/15 03:16:14 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "functions_tests.hpp"
#include <set>

void	test_multiset_default_constructor1(void)
{
	ft::multiset<std::string> ft_cont;	
	assert(ft_cont.size() == 0);
}

void	test_multiset_copy_constructor(void)
{
	ft::multiset<std::string> ft_cont;	
	ft_cont.insert("aaaaa");
	ft_cont.insert("eeeee123");
	ft_cont.insert("iiiiiii");
	ft_cont.insert("ooooo");
	ft_cont.insert("uuuu");
	assert(ft_cont.size() == 5);
	ft::multiset<std::string> ft_cont2(ft_cont);
	assert(ft_cont.size() == ft_cont2.size());
//	ft_cont.debug(output_string_with_4_char);
//	ft_cont2.debug(output_string_with_4_char);
}

void	test_multiset_operator_equal_constructor()
{
	ft::multiset<std::string> ft_cont;	
	ft_cont.insert("aaaaa");
	ft_cont.insert("eeeee123");
	assert(ft_cont.size() == 2);

	ft::multiset<std::string> ft_cont2;	
	assert(ft_cont2.empty() == true);
	ft_cont = ft_cont2;
	assert(ft_cont.empty());
}

void	test_multiset_range_constructor(size_t size)
{
	ft::multiset<int> ft_cont1;	
	
	for (size_t i = 0; i < size; i++)
		ft_cont1.insert(i);	

	ft::multiset<int>::iterator ft_it = ft_cont1.begin();

	//from start to end;
	ft::multiset<int> ft_cont2(ft_it, ft_cont1.end());

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
	ft::multiset<int> ft_cont3(ft_it, ft_cont1.end());
	assert(ft_cont3.size() == ft_cont1.size() - (difference_in_size));
}

void	tests_multiset_constructors()
{
	test_multiset_default_constructor1();
	test_multiset_copy_constructor();
	test_multiset_operator_equal_constructor();
	test_multiset_range_constructor(0);
	test_multiset_range_constructor(1);
	test_multiset_range_constructor(2);
	test_multiset_range_constructor(3);
	test_multiset_range_constructor(10);
}

void	test_multiset_insert_single_element(void)
{
	std::pair<ft::multiset<int>::iterator, bool> result;
	ft::multiset<int> ft_cont1;	

	result = ft_cont1.insert(1);
	assert(result.second == true);
	assert(result.first == ft_cont1.begin());

	result = ft_cont1.insert(1);
	assert(result.second == true);
	assert(result.first == ft_cont1.begin());

	result = ft_cont1.insert(2);
	assert(result.second == true);
	assert(result.first == ++ft_cont1.begin());
	assert(ft_cont1.size() == 3);
}

void	test_multiset_insert_range(void)
{
	std::multiset<int> std_cont;

	//inserting three nodes to the std container
	std_cont.insert(1);

	std_cont.insert(2);

	std_cont.insert(3);

	ft::multiset<int> ft_cont2;	
	std::multiset<int> std_cont2;	
	ft_cont2.insert(std_cont.begin(), std_cont.end());
	std_cont2.insert(std_cont.begin(), std_cont.end());
	assert(*ft_cont2.begin() == *std_cont2.begin());
	assert(*(++ft_cont2.begin()) == *(++std_cont2.begin()));
	assert(ft_cont2.size() == std_cont2.size());
	assert(*(--ft_cont2.end()) == *(--std_cont2.end()));
}


void	tests_multiset_insert(void)
{
	test_multiset_insert_single_element();
	test_multiset_insert_range();
}

void	test_multiset_erase_range1(size_t size)
{
	ft::multiset<int, std::string> ft_cont1;	

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

void	test_multiset_erase_range2(size_t size)
{
	ft::multiset<int, std::string> ft_cont1;	

	//inserting three nodes to the std container
	for (size_t i = 0; i < size; i++)
		ft_cont1.insert(i);

	//erase all but last
	assert(ft_cont1.size() == size);
	//ft_cont1.debug(output_int_with_4_char);
	ft::multiset<int, std::string>::iterator it = ft_cont1.begin();
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

void	tests_multiset_erase(void)
{
	test_multiset_erase_range1(0);
	test_multiset_erase_range1(1);
	test_multiset_erase_range1(2);
	test_multiset_erase_range1(3);
	test_multiset_erase_range1(4);
	test_multiset_erase_range1(14);
	test_multiset_erase_range1(15);
	test_multiset_erase_range2(4); 
	test_multiset_erase_range2(5); 
	test_multiset_erase_range2(6); 
	test_multiset_erase_range2(8); 
	test_multiset_erase_range2(9); 
}
void	test_multiset_swap(void)
{	

	ft::multiset<int, std::string> ft_cont1;	
	//inserting 20 nodes to the std container
	for (size_t i = 0; i < 20; i++)
		ft_cont1.insert(i);

	ft::multiset<int, std::string> ft_cont2;	
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

void	test_multiset_find(size_t size, int to_add)
{
	ft::multiset<int> ft_cont1;	
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

void tests_multiset_find(void)
{
	test_multiset_find(0, 1);
	test_multiset_find(3, 1);
	test_multiset_find(3, 4);
}

void	test_multiset_count(void)
{
	ft::multiset<int, std::string> ft_cont1;	
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

void	test_multiset_lower_bound(void)
{	
	ft::multiset<int, std::string> ft_cont;	
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

void	test_multiset_upper_bound(void)
{
	ft::multiset<int, std::string> ft_cont;	
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

void	tests_multiset_tree_equal_range(void)
{
	typedef ft::multiset<int, std::string>::iterator it;
	ft::multiset<int, std::string> ft_cont;	
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

void tests_multiset(void)
{
	tests_multiset_constructors();
	tests_multiset_insert();
	tests_multiset_erase();
	test_multiset_swap();
	tests_multiset_find();
	test_multiset_count();
	test_multiset_lower_bound();
	test_multiset_upper_bound();
	tests_multiset_tree_equal_range();
}
