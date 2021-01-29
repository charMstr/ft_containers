/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_vector.cpp                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 21:24:00 by charmstr          #+#    #+#             */
/*   Updated: 2021/01/29 10:52:54 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"
#include <iterator>

template <typename T>
void compare_std_ft_cont(ft::vector<T> &ft_cont, std::vector<T> &std_cont)
{
	assert(ft_cont.size() == std_cont.size());	
	assert(ft_cont.max_size() == std_cont.max_size());	
	assert(ft_cont.empty() == std_cont.empty());	
	assert(ft_cont.capacity() == std_cont.capacity());

	typename std::vector<T>::iterator std_it = std_cont.begin();
	typename ft::vector<T>::iterator ft_it = ft_cont.begin();
	for(; ft_it != ft_cont.end() && std_it != std_cont.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
}

void test_constructor_default(void)
{
	ft::vector<int>::iterator it;
	std::vector<int> std_cont;
	ft::vector<int> ft_cont;

	compare_std_ft_cont(ft_cont, std_cont);
	for (it = ft_cont.begin(); it != ft_cont.end(); it++)
		assert(*it == 8);
}

void test_constructor_range(void)
{		
	ft::vector<int>::iterator it;
	std::vector<int> std_cont(4, 8);
	ft::vector<int> ft_cont(4, 8);

	compare_std_ft_cont(ft_cont, std_cont);
	for (it = ft_cont.begin(); it != ft_cont.end(); it++)
		assert(*it == 8);

	////////////////////
	/*
	std::vector<int> std_container(4, 8); 
	std::vector<int>::iterator std_it1 = std_container.begin();
	std::vector<int>::iterator std_it2 = ++std_container.begin();
	//note: std_it2 is bigger than std_it
	std::vector<int> container1(std_it2, std_it1); 
	std::cout << container1.begin().base() << std::endl;
	std::cout << container1.size() << std::endl;

	ft::vector<int> ft_container(4, 8); 
	ft::vector<int>::iterator ft_it1 = ft_container.begin();
	ft::vector<int>::iterator ft_it2 = ++ft_container.begin();
	//note: ft_it2 is bigger than ft_it
	ft::vector<int> container2(ft_it2, ft_it1); 
	std::cout << container2.begin().base() << std::endl;
	*/
}

void test_destructor_and_clear(void)
{	
	std::vector<int> std_cont(4, 8);
	ft::vector<int> ft_cont(4, 8);

	std_cont.clear();
	ft_cont.clear();
	compare_std_ft_cont(ft_cont, std_cont);
}

void	test_begin_vs_const_begin(void)
{
	ft::vector<int> ft_cont(4, 8);
	std::vector<int> std_cont(4, 8);

	ft::vector<int>::iterator ft_it1 = ft_cont.begin();
	std::vector<int>::iterator std_it1 = std_cont.begin();

	(void)std_it1;

	//conversion from normal iterator to const_iterator OK
	ft::vector<int>::const_iterator ft_const_it1 = ft_cont.begin();
	std::vector<int>::const_iterator std_const_it1 = std_cont.begin();
	//(void)ft_const_it1;
	(void)std_const_it1;
	
	ft::vector<const int> ft_const_cont(4, 8);
	std::vector<const int> std_const_cont(4, 8);
	
	//conversion from container containing const values to normal iterator:
	//not possible: OK
//	ft::vector<int>::iterator ft_it2 = ft_const_cont.begin();
//	std::vector<int>::iterator std_it2 = std_const_cont.begin();

	//conversion from container containing const values to const _iterator OK
	ft::vector<int>::const_iterator ft_const_it2 = ft_const_cont.begin();
	std::vector<int>::const_iterator std_const_it2 = std_const_cont.begin();

	(void)ft_const_it2;
	(void)std_const_it2;
}

void _test_reserve(size_t initial_size, size_t new_size)
{
	ft::vector<int> ft_cont(initial_size, 42);
	std::vector<int> std_cont(initial_size, 42);

	assert(ft_cont.size() == std_cont.size());

	ft_cont.reserve(new_size);
	std_cont.reserve(new_size);

	assert(ft_cont.size() == std_cont.size());
	assert(ft_cont.capacity() == std_cont.capacity());	
}

