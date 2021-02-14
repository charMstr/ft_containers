/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_tests.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 04:59:05 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/10 17:45:00 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCIONS_TESTS_HPP
# define FUNCIONS_TESTS_HPP

#include <iostream>
#include <iterator>

#include <vector>
#include "../ft_random_access_iterator.hpp"
#include "../vector.hpp"

# include <deque>
# include "../deque_iterator.hpp"
# include "../deque.hpp"

# include <stack>
# include "../stack.hpp"

# include <list>
# include "../list.hpp"

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

class test_class
{
	public:
	int haha;	
	test_class() : haha(int()) {}
};

#endif
