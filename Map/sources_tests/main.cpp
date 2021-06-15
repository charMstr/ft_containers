/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 04:37:30 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/15 03:16:37 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"
#include <sstream>

void introduce_test(char *str)
{
	std::cout << std::endl << "\033[33m";
	std::cout << "#############################################################" << std::endl;
	std::cout << " test on: \033[32m" << str << "\033[33m"<< std::endl;
	std::cout << "#############################################################" << "\033[0m" <<  std::endl;
}

void end_test(char *str)
{
	std::cout << "\033[32m [ OK ]\033[33m for \033[32m" << str << std::endl;	
	std::cout << "\033[33m";
	std::cout << "#############################################################" << "\033[0m" <<  std::endl << std::endl;
}

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

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	/*
	char test_name1[] = "random access iterators";
	introduce_test(test_name1);
	test_random_access_iterator();
	end_test(test_name1);

	char test_name2[] = "reverse iterator";
	introduce_test(test_name2);
	tests_reverse_iterator();
	end_test(test_name2);
	
	char test_name3[] = "ft_vector";
	introduce_test(test_name3);
	tests_vector();
	end_test(test_name3);

	char test_name4[] = "ft_deque";
	introduce_test(test_name4);
	tests_deque();
	end_test(test_name4);

	char test_name5[] = "ft_stack";
	introduce_test(test_name5);
	tests_stack();
	end_test(test_name5);

	char test_name6[] = "ft_list";
	introduce_test(test_name6);
	tests_list();
	end_test(test_name6);

	char test_name7[] = "rb_tree";
	introduce_test(test_name7);
	tests_rb_tree();
	end_test(test_name7);
	
	char test_name8[] = "map";
	introduce_test(test_name8);
	tests_map();
	end_test(test_name8);

	char test_name9[] = "multimap";
	introduce_test(test_name9);
	tests_multimap();
	end_test(test_name9);
	*/

	char test_name10[] = "set";
	introduce_test(test_name10);
	tests_multimap();
	end_test(test_name10);

	char test_name11[] = "multiset";
	introduce_test(test_name11);
	tests_multimap();
	end_test(test_name11);

    return (0);
}