void test_resize(size_t initial_size, size_t new_size, int new_value)
{	
	ft::vector<int> ft_cont(initial_size, 42);
	std::vector<int> std_cont(initial_size, 42);	

	assert(ft_cont.size() == std_cont.size());
	assert(ft_cont.capacity() == std_cont.capacity());

	ft_cont.resize(new_size, new_value);
	std_cont.resize(new_size, new_value);

	assert(ft_cont.size() == std_cont.size());
	assert(ft_cont.capacity() == std_cont.capacity());	

	std::vector<int>::iterator std_it = std_cont.begin();
	ft::vector<int>::iterator ft_it = ft_cont.begin();
	while((ft_it != ft_cont.end()) && (std_it != std_cont.end()))
	{
		assert(*ft_it == *std_it);	
		ft_it++;
		std_it++;
	}
	assert(ft_it == ft_cont.end() && std_it == std_cont.end());
}

void	test_reserve_and_resize(void)
{
	_test_reserve(2,1);
	_test_reserve(2,2);
	_test_reserve(2,3);
	test_resize(3, 1, 8);
	test_resize(3, 3, 8);
	test_resize(3, 5, 8);
	test_resize(3, 6, 8);
	test_resize(3, 7, 8);
	test_resize(3, 8, 8);
}

void	_test_equal_assignement(int size_1, int size_2)
{		
	std::vector<int> cont1(size_1,42);
	std::vector<int> cont2(size_2,8);
	ft::vector<int> ft_cont1(size_1,42);
	ft::vector<int> ft_cont2(size_2,8);

	cont2 = cont1;
	ft_cont2 = ft_cont1;
	assert(cont2.size() == ft_cont2.size());
	assert(cont2.capacity() == ft_cont2.capacity());
	compare_std_ft_cont(ft_cont2, cont2);
}

void test_equal_assignement(void)
{
	_test_equal_assignement(2, 5);	
	_test_equal_assignement(6, 2);	
	_test_equal_assignement(3, 3);	
}


void	test_front_and_back(void)
{
	std::vector<int> cont1;	
	ft::vector<int> ft_cont1;	

	int &a = cont1.front();
	//a = 12; //provoques a sefault on the std.
	//a = cont1.back(); //segfault
	(void)a;

	int &b = ft_cont1.front();
	//b = 12; //provoques a sefault as well: OK
	//b = cont1.back(); //segfault
	(void)b;

	std::vector<int> cont2(2,2);	
	ft::vector<int> ft_cont2(2,2);	

	int &c = cont2.front();
	int &d = ft_cont2.front();
	c = 42;
	d = 42;
	assert(*cont2.begin().base() == *ft_cont2.begin().base());
	assert(*cont2.begin().base() == 42);

	int &e = cont2.back();
	int &f = ft_cont2.back();
	e = 43;
	f = 43;
	assert(cont2.back() == ft_cont2.back());
	assert(cont2.back() == 43);
}

void	test_brackets(void)
{
	//std::vector<int> cont1;
	//int a;
	//a = cont1[0]; //segfault.

	std::vector<int> cont1(1,1);
	ft::vector<int> ft_cont1(1,1);	
	int a = cont1[0];
	int b = ft_cont1[0]; //OK
	assert(a == b);
	//a = cont1[1000000]; //segfault, not protected.
}

void	test_at_symbol(void)
{
	std::vector<int> cont1;
	ft::vector<int> ft_cont1;
	int a;
	try { a = cont1.at(0); }
	catch (std::exception &e)
	{ std::cout << e.what() << std::endl; }
	try { a = ft_cont1.at(0); }
	catch (std::exception &e)
	{ std::cout << e.what() << std::endl; }

	std::vector<int> cont2(2,2);
	ft::vector<int> ft_cont2(2,2);
	try { a = cont2.at(2); }
	catch (std::exception &e)
	{ std::cout << e.what() << std::endl; }
	try { a = ft_cont2.at(2); }
	catch (std::exception &e)
	{ std::cout << e.what() << std::endl; }
}

void display_std_cont(std::vector<int> std_cont)
{
	std::cout << "std_cont: " << std::endl;
	for (std::vector<int>::iterator it = std_cont.begin(); it != std_cont.end(); it++)
	{
		std::cout << *it << " ";		
	}
	std::cout << std::endl;
}

