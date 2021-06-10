/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_tests.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 04:59:05 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/09 23:06:26 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCIONS_TESTS_HPP
# define FUNCIONS_TESTS_HPP

#include <iostream>
#include <iterator>


# include "../rb_tree.hpp"

//# include <list>
//# include "../list.hpp"

#include <assert.h>
# include <exception>

void	introduce_test(char *str);

void	end_test(void);

void	test_random_access_iterator(void);

void	tests_vector(void);

void	tests_reverse_iterator(void);

void	tests_deque(void);

void	tests_stack(void);

void	tests_list(void);

void	tests_rb_tree();

class test_class
{
	public:
	int haha;	
	test_class() : haha(int()) {}
};

#endif
