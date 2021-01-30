/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_reverse_iterator.cpp                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/30 04:01:24 by charmstr          #+#    #+#             */
/*   Updated: 2021/01/30 10:38:26 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"

/*
** when a reverse_iterator is build from an iterator, the iterator is not
** modified when modification are applied to the reverse iterator (like ++
** operator for example).
*/

void test_constructors(void)
{	
	std::vector<int> std_cont;	
	ft::vector<int> ft_cont;
	for (int i = 0; i < 3; i++)
	{
		std_cont.push_back(i);	
		ft_cont.push_back(i);	
	}

	ft::vector<int>::iterator  ft_it = ft_cont.begin();
	std::vector<int>::iterator std_it = std_cont.begin();

	//builing from an existing iterator;
	std::vector<int>::reverse_iterator r_std_it1(std_it + 1);
	ft::vector<int>::reverse_iterator r_ft_it1(ft_it + 1);

	//building straight away from an iterator:
	std::vector<int>::reverse_iterator r_std_it2(std_cont.begin());
	ft::vector<int>::reverse_iterator r_ft_it2(ft_cont.begin());

	//building from another reverse iterator;
	r_std_it2 = r_std_it1;
	r_ft_it2 = r_ft_it1;	
	assert(*r_std_it2 == *r_std_it1);
	assert(*r_ft_it2 == *r_ft_it1);
}

void	test_operators(size_t size, size_t offset)
{
	std::vector<int> std_cont;	
	ft::vector<int> ft_cont;

	for (size_t i = 0; i < size; i++)
	{
		std_cont.push_back(i);	
		ft_cont.push_back(i);
	}

	ft::vector<int>::iterator  ft_it;
	std::vector<int>::iterator std_it;

	std_it = std_cont.begin() + offset;
	ft_it = ft_cont.begin() + offset;

	std::vector<int>::reverse_iterator r_std_it(std_it);
	ft::vector<int>::reverse_iterator r_ft_it(ft_it);

	assert(*r_std_it == *r_ft_it);

	//post increment;
	for (size_t i = 0; i < offset - 1; i++)
	{
		assert(*r_ft_it++ == *r_std_it++);
		assert(*ft_it == *std_it); //making sure the original is not modified
	}

	//pre increment
	r_std_it = std_cont.rbegin() + offset;
	r_ft_it = ft_cont.rbegin() + offset;

	for (size_t i = 0; i < offset - 1; i++)
	{
//		std::cout << *r_ft_it << " vs " << *r_std_it << std::endl;
		assert(*++r_ft_it == *++r_std_it);
	}

	//pre decrement
	r_std_it = std_cont.rbegin() + offset;
	r_ft_it = ft_cont.rbegin() + offset;
	for (size_t i = 0; i < offset - 1; i++)
	{
		assert(*--r_ft_it == *--r_std_it);
	}

	//post decrement
	r_std_it = std_cont.rbegin() + offset;
	r_ft_it = ft_cont.rbegin() + offset;
	for (size_t i = 0; i < offset - 1; i++)
	{
		assert(*r_ft_it-- == *r_std_it--);
	}

	//operator + size_t
	r_std_it = std_cont.rbegin() + offset;
	r_ft_it = ft_cont.rbegin() + offset;
	assert(*(r_std_it + 2) == *(r_ft_it + 2));

	//operator - size_t
	assert(*(r_std_it - 2) == *(r_ft_it - 2));

	//operator +=
	r_std_it += 3;
	r_ft_it += 3;
	assert(*r_std_it == *r_ft_it);

	//operator -=
	r_std_it -= 3;
	r_ft_it -= 3;
	assert(*r_std_it == *r_ft_it);

	assert(r_std_it[2] == r_ft_it[2]);

	//size_t + reverse_it;
	r_std_it = std_cont.rbegin() + offset;
	r_ft_it = ft_cont.rbegin() + offset;
	r_std_it = 2 + r_std_it;
	r_ft_it = 2 + r_ft_it;
	assert(*r_std_it == *r_ft_it);

	//comparison operator;
	r_std_it = std_cont.rbegin() + offset;
	r_ft_it = ft_cont.rbegin() + offset;	
	assert(r_std_it < r_std_it + 1);
	assert(r_ft_it < r_ft_it + 1);
	assert(r_std_it + 1 > r_std_it);
	assert(r_ft_it + 1 > r_ft_it);
	assert(r_std_it <= r_std_it);
	assert(r_ft_it <= r_ft_it);
	assert(r_std_it >= r_std_it);
	assert(r_ft_it >= r_ft_it);
	assert(r_std_it + 1 >= r_std_it);
	assert(r_ft_it + 1 >= r_ft_it);
	assert(r_std_it <= r_std_it + 1);
	assert(r_ft_it <= r_ft_it + 1);

	//substrating a reverse iterator to another
	assert(r_ft_it - (r_ft_it - 1) == r_std_it - (r_std_it - 1));
}

void	test_rend_rbegin(size_t size)
{
	std::vector<int> std_cont;	
	ft::vector<int> ft_cont;

	for (size_t i = 0; i < size; i++)
	{
		std_cont.push_back(i);	
		ft_cont.push_back(i);
	}

	ft::vector<int>::iterator  ft_it;
	std::vector<int>::iterator std_it;

	std::vector<int>::reverse_iterator r_std_it;
	ft::vector<int>::reverse_iterator r_ft_it;

	r_std_it = std_cont.rbegin();
	r_ft_it = ft_cont.rbegin();
	assert(*r_std_it == *r_ft_it);

	/*
	for (; r_std_it != std_cont.rend(); r_std_it++)
	{
		std::cout << *r_std_it << ".";
	}
	std::cout << std::endl;

	for (; r_ft_it != ft_cont.rend(); r_ft_it++)
	{
		std::cout << *r_ft_it << ".";
	}
	std::cout << std::endl;
	*/
}