void display_ft_cont(ft::vector<int> ft_cont)
{
	std::cout << "ft_cont:  " << std::endl;
	ft::vector<int>::iterator it;
	for  (it = ft_cont.begin(); it != ft_cont.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}


void	test_push_and_pop_back(void)
{
	ft::vector<int> ft_cont1;
	std::vector<int> std_cont1;
	for (int i = 0; i < 10; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
	}
	compare_std_ft_cont(ft_cont1, std_cont1);	
	for (int i = 0; i < 10; i++)
	{
		std_cont1.pop_back();
		ft_cont1.pop_back();
		compare_std_ft_cont(ft_cont1, std_cont1);
	}
	assert(std_cont1.empty());
	assert(ft_cont1.empty());
}

void test_insert_one(void)
{
	std::vector<int> std_cont;
	ft::vector<int> ft_cont;

	for (int i = 0; i < 4; i++)
	{
		std_cont.insert(std_cont.begin(), 42);
		ft_cont.insert(ft_cont.begin(), 42);
		compare_std_ft_cont(ft_cont, std_cont);
	}

	std::vector<int>::iterator std_it = std_cont.begin();
	ft::vector<int>::iterator ft_it = ft_cont.begin();

	std_it++;
	ft_it++;

	std_it = std_cont.insert(std_it, 8);
	std_it = std_cont.insert(std_it, 12);
	ft_it = ft_cont.insert(ft_it, 8);
	ft_it = ft_cont.insert(ft_it, 12);
		
	//display_ft_cont(ft_cont);
	//std::cout << std::endl;
	//display_std_cont(std_cont);
	compare_std_ft_cont(ft_cont, std_cont);
}

void	test_insert_fill(int reserve_size, int actual_size, \
		int offset_position, int insert_size)
{
	ft::vector<int> ft_cont;
	std::vector<int> std_cont;
	ft_cont.reserve(reserve_size);  //capacity = reserve_size
	std_cont.reserve(reserve_size);

	for (int i = 0; i < actual_size; i++) //first actual_size objects created
	{	
		std_cont.push_back(i);
		ft_cont.push_back(i);
	}

	ft_cont.insert(ft_cont.begin() + offset_position, insert_size, 8);
	std_cont.insert(std_cont.begin() + offset_position, insert_size, 8);
	//display_ft_cont(ft_cont);
	//std::cout << std::endl;
	//display_std_cont(std_cont);
	compare_std_ft_cont(ft_cont, std_cont); 	//OK
}

void	test_insert_range(int reserve_size, int actual_size, int position,
		int first, int last)
{
	std::vector<int> std_cont;
	std::vector<int> ref;
	ft::vector< int > ft_cont;

	ft_cont.reserve(reserve_size);  //capacity = reserve_size
	std_cont.reserve(reserve_size);
	ref.reserve(reserve_size);

	for (int i = 0; i < actual_size; i++) //first actual_size objects created
	{	
		std_cont.push_back(i);
		ref.push_back(i);
		ft_cont.push_back(i);
	}

	//display_std_cont(std_cont);
	std_cont.insert(std_cont.begin() + position, ref.begin() + first, ref.begin() + last);
	//display_std_cont(std_cont);
	ft_cont.insert(ft_cont.begin() + position, ref.begin() + first, ref.begin() + last);
	assert(ft_cont.begin().base() < ft_cont.end().base());
	//std::cout  << std::endl;
	//display_ft_cont(ft_cont);
	compare_std_ft_cont(ft_cont, std_cont);
}

void	test_insert(void)
{
	//test when inserting only one elem at given position
	test_insert_one();	
	//inserting at the begining of an empty container.
	test_insert_fill(1, 0, 0, 1);
	//inserting in an empty container that has not enough space.
	test_insert_fill(1, 0, 0, 2);
	//inserting in a non empty container that has not enough space.
	test_insert_fill(1, 1, 0, 2);

	//inserting in container that has enough space when distance from postion
	//to n is more than 
	test_insert_fill(12, 6, 4 , 4);
	test_insert_fill(12, 6, 4 , 3);
	test_insert_fill(12, 6, 4 , 2);
	test_insert_fill(12, 6, 4 , 1);
	std::cout << std::endl;

	//range insert within existing capacity
	test_insert_range(12, 6, 4 , 1, 2);
	test_insert_range(12, 6, 4 , 1, 3);
	test_insert_range(12, 6, 4 , 1, 4);
	test_insert_range(12, 6, 4 , 1, 4);

	//range insert out of existing capacity
	test_insert_range(12, 8, 4 , 1, 6);
	test_insert_range(12, 8, 4 , 0, 8);
	std::cout << std::endl;
}

void	test_erase_one(size_t size, size_t  offset)
{
	std::vector<int> std_cont;
	ft::vector<int> ft_cont;

//	std_cont.erase(std_cont.begin()); //segfault on empty vector //OK
	//also std_cont segfault when given a position that is end() or after

	for (size_t i = 0; i < size; i++)
	{
		std_cont.push_back( i);
		ft_cont.push_back( i);
		compare_std_ft_cont(ft_cont, std_cont);
	}

	size_t dist_std;
	size_t dist_ft;
	ft::vector<int>::iterator ft_it;
	std::vector<int>::iterator std_it;

	ft_it = ft_cont.erase(ft_cont.begin() + offset);
	std_it = std_cont.erase(std_cont.begin() + offset);

	ft::distance(ft_cont.begin(), ft_it, dist_ft);
	ft::distance(std_cont.begin(), std_it, dist_std);

	//display_ft_cont(ft_cont);
	//display_std_cont(std_cont);
	//std::cout << std::endl;
	assert(dist_std == dist_ft);
	compare_std_ft_cont(ft_cont, std_cont);
}

void	test_erase_range(size_t size, size_t first, size_t last)
{
	std::vector<int> std_cont;
	ft::vector<int> ft_cont;

	for (size_t i = 0; i < size; i++)
	{
		std_cont.push_back( i);
		ft_cont.push_back( i);
		compare_std_ft_cont(ft_cont, std_cont);
	}

	size_t dist_std;
	size_t dist_ft;
	ft::vector<int>::iterator ft_it;
	std::vector<int>::iterator std_it;

	ft_it = ft_cont.erase(ft_cont.begin() + first, ft_cont.begin() + last);
	std_it = std_cont.erase(std_cont.begin() + first, std_cont.begin() + last);

	ft::distance(ft_cont.begin(), ft_it, dist_ft);
	ft::distance(std_cont.begin(), std_it, dist_std);

	//std::cout << "res ft: " << dist_ft << std::endl;
	//std::cout << "res std: " << dist_std << std::endl;
	//display_ft_cont(ft_cont);
	//display_std_cont(std_cont);
	//std::cout << std::endl;

	assert(dist_std == dist_ft);
	compare_std_ft_cont(ft_cont, std_cont);
}

void	test_erase(void)
{
	//erase the first
	test_erase_one(4, 0);
	test_erase_one(4, 1);
	test_erase_one(4, 2);
	//erase the last
	test_erase_one(4, 3);
	//test_erase_one(4, 4); //segfault on std

	test_erase_range(10, 1, 4);
	test_erase_range(10, 0, 0);
	test_erase_range(10, 0, 1);
	test_erase_range(10, 3, 9);
}

void	test_swap(void)
{
	ft::vector< int > ft_cont1(3, 100);
	ft::vector< int > ft_cont2(5, 42);
	/*
	std::cout << "before swap:"<< std::endl;
	display_ft_cont(ft_cont1);
	display_ft_cont(ft_cont2);
	ft_cont1.swap(ft_cont2);
	display_ft_cont(ft_cont1);
	display_ft_cont(ft_cont2);
	*/
}

void	test_equal_operator(void)
{
	ft::vector<int> ft_cont1;
	ft::vector<int> ft_cont2;
	for (int i = 0; i < 10; i++)
	{
		ft_cont2.push_back(i);
		ft_cont1.push_back(i);
	}
	assert(ft_cont1 == ft_cont2);
	ft_cont1.pop_back();
	ft_cont1.push_back(42);
	assert(ft_cont1 != ft_cont2);
}

void	test_inferior_operator(void)
{
	std::vector<int> std_cont1;	
	std::vector<int> std_cont2;	
	ft::vector<int> ft_cont1;	
	ft::vector<int> ft_cont2;	
	for (int i = 0; i < 10; i++)
	{
		std_cont1.push_back(i);
		std_cont2.push_back(i);
		ft_cont1.push_back(i);
		ft_cont2.push_back(i);
	}
	//should return 0 when the size is the same and they contain the same
	assert(std_cont1 < std_cont2 ==  ft_cont1 < ft_cont2);

	std_cont2.push_back(42);
	ft_cont2.push_back(42);
	//should return true when the size of cont2 is bigger
	assert(std_cont1 < std_cont2 ==  ft_cont1 < ft_cont2);

	//sould return false when size of cont1 is bigger
	std_cont1.push_back(42);
	ft_cont1.push_back(42);
	std_cont1.push_back(42);
	ft_cont1.push_back(42);
	assert(std_cont1 < std_cont2 ==  ft_cont1 < ft_cont2);

	//should return true when the in cont1 we have someting smaller than cont2.
	std_cont2.push_back(43);
	ft_cont2.push_back(43);
	assert(std_cont1 < std_cont2 ==  ft_cont1 < ft_cont2);
	/*
	if (std_cont1 < std_cont2)
		std::cout << "std_con1 is inferior"<< std::endl;
	else
		std::cout << "std_cont1 is NOT inferior"<< std::endl;
		*/
}

void tests_vector(void)
{
	test_constructor_default();
 	test_constructor_range();
	test_destructor_and_clear();
	test_begin_vs_const_begin();
	test_reserve_and_resize();
	test_equal_assignement();
	test_front_and_back();
	test_brackets();
	test_at_symbol();
	test_push_and_pop_back();
	test_insert();
	test_erase();
	test_swap();
	test_equal_operator();
	test_inferior_operator();
}
