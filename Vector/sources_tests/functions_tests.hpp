/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   functions_tests.hpp                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 04:59:05 by charmstr          #+#    #+#             */
/*   Updated: 2021/01/26 12:52:02 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FUNCIONS_TESTS_HPP
# define FUNCIONS_TESTS_HPP

#include <iostream>
#include "../ft_random_access_iterator.hpp"
#include "../vector.hpp"
#include <vector>
#include <assert.h>
# include <exception>

void	introduce_test(char *str);
void	end_test(void);

void	test_random_access_iterator(void);
void	tests_vector(void);

class test_class
{
	public:
	int haha;	
//	test_class()  ;
};

#endif
