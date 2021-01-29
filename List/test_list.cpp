/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test_list.cpp                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/15 14:44:27 by charmstr          #+#    #+#             */
/*   Updated: 2021/01/15 15:11:35 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <list>
#include <iostream>

int	main(int argc __attribute__((unused)), char **argv __attribute__((unused)))
{
	std::list<int> container;

	std::cout << std::list<int>::value_type();
	return (0);
}
