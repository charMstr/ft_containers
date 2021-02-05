/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_stack.cpp                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/05 09:46:31 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/05 23:29:23 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"
#include <iterator>
#include <stack>

void	stack_test_empty(void)
{
	ft::stack<int> ft_cont;
	std::stack<int> std_cont;

	assert(ft_cont.empty() == std_cont.empty());
	assert(ft_cont.size() == std_cont.size());

	ft_cont.push(42);
	ft_cont.push(43);

	std_cont.push(42);
	std_cont.push(43);
	assert(ft_cont.empty() == std_cont.empty());
	assert(ft_cont.size() == std_cont.size());
}

void	stack_test_push_and_pop(size_t size)
{
	ft::stack<int> ft_cont;
	std::stack<int> std_cont;

	for (size_t i = 0; i < size; i++)
	{
		std_cont.push(42 + size);
		ft_cont.push(42 + size);
	}
	assert(ft_cont.empty() == std_cont.empty());
	assert(ft_cont.size() == std_cont.size());

	size = ft_cont.size();
	for (size_t i = 0; i < size; i++)
	{
		std_cont.pop();
		ft_cont.pop();
		assert(ft_cont.empty() == std_cont.empty());
		assert(ft_cont.size() == std_cont.size());
	}
}

void	stack_test_push(void)
{
	stack_test_push_and_pop(0);
	stack_test_push_and_pop(1);
	stack_test_push_and_pop(4);
	stack_test_push_and_pop(11);
	stack_test_push_and_pop(21);
}

void	stack_test_top(size_t initial_size)
{	
	/* 
	** //accessing the top of an empty container: segfault
	** std::stack<int> std_cont;
	** int &a =  std_cont.top();
	** (void)a;
	*/
	std::stack<int> std_cont;
	ft::stack<int> ft_cont;

	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont.push(42 + i);	
		ft_cont.push(42 + i);
	}	
	ft_cont.top() = 12; //ok, assignable
	std_cont.top() = 12; //ok, assignable
	int &a = ft_cont.top();
	int &b = std_cont.top();
	a += 3;
	b += 3;
	//std::cout << ft_cont.top() << std::endl;
	assert(ft_cont.top() == std_cont.top());

	while (ft_cont.size())
	{
		assert(ft_cont.top() == ft_cont.top());
		ft_cont.pop();
		std_cont.pop();
	}
}

void stack_test_top_const(void)
{
	std::stack<const int> std_cont;
	std_cont.push(42);	
	std_cont.pop();

	ft::stack<const int> ft_cont;
	ft_cont.push(42);
	ft_cont.pop();

	//OK
	/*
	const int &a = ft_cont.top();
	const int &b = std_cont.top();
	*/

	//OK
	/*
	ft_cont.top() = 12;
	std_cont.top() = 12;
	*/
}

void stack_test_relational_operators(size_t initial_size)
{	
	std::stack<int> std_cont1;
	std::stack<int> std_cont2;
	ft::stack<int> ft_cont1;
	ft::stack<int> ft_cont2;

	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push(42 + i);	
		ft_cont1.push(42 + i);
		std_cont2.push(42 + i);	
		ft_cont2.push(42 + i);
	}	
	assert(std_cont1 == std_cont2);
	assert(ft_cont1 == ft_cont2);

	assert(std_cont1 <= std_cont2);
	assert(ft_cont1 <= ft_cont2);

	assert(std_cont1 >= std_cont2);
	assert(ft_cont1 >= ft_cont2);

	std_cont1.push(2);
	ft_cont1.push(2);

	assert(std_cont1 != std_cont2);
	assert(ft_cont1 != ft_cont2);

	assert(std_cont1 > std_cont2);
	assert(ft_cont1 > ft_cont2);

	assert(std_cont2 < std_cont1);
	assert(ft_cont2 < ft_cont1);

	assert(std_cont2 <= std_cont1);
	assert(ft_cont2 <= ft_cont1);
}

void	tests_stack(void)
{
	stack_test_empty();
	stack_test_push();
	stack_test_top(42);
	stack_test_top_const();

	stack_test_relational_operators(12);

	std::cout << "\033[32m [ OK ]\033[m" << std::endl;	
}
