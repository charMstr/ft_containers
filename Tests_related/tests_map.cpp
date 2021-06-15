/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_map.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/06/14 18:55:19 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/15 02:42:08 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"
#include <iterator>
#include <sstream>
#include <map>

void	test_map_default_constructor1(void)
{
	ft::map<std::string, int> ft_cont;	
	assert(ft_cont.size() == 0);
}

void	test_map_copy_constructor(void)
{
	typedef std::pair<std::string, int> t_pair;

	ft::map<std::string, int> ft_cont;	
	t_pair pair1("aaaaa", 1);
	t_pair pair2("eeeee123", 1);
	t_pair pair3("iiiiiii", 1);
	t_pair pair4("ooooo", 1);
	t_pair pair5("uuuu", 1);
	ft_cont.insert(pair1);
	ft_cont.insert(pair2);
	ft_cont.insert(pair3);
	ft_cont.insert(pair4);
	ft_cont.insert(pair5);
	assert(ft_cont.size() == 5);
	ft::map<std::string, int> ft_cont2(ft_cont);
	assert(ft_cont.size() == ft_cont2.size());
//	ft_cont.debug(output_string_with_4_char);
//	ft_cont2.debug(output_string_with_4_char);
}

void	test_map_operator_equal_constructor()
{
	typedef std::pair<std::string, int> t_pair;

	ft::map<std::string, int> ft_cont;	
	t_pair pair1("aaaaa", 1);
	t_pair pair2("eeeee123", 1);
	ft_cont.insert(pair1);
	ft_cont.insert(pair2);
	assert(ft_cont.size() == 2);

	ft::map<std::string, int> ft_cont2;	
	assert(ft_cont2.empty() == true);
	ft_cont = ft_cont2;
	assert(ft_cont.empty());
}

void	test_map_range_constructor(size_t size)
{
	typedef std::pair<int, std::string> t_pair;
	ft::map<int, std::string> ft_cont1;	
	
	for (size_t i = 0; i < size; i++)
	{	
		t_pair pair1(i, "charmstr");
		ft_cont1.insert(pair1);	
	}
	ft::map<int, std::string>::iterator ft_it = ft_cont1.begin();

	//from start to end;
	ft::map<int, std::string> ft_cont2(ft_it, ft_cont1.end());

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
	ft::map<int, std::string> ft_cont3(ft_it, ft_cont1.end());
	assert(ft_cont3.size() == ft_cont1.size() - (difference_in_size));
}

void	tests_map_constructors()
{
	test_map_default_constructor1();
	test_map_copy_constructor();
	test_map_operator_equal_constructor();
	test_map_range_constructor(0);
	test_map_range_constructor(1);
	test_map_range_constructor(2);
	test_map_range_constructor(3);
	test_map_range_constructor(10);
}

void	test_map_insert_single_element(void)
{
	typedef std::pair<int, std::string> t_pair;
	std::pair<ft::map<int, std::string>::iterator, bool> result;
	ft::map<int, std::string> ft_cont1;	

	t_pair pair1(1, "salut");
	result = ft_cont1.insert(pair1);
	assert(result.second == true);
	assert(result.first == ft_cont1.begin());

	t_pair pair2(1, "salut");
	result = ft_cont1.insert(pair2);
	assert(result.second == false);
	assert(result.first == ft_cont1.begin());

	t_pair pair3(2, "salut");
	result = ft_cont1.insert(pair3);
	assert(result.second == true);
	assert(result.first == ++ft_cont1.begin());
}

