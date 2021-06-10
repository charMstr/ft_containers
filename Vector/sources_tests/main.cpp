/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.cpp                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 04:37:30 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/08 12:46:01 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"

void introduce_test(char *str)
{
	std::cout << std::endl << "\033[33m";
	std::cout << "#############################################################" << std::endl;
	std::cout << " test on: \033[32m" << str << "\033[33m"<< std::endl;
	std::cout << "#############################################################" << "\033[0m" <<  std::endl;
}

void end_test(void)
{
	std::cout << "\033[33m";
	std::cout << "#############################################################" << std::endl;	
}

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	char test_name1[] = "random access iterators";
	introduce_test(test_name1);
	test_random_access_iterator();
	end_test();

	char test_name2[] = "reverse iterator";
	introduce_test(test_name2);
	tests_reverse_iterator();
	end_test();
	
	char test_name3[] = "ft_vector";
	introduce_test(test_name3);
	tests_vector();
	end_test();

	char test_name4[] = "ft_deque";
	introduce_test(test_name4);
	tests_deque();
	end_test();

	char test_name5[] = "ft_stack";
	introduce_test(test_name5);
	tests_stack();
	end_test();

	char test_name6[] = "ft_list";
	introduce_test(test_name6);
	tests_list();
	end_test();
	
    return (0);
}
