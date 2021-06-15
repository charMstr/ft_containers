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

# include "../ft_utils.hpp"

# include <map>
# include "../map.hpp"
# include "../multimap.hpp"

# include <set>
# include "../set.hpp"
# include "../multiset.hpp"

#include <assert.h>
# include <exception>

void	introduce_test(char *str);

void	end_test(char *str);

void	test_random_access_iterator(void);

void	tests_vector(void);

void	tests_reverse_iterator(void);

void	tests_deque(void);

void	tests_stack(void);

void	tests_list(void);

void	tests_rb_tree(void);

void	tests_map(void);

void	tests_multimap(void);

void	output_int_with_4_char(const int &num);
void	output_string_with_4_char(const std::string &str);

class test_class
{
	public:
	int haha;	
	test_class() : haha(int()) {}
};

#endif