#include <list>
void test_(void)
{
	std::list<int> std_cont;

	for (int i = 0; i < 10; i++)
		std_cont.push_back(i);

	std::list<int>::reverse_iterator r_it = std_cont.rbegin();

	(void)r_it;
	//std::cout << r_it[3] << std::endl;
}

void	test_reverse_const_non_const_restrictions(void)
{
	//creation of two containers: std and ft
	ft::vector<int> ft_cont1(2,3);
	std::vector<int> std_cont1(2,3);

	//creation of two reverse iterator (non const).
	ft::vector<int>::reverse_iterator r_ft_it1 = ft_cont1.rbegin();
	std::vector<int>::reverse_iterator r_std_it1 = std_cont1.rbegin();
	
	//creatoin of two other reverse iterators (non const).
	ft::vector<int>::reverse_iterator r_ft_it2(r_ft_it1);
	std::vector<int>::reverse_iterator r_std_it2(r_std_it1);
	(void)r_std_it2;

	r_ft_it1++;   
	r_std_it1++; 

	*r_ft_it1 = 1;
	*r_std_it1 = 1;

	//creation of CONST reverse iterators from a non const reverse iterator.
	ft::vector<int>::const_reverse_iterator const_r_ft_it1 = r_ft_it1; 
	std::vector<int>::const_reverse_iterator const_r_std_it1 = r_std_it1; 

	const_r_ft_it1++; //OK
	const_r_std_it1++; //OK

	//*const_r_ft_it1 = 12; //Cant dereference: OK
	//*const_r_std_it1 = 12; //Cant dereference: OK
	
	//r_ft_it2 = r_ft_it1; //possible, OK
	//r_ft_it2 = const_r_ft_it1; //NOT possible, OK

	//std::vector<int>::reverse_iterator rit(const_r_std_it1); //possible, but
	//should not!
	//ft::vector<int>::reverse_iterator rit1(const_r_ft_it1); //impossible, OK

}

void test_reverse_comparison_between_const_and_non_const(void)
{
	std::vector<int> std_cont1(2,3);

	std::vector<int>::reverse_iterator std_it1 = std_cont1.rbegin();
	std::vector<int>::const_reverse_iterator std_const_it1 = std_it1; 

	assert (std_const_it1 == std_it1);
	assert (std_const_it1 <= std_it1);
	assert (!(std_const_it1 < std_it1));
	assert (std_const_it1 >= std_it1);
	assert (!(std_const_it1 > std_it1));
	
	std_const_it1++;
	assert(std_const_it1 != std_it1);
	assert(std_const_it1 >= std_it1);
	assert(std_const_it1 > std_it1);
	assert(!(std_const_it1 <= std_it1));
	assert(!(std_const_it1 < std_it1));

	assert(std_it1 != std_const_it1);
	assert(!(std_it1 == std_const_it1));
	assert(!(std_it1 >= std_const_it1));
	assert(!(std_it1 > std_const_it1));
	assert(std_it1 <= std_const_it1);
	assert(std_it1 < std_const_it1);

	size_t n;
	n = std_const_it1 - std_it1;
	n = std_it1 - std_const_it1;
	std_it1 += n;
	/*
	n = std_const_it1 + std_it1;
	n = std_it1 + std_const_it1;
	n = std_const_it1++ + std_it1;
	n = std_const_it1 + std_it1++;
	n = std_it1++ + std_const_it1;
	n = std_it1 + std_const_it1++;
	*/ //OK


	//with FT version (COPY PAST)
	ft::vector<int> ft_cont1(2,3);

	ft::vector<int>::reverse_iterator ft_it1 = ft_cont1.rbegin();
	ft::vector<int>::const_reverse_iterator ft_const_it1 = ft_it1; 

	assert (ft_it1 == ft_it1);
	assert (ft_it1 == ft_const_it1);
	assert (ft_const_it1 == ft_it1);
	assert (ft_const_it1 == ft_const_it1);
	assert (ft_const_it1 <= ft_it1);
	assert (!(ft_const_it1 < ft_it1));
	assert (ft_const_it1 >= ft_it1);
	assert (!(ft_const_it1 > ft_it1));
	
	ft_const_it1++;
	assert(ft_const_it1 != ft_it1);
	assert(ft_const_it1 >= ft_it1);
	assert(ft_const_it1 > ft_it1);
	assert(!(ft_const_it1 <= ft_it1));
	assert(!(ft_const_it1 < ft_it1));

	assert(ft_it1 != ft_const_it1);
	assert(!(ft_it1 == ft_const_it1));
	assert(!(ft_it1 >= ft_const_it1));
	assert(!(ft_it1 > ft_const_it1));
	assert(ft_it1 <= ft_const_it1);
	assert(ft_it1 < ft_const_it1);

	
	n = ft_const_it1 - ft_it1;
	n = ft_it1 - ft_const_it1;
	ft_it1 += n;

	/*
	n = ft_const_it1 + ft_it1;
	n = ft_it1 + ft_const_it1;
	n = ft_const_it1++ + ft_it1;
	n = ft_const_it1 + ft_it1++;
	n = ft_it1++ + ft_const_it1;
	n = ft_it1 + ft_const_it1++;
	*/ //OK should not be defined.
}

void	tests_reverse_iterator(void)
{
	test_constructors();
	test_operators(8, 4);
	test_rend_rbegin(4);
	test_reverse_const_non_const_restrictions();
	test_reverse_comparison_between_const_and_non_const();

	std::cout << "\033[32m [ OK ]\033[m" << std::endl;	
}