void	test_map_insert_range(void)
{
	std::map<int, std::string> std_cont;
	typedef std::pair<int, std::string> t_pair;

	//inserting three nodes to the std container
	t_pair pair1(1, "salut");
	std_cont.insert(pair1);

	t_pair pair2(2, "salut");
	std_cont.insert(pair2);

	t_pair pair3(3, "salut");
	std_cont.insert(pair3);

	ft::map<int, std::string> ft_cont2;	
	std::map<int, std::string> std_cont2;	
	ft_cont2.insert(std_cont.begin(), std_cont.end());
	std_cont2.insert(std_cont.begin(), std_cont.end());
	assert(ft_cont2.begin()->first == std_cont2.begin()->first);
	assert((++ft_cont2.begin())->first == (++std_cont2.begin())->first);
	assert(ft_cont2.size() == std_cont2.size());
	assert((--ft_cont2.end())->first == (--std_cont2.end())->first);
}


void	tests_map_insert(void)
{
	test_map_insert_single_element();
	test_map_insert_range();
}

void	test_map_erase_range1(size_t size)
{
	ft::map<int, std::string> ft_cont1;	
	typedef std::pair<int, std::string> t_pair;

	//inserting three nodes to the std container
	for (size_t i = 0; i < size; i++)
	{
		t_pair pair(i, "salut");
		ft_cont1.insert(pair);
	}
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

void	test_map_erase_range2(size_t size)
{
	ft::map<int, std::string> ft_cont1;	
	typedef std::pair<int, std::string> t_pair;

	//inserting three nodes to the std container
	for (size_t i = 0; i < size; i++)
	{
		t_pair pair(i, "salut");
		ft_cont1.insert(pair);
	}
	//erase all but last
	assert(ft_cont1.size() == size);
	//ft_cont1.debug(output_int_with_4_char);
	ft::map<int, std::string>::iterator it = ft_cont1.begin();
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

void	tests_map_erase(void)
{
	test_map_erase_range1(0);
	test_map_erase_range1(1);
	test_map_erase_range1(2);
	test_map_erase_range1(3);
	test_map_erase_range1(4);
	test_map_erase_range1(14);
	test_map_erase_range1(15);
	test_map_erase_range2(4); 
	test_map_erase_range2(5); 
	test_map_erase_range2(6); 
	test_map_erase_range2(8); 
	test_map_erase_range2(9); 
}
void	test_map_swap(void)
{	
	typedef std::pair<int, std::string> t_pair;

	ft::map<int, std::string> ft_cont1;	
	//inserting 20 nodes to the std container
	for (size_t i = 0; i < 20; i++)
	{
		t_pair pair(i, "salut");
		ft_cont1.insert(pair);
	}
	ft::map<int, std::string> ft_cont2;	
	//inserting 12 nodes to the std container
	for (size_t i = 42; i < 12 + 42; i++)
	{
		t_pair pair(i, "salut");
		ft_cont2.insert(pair);
	}
	ft_cont1.swap(ft_cont2);
	assert(ft_cont1.size() == 12);
	assert(ft_cont1.begin()->first == 42);
	assert(ft_cont2.size() == 20);
	assert(ft_cont2.begin()->first == 0);
}

void test_hook_operator(size_t size, int to_add)
{
	typedef std::pair<int, std::string> t_pair;

	ft::map<int, std::string> ft_cont1;	
	//inserting "size" nodes to the std container
	for (size_t i = 1; i <= size; i++)
	{
		t_pair pair(i, "salut");
		ft_cont1.insert(pair);
	}
	size_t current_size = ft_cont1.size();
	assert(ft_cont1.size() == size);

	ft::map<int, std::string>::mapped_type value;
	value = ft_cont1[to_add];
	if (to_add > (int)size)
	{
		assert(current_size + 1 == ft_cont1.size());
		assert(value == "");
	}
	else
	{
		assert(current_size == ft_cont1.size());
		assert(value == "salut");
	}
	//ft_cont1.debug(output_int_with_4_char); //OK
}

void tests_hook_operator(void)
{
	test_hook_operator(3, 2);
	test_hook_operator(3, 3);
	test_hook_operator(3, 4);
	test_hook_operator(4, 5);
}

void	test_map_find(size_t size, int to_add)
{
	typedef std::pair<int, std::string> t_pair;

	ft::map<int, std::string> ft_cont1;	
	//inserting "size" nodes to the std container
	for (size_t i = 0; i < size; i++)
	{
		t_pair pair(i, "salut");
		ft_cont1.insert(pair);
	}
	assert(ft_cont1.size() == size);
	ft_cont1[to_add];
	assert(ft_cont1.find(to_add) != ft_cont1.end());
	assert(ft_cont1.find(to_add)->first == to_add);
	//ft_cont1.debug(output_int_with_4_char); //OK
}

void tests_map_find(void)
{
	test_map_find(0, 1);
	test_map_find(3, 1);
	test_map_find(3, 4);
}

void	test_map_count(void)
{
	typedef std::pair<int, std::string> t_pair;

	ft::map<int, std::string> ft_cont1;	
	//inserting "size" nodes to the std container
	for (size_t i = 0; i < 42; i++)
	{
		t_pair pair(i, "salut");
		ft_cont1.insert(pair);
	}
	assert(ft_cont1.size() == 42);
	assert(ft_cont1.count(10) == 1);
	assert(ft_cont1.count(43) == 0);
	//try to insert a key that already exists.
	t_pair pair(10, "salut");
	ft_cont1.insert(pair);
	assert(ft_cont1.size() == 42);
}

void	test_map_lower_bound(void)
{	
	ft::map<int, std::string> ft_cont;	
	ft_cont[1];
	ft_cont[2];
	ft_cont[3];
	ft_cont[4];
	ft_cont[5];
	assert(ft_cont.lower_bound(3)->first == 3);
	assert(ft_cont.lower_bound(0) == ft_cont.find(1));
	assert(ft_cont.lower_bound(-1) == ft_cont.find(1));
	assert(ft_cont.lower_bound(2) == ft_cont.find(2));
	assert(ft_cont.lower_bound(6) == ft_cont.end());
}

void	test_map_upper_bound(void)
{
	ft::map<int, std::string> ft_cont;	
	ft_cont[1];
	ft_cont[2];
	ft_cont[3];
	ft_cont[4];
	ft_cont[5];
	assert(ft_cont.upper_bound(-1) == ft_cont.find(1));
	assert(ft_cont.upper_bound(0) == ft_cont.find(1));
	assert(ft_cont.upper_bound(1) == ft_cont.find(2));
	assert(ft_cont.upper_bound(2) == ft_cont.find(3));
	assert(ft_cont.upper_bound(4) == ft_cont.find(5));
	assert(ft_cont.upper_bound(5) == ft_cont.end());
	assert(ft_cont.upper_bound(6) == ft_cont.end());
}

void	tests_map_tree_equal_range(void)
{
	typedef ft::map<int, std::string>::iterator it;
	ft::map<int, std::string> ft_cont;	
	ft_cont[1];
	ft_cont[2];
	ft_cont[3];
	ft_cont[4];
	ft_cont[5];
	ft_cont[6];

	std::pair<it, it> my_pair1 = ft_cont.equal_range(4);
	assert(my_pair1.first->first == 4);
	assert(my_pair1.second->first == 5);

	my_pair1 = ft_cont.equal_range(5);
	assert(my_pair1.first->first == 5);
	assert(my_pair1.second->first == 6);

	my_pair1 = ft_cont.equal_range(6);
	assert(my_pair1.first->first == 6);
	assert(my_pair1.second == ft_cont.end());

	my_pair1 = ft_cont.equal_range(7);
	assert(my_pair1.first == ft_cont.end());
	assert(my_pair1.second == ft_cont.end());

	my_pair1 = ft_cont.equal_range(-1);
	assert(my_pair1.first == ft_cont.begin());
	assert(my_pair1.second == ft_cont.find(1));
}

void tests_map(void)
{
	tests_map_constructors();
	tests_map_insert();
	tests_map_erase();
	test_map_swap();
	tests_hook_operator();
	tests_map_find();
	test_map_count();
	test_map_lower_bound();
	test_map_upper_bound();
	tests_map_tree_equal_range();
}
