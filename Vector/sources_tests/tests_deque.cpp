/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_deque.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/31 06:35:00 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/05 23:29:51 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"
#include <iterator>

template <typename T>
void compare_std_ft_cont(std::deque<T> &std_cont, ft::deque<T> &ft_cont)
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

template< typename T >
void	std_display_specs(std::deque<T> &std_cont)
{
	std::cout << std::endl;
	std::cout << "STD_cont: " << std::endl;
	std::cout << " size: " << std_cont.size() << std::endl;
	std::cout << " maz_size: " << std_cont.max_size() << std::endl;
	std::cout << " is_empty: " << std_cont.empty() << std::endl;
}

template< typename T >
void	ft_display_specs(ft::deque<T> &ft_cont)
{
	std::cout << std::endl;
	std::cout << "FT_cont: " << std::endl;
	std::cout << " size: " << ft_cont.size() << std::endl;
	std::cout << " maz_size: " << ft_cont.max_size() << std::endl;
	std::cout << " is_empty: " << ft_cont.empty() << std::endl;
}

void	ft_display_content(ft::deque<int> ft_cont)
{
	std::cout << std::endl << "FT CONTENT:" << std::endl;
	for (ft::deque<int>::iterator it = ft_cont.begin(); it != ft_cont.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	std_display_content(std::deque<int> std_cont)
{
	std::cout << std::endl << "STD CONTENT:" << std::endl;
	for (std::deque<int>::iterator it = std_cont.begin(); it != std_cont.end(); it++)
	{
		std::cout << *it << " ";
	}
	std::cout << std::endl;
}

void	constructor_fill(int size, int value)
{
	std::deque<int> std_cont(size, value);
	ft::deque<int> ft_cont(size, value);

	ft::deque<int>::iterator ft_it = ft_cont.begin();
	std::deque<int>::iterator std_it = std_cont.begin();

	for (; ft_it != ft_cont.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
	assert(std_cont.size() == ft_cont.size());
	ft_cont.clear();
}

void	push_back(int size)
{
	std::deque<int> std_cont;
	ft::deque<int> ft_cont;

	ft::deque<int>::iterator ft_it;
	std::deque<int>::iterator std_it;

	for (int i = 0; i < size; i++)
	{
		std_cont.push_back(i);	
		ft_cont.push_back(i);
		assert(std_cont.size() == ft_cont.size());
	}

	ft_it = ft_cont.begin();
	std_it = std_cont.begin();
	for (; ft_it != ft_cont.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
	assert(std_cont.size() == ft_cont.size());
}


void	push_front(int size)
{
	std::deque<int> std_cont;
	ft::deque<int> ft_cont;

	ft::deque<int>::iterator ft_it;
	std::deque<int>::iterator std_it;

	for (int i = 0; i < size; i++)
	{
		std_cont.push_front(i);	
		ft_cont.push_front(i);
		assert(std_cont.size() == ft_cont.size());
	}

	ft_it = ft_cont.begin();
	std_it = std_cont.begin();
	for (; ft_it != ft_cont.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
	assert(std_cont.size() == ft_cont.size());
}


void push(void)
{	
	push_back(0);
	push_back(1);
	push_back(4);
	push_back(5);
	push_back(8);
	push_back(17);
	push_front(0);
	push_front(1);
	push_front(4);
	push_front(5);
	push_front(8);
	push_front(17);
}

void pop_front(size_t size)
{	
	std::deque<int> std_cont;
	ft::deque<int> ft_cont;

	for (size_t i = 0; i < size; i++)
	{
		std_cont.push_front(i);	
		ft_cont.push_front(i);
	}
	assert(std_cont.size() == ft_cont.size());
	for (size_t i = 0; i < size ; i++)
	{
		std_cont.pop_front();	
		ft_cont.pop_front();
		assert(std_cont.empty() == ft_cont.empty());
		if (!std_cont.empty())
		{
			assert(std_cont.size() == ft_cont.size());
			assert(*std_cont.begin() == *ft_cont.begin());
		}
	}
}

void pop_back(size_t size)
{	
	std::deque<int> std_cont;
	ft::deque<int> ft_cont;

	for (size_t i = 0; i < size; i++)
	{
		std_cont.push_back(i);	
		ft_cont.push_back(i);
	}
	assert(std_cont.size() == ft_cont.size());
	for (size_t i = 0; i < size ; i++)
	{
		std_cont.pop_back();	
		ft_cont.pop_back();
		assert(std_cont.empty() == ft_cont.empty());
		assert(std_cont.size() == ft_cont.size());
		if (!std_cont.empty())
		{
			assert(*std_cont.begin() == *ft_cont.begin());
		}
	}
	ft_cont.clear();
}

void pop(void)
{	
	pop_front(3);
	pop_front(4);
	pop_front(13);
	pop_front(17);
	pop_back(3);
	pop_back(4);
	pop_back(13);
	pop_back(17);
}

void	copy_assignement(void)
{
	ft::deque<int> ft_cont;

	for (size_t i = 0; i < 15; i++)
		ft_cont.push_back(i);

	ft::deque<int> ft_cont2(5, 5);;
	ft_cont2 = ft_cont;
	ft_cont = ft::deque<int>();
}

void	clear(void)
{
	ft::deque<int> ft_cont(0, 12);
	ft_cont.clear();
	ft::deque<int> ft_cont1(3, 12);
	ft_cont1.clear();
	ft::deque<int> ft_cont2(4, 12);
	ft_cont2.clear();
	ft::deque<int> ft_cont3(8, 12);
	ft_cont3.clear();
	ft::deque<int> ft_cont4(17, 12);
	ft_cont4.clear();
	ft_cont4.push_back(4);
}

void test_mixed_push(size_t size)
{
	std::deque<int> std_cont;
	ft::deque<int> ft_cont;

	for (size_t i = 0; i < size; i++)
	{
		if (i % 2)
		{
			std_cont.push_back(i);	
			ft_cont.push_back(i);
		}
		else
		{
			std_cont.push_front(i);	
			ft_cont.push_front(i);
		}
	}
	for (size_t i = 0; i < size ; i++)
	{
		assert(std_cont.empty() == ft_cont.empty());
		assert(std_cont.size() == ft_cont.size());
		if (!std_cont.empty())
		{
			assert(*(std_cont.begin() + i) == *(ft_cont.begin() + i));
		}
	}
}

void constructor_range(void)
{		
	std::deque<int> std_cont1;
	ft::deque<int> ft_cont1;

	for (size_t i = 0; i < 16; i++)
	{
		std_cont1.push_back(i);	
		ft_cont1.push_back(i);
	}

	//full range
	ft::deque<int> ft_cont2(ft_cont1.begin(), ft_cont1.end());
	std::deque<int> std_cont2(std_cont1.begin(), std_cont1.end());
	for (size_t i = 0; i < 16; i++)
	{
		assert(std_cont2.empty() == ft_cont2.empty());
		assert(std_cont2.size() == ft_cont2.size());
		if (!std_cont2.empty())
		{
			assert(*(std_cont2.begin() + i) == *(ft_cont2.begin() + i));
		}
	}

	//subrange
	ft::deque<int> ft_cont3(ft_cont1.begin() + 5, ft_cont1.end() -1);
	std::deque<int> std_cont3(std_cont1.begin() + 5, std_cont1.end() -1);
	for (size_t i = 0; i < 16 ; i++)
	{
		assert(std_cont3.empty() == ft_cont3.empty());
		assert(std_cont3.size() == ft_cont3.size());
		if (std_cont3.begin() + i == std_cont3.end())
			break;
		if (!std_cont3.empty())
		{
			assert(*(std_cont3.begin() + i) == *(ft_cont3.begin() + i));
		}
	}
}

void test_resize(size_t size_init, size_t new_size)
{
	std::deque<int> std_cont1;
	ft::deque<int> ft_cont1;

	for (size_t i = 0; i < size_init; i++)
	{
		std_cont1.push_back(i);	
		ft_cont1.push_back(i);
	}
	ft_cont1.resize(new_size, 42);
	std_cont1.resize(new_size, 42);

	assert(std_cont1.empty() == ft_cont1.empty());
	assert(std_cont1.size() == ft_cont1.size());
	ft::deque<int>::iterator ft_it = ft_cont1.begin();
	std::deque<int>::iterator std_it = std_cont1.begin();
	for (; ft_it != ft_cont1.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
}

void test_resize()
{
	test_resize(0, 12);	
	//upsize
	test_resize(3, 12);	
	//downsize
	test_resize(11, 4);	 //tester ce cas batard
	test_resize(12, 0);	 //tester ce cas batard
	test_resize(25, 6);	 //tester ce cas batard
}

void	deque_test_assign1(size_t initial_size, size_t new_size)
{
	std::deque<int> std_cont1;
	ft::deque<int> ft_cont1;

	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push_back(i);	
		ft_cont1.push_back(i);
	}
	ft_cont1.assign(new_size, 42);
	std_cont1.assign(new_size, 42);

	assert(std_cont1.empty() == ft_cont1.empty());
	assert(std_cont1.size() == ft_cont1.size());
	ft::deque<int>::iterator ft_it = ft_cont1.begin();
	std::deque<int>::iterator std_it = std_cont1.begin();
	for (; ft_it != ft_cont1.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
}

void	deque_test_assign2(size_t initial_size, size_t offset1, size_t
		offset2)
{
	std::deque<int> std_cont1;
	ft::deque<int> ft_cont1;

	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push_back(i);	
		ft_cont1.push_back(i);
	}

	std::deque<int> std_cont2;
	ft::deque<int> ft_cont2;
	
	std_cont2.assign(std_cont1.begin()+ offset1, std_cont1.begin() + offset2);
	ft_cont2.assign(ft_cont1.begin() + offset1, ft_cont1.begin() + offset2);

	assert(std_cont2.empty() == ft_cont2.empty());
	assert(std_cont2.size() == ft_cont2.size());
	ft::deque<int>::iterator ft_it = ft_cont2.begin();
	std::deque<int>::iterator std_it = std_cont2.begin();
	for (; ft_it != ft_cont2.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
}

void	deque_test_assign(void)
{
	//FILL
	//upsize
	deque_test_assign1(0, 1);	
	deque_test_assign1(2, 3);	
	deque_test_assign1(2, 6);	
	deque_test_assign1(5, 16);	
	//downsize
	deque_test_assign1(3, 2);	
	deque_test_assign1(1, 0);	
	deque_test_assign1(6, 2);	
	deque_test_assign1(16, 5);	

	//RANGE
	deque_test_assign2(0, 0, 0);	
	deque_test_assign2(15, 0, 0);	
	deque_test_assign2(15, 0, 1);	
	deque_test_assign2(15, 2, 4);	
	deque_test_assign2(15, 5, 9);	
	deque_test_assign2(15, 5, 14);	
}

void deque_erase_range(size_t initial_size, size_t start, size_t end)
{
	std::deque<int> std_cont1;
	ft::deque<int> ft_cont1;

	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push_back(i);	
		ft_cont1.push_back(i);
	}

	end = std::min(initial_size, end);
	start = std::min(initial_size, start);

	ft::deque<int>::iterator ft_it;
	std::deque<int>::iterator std_it;
	ft_it = ft_cont1.erase(ft_cont1.begin() + start, ft_cont1.begin() + end);
	std_it = std_cont1.erase(std_cont1.begin() + start, std_cont1.begin() + end);

	ft_it = ft_cont1.begin();
	std_it = std_cont1.begin();
	assert(std_cont1.empty() == ft_cont1.empty());
	assert(std_cont1.size() == ft_cont1.size());
	if (!std_cont1.empty())
		assert(*ft_it == *std_it);
	for (; ft_it != ft_cont1.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
}

void	deque_erase_range(void)
{
	deque_erase_range(0, 0, 4);
	deque_erase_range(0, 1, 4);
	deque_erase_range(10, 1, 4);
	deque_erase_range(15, 13, 14);
	deque_erase_range(15, 12, 14);
	deque_erase_range(15, 11, 14);
	deque_erase_range(15, 10, 14);
	deque_erase_range(15, 9, 14);
	deque_erase_range(15, 7, 14);
}

void	deque_insert_position(size_t initial_size, size_t position)
{
	std::deque<int> std_cont1;
	ft::deque<int> ft_cont1;
	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push_back(i);	
		ft_cont1.push_back(i);
	}
	ft::deque<int>::iterator ft_it;
	std::deque<int>::iterator std_it;	

	position = std::min(position, ft_cont1.size());

	ft_it = ft_cont1.insert(ft_cont1.begin() + position, 42);
	std_it = std_cont1.insert(std_cont1.begin() + position, 42);
	assert(std_cont1.empty() == ft_cont1.empty());
	assert(std_cont1.size() == ft_cont1.size());
	if (!std_cont1.empty())
		assert(*ft_it == *std_it);
	ft_it = ft_cont1.begin();
	std_it = std_cont1.begin();
	for (; ft_it != ft_cont1.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
}

void	deque_insert_fill(size_t initial_size, size_t position, size_t fill)
{
	std::deque<int> std_cont1;
	ft::deque<int> ft_cont1;
	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push_back(i);	
		ft_cont1.push_back(i);
	}
	ft::deque<int>::iterator ft_it;
	std::deque<int>::iterator std_it;	

	position = std::min(position, ft_cont1.size());

	ft_cont1.insert(ft_cont1.begin() + position, fill, 42);
	std_cont1.insert(std_cont1.begin() + position, fill, 42);
	assert(std_cont1.empty() == ft_cont1.empty());
	assert(std_cont1.size() == ft_cont1.size());
	ft_it = ft_cont1.begin();
	std_it = std_cont1.begin();
	for (; ft_it != ft_cont1.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
}

void	deque_insert_range(size_t initial_size, size_t position, \
		size_t initial_size2, size_t offset1, size_t offset2)
{
	//container that will reveive the insertion.
	std::deque<int> std_cont1;
	ft::deque<int> ft_cont1;
	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push_back(i);	
		ft_cont1.push_back(i);
	}

	//container that will give the range from which to insert.
	std::deque<int> std_cont2;
	ft::deque<int> ft_cont2;
	for (size_t i = 0; i < initial_size2; i++)
	{
		std_cont2.push_back(i + 42);	
		ft_cont2.push_back(i + 42);
	}

	ft::deque<int>::iterator ft_it;
	std::deque<int>::iterator std_it;	

	position = std::min(position, ft_cont1.size());
	offset2 = std::min(offset2, initial_size2); //making sure
	offset1 = std::min(offset1, offset2);//making shure !(offset1>offset2)

	ft_cont1.insert(ft_cont1.begin() + position, ft_cont2.begin() + offset1, ft_cont2.begin() + offset2);
	std_cont1.insert(std_cont1.begin() + position, std_cont2.begin() + offset1, std_cont2.begin() + offset2);
	assert(std_cont1.empty() == ft_cont1.empty());
	assert(std_cont1.size() == ft_cont1.size());
	ft_it = ft_cont1.begin();
	std_it = std_cont1.begin();
	for (; ft_it != ft_cont1.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
}

void deque_insert(void)
{
	//position
	deque_insert_position(7, 7);	
	deque_insert_position(7, 6);	
	deque_insert_position(8, 6);	
	deque_insert_position(15, 6);	
	deque_insert_position(1, 0);	
	deque_insert_position(2, 0);	
	deque_insert_position(0, 1);	
	deque_insert_position(0, 0);	

	//position + fill
	deque_insert_fill(7, 7, 0);	
	deque_insert_fill(7, 7, 3);	
	deque_insert_fill(7, 7, 6);	
	deque_insert_fill(7, 7, 15);	
	deque_insert_fill(7, 6, 0);	
	deque_insert_fill(7, 6, 1);	
	deque_insert_fill(7, 6, 2);	
	deque_insert_fill(8, 6, 0);	
	deque_insert_fill(8, 6, 2);	
	deque_insert_fill(8, 6, 8);	
	deque_insert_fill(15, 6, 1);	
	deque_insert_fill(1, 0, 8);	
	deque_insert_fill(2, 0, 8);	
	deque_insert_fill(2, 0, 1);	
	deque_insert_fill(2, 0, 2);	
	deque_insert_fill(2, 1, 2);	
	deque_insert_fill(2, 1, 1);	
	deque_insert_fill(0, 1, 8);	
	deque_insert_fill(0, 0, 8);	

	//range
	deque_insert_range(13, 12, 10, 2, 5);
	deque_insert_range(0, 12, 10, 2, 5);
	deque_insert_range(1, 0, 10, 2, 5);
	deque_insert_range(10, 0, 10, 0, 1);
	deque_insert_range(10, 0, 10, 0, 5);
	deque_insert_range(10, 0, 10, 5, 10);
	deque_insert_range(10, 0, 10, 0, 10);
	deque_insert_range(5, 4, 10, 0, 10);
	deque_insert_range(5, 4, 10, 3, 10);
	deque_insert_range(6, 3, 10, 2, 7);
	deque_insert_range(7, 4, 20, 0, 13);
	deque_insert_range(7, 4, 20, 0, 13);
	deque_insert_range(15, 10, 20, 0, 13);
	deque_insert_range(120, 30, 220, 56, 130);
}

void	deque_reverse_iterator(size_t initial_size)
{
	std::deque<int> std_cont1;
	ft::deque<int> ft_cont1;
	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push_back(i);	
		ft_cont1.push_back(i);
	}
	ft::deque<int>::iterator ft_it;
	std::deque<int>::iterator std_it;	
	ft::deque<int>::reverse_iterator ft_rev_it;
	std::deque<int>::reverse_iterator std_rev_it;	

	ft_rev_it = ft_cont1.rbegin();
	std_rev_it = std_cont1.rbegin();
	for (;ft_rev_it != ft_cont1.rend(); ft_rev_it++)
	{
		assert(*ft_rev_it == *std_rev_it);
		std_rev_it++;
	}
}

void	deque_test_at_symbol(void)
{
	std::deque<int> cont1;
	ft::deque<int> ft_cont1;
	int a;
	try { a = cont1.at(0); }
	catch (std::exception &e)
	{ std::cout << e.what() << std::endl; }
	try { a = ft_cont1.at(0); }
	catch (std::exception &e)
	{ std::cout << e.what() << std::endl; }

	std::deque<int> cont2(2,2);
	ft::deque<int> ft_cont2(2,2);
	try { a = cont2.at(2); }
	catch (std::exception &e)
	{ std::cout << e.what() << std::endl; }
	try { a = ft_cont2.at(2); }
	catch (std::exception &e)
	{ std::cout << e.what() << std::endl; }
}

void	deque_test_constness(void)
{
	ft::deque<const int> ft_cont1;	
	ft::deque<int> ft_cont2;	

	for (size_t i = 0; i < 16; i++)
	{
		ft_cont1.push_back(i);
		ft_cont2.push_back(i);	
	}

	//ft_cont1[0] = 12; //cant assign, good!
	ft_cont2[0] = 12;

	ft::deque<const int>::iterator it1 = ft_cont1.begin();
	ft::deque<int>::iterator it2 = ft_cont2.begin();

	//cant convert from const to non const, good!
	//ft::deque<int>::iterator it3 = it1;
	//ft::deque<int>::iterator it3(it1);
	//ft::deque<int>::iterator it3 = ft_cont1.begin();

	//can convert from non const to const
	//ft::deque<const int>::iterator it3 = it2;
	//no viable conversion for the std_version !!
	//std::deque<const int>::iterator it3 = it2;

	//cannot change value after convertion from non const to const, ok!
	// *it3 = 42;
}

void constructor_default(void)
{
	const ft::deque<int> ft_cont1(3, 2);

	ft::deque<int> ft_cont2;
	ft_cont2 = ft_cont1;

	const std::deque<int> std_cont1(3, 2);

	std::deque<int> std_cont2;
	std_cont2 = std_cont1;

	const std::deque<const int> std_cont3 = std::deque<const int>();
	const ft::deque<const int> ft_cont4 = ft::deque<const int>();
}

void deque_test_relational_operators(size_t initial_size)
{	
	std::deque<int> std_cont1;
	std::deque<int> std_cont2;
	ft::deque<int> ft_cont1;
	ft::deque<int> ft_cont2;

	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push_back(42 + i);	
		ft_cont1.push_back(42 + i);
		std_cont2.push_back(42 + i);	
		ft_cont2.push_back(42 + i);
	}	
	assert(std_cont1 == std_cont2);
	assert(ft_cont1 == ft_cont2);

	assert(std_cont1 <= std_cont2);
	assert(ft_cont1 <= ft_cont2);

	assert(std_cont1 >= std_cont2);
	assert(ft_cont1 >= ft_cont2);

	std_cont1.push_back(2);
	ft_cont1.push_back(2);

	assert(std_cont1 != std_cont2);
	assert(ft_cont1 != ft_cont2);

	assert(std_cont1 > std_cont2);
	assert(ft_cont1 > ft_cont2);

	assert(std_cont2 < std_cont1);
	assert(ft_cont2 < ft_cont1);

	assert(std_cont2 <= std_cont1);
	assert(ft_cont2 <= ft_cont1);
}

void tests_deque(void)
{
	copy_assignement();
	clear();
	constructor_fill(3,8);
	constructor_fill(17,8);
	constructor_fill(0,8);
	constructor_range();
	push();
	pop();
	test_mixed_push(15);
	test_resize();
	deque_test_assign();
	deque_erase_range();
	deque_insert();
	deque_reverse_iterator(13);
	deque_reverse_iterator(22);
	deque_reverse_iterator(1);
	deque_reverse_iterator(0);
	deque_test_at_symbol();

	constructor_default();
	deque_test_constness();
	deque_test_relational_operators(12);

	std::cout << "\033[32m [ OK ]\033[m" << std::endl;	
}
