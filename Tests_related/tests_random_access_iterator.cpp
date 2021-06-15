/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_random_access_iterator.cpp                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/01/23 04:16:06 by charmstr          #+#    #+#             */
/*   Updated: 2021/06/15 05:37:17 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"

void	 test_operators(void)
{
	std::vector<int> std_cont;
	size_t size = 4;

	ft::random_access_iterator<int> my_it;
	ft::random_access_iterator<int> my_end;
	std::vector<int>::iterator std_it;
	std::vector<int>::iterator std_end;

	//filling the vector with values from 0 to n...
	for (size_t i = 0; i < size; i++)
	{
		std_cont.push_back(i);
	}

	//setting the ends.
	std_end = std_cont.end();
	my_end = std_cont.end().base();	

	//pree-increment OK
	my_it = std_cont.begin().base();	
	my_it = ++my_it;
	assert(my_it == std_cont.begin().base() + 1);

	//post-increment OK
	my_it = std_cont.begin().base();	
	my_it = my_it++;
	assert(my_it == std_cont.begin().base());

	//pre-increment in loop
	std_it = std_cont.begin();
	my_it = std_cont.begin().base();	
	for (size_t i = 0; i < size - 1; i++)
	{
		assert(*++std_it == *++my_it);	 //checking the content is the same
	}
	++std_it;
	++my_it;
	//!= sign
	assert(!(my_it != my_end));  //we arrived at the end
	assert(!(std_it != std_end)); //we also arrived at the end

	//post-increment in loop
	std_it = std_cont.begin();
	my_it = std_cont.begin().base();	
	for (size_t i = 0; i < size; i++)
	{
		assert(*std_it++ == *my_it++);	 //checking the content is the same
	}

	std_it = std_cont.end() - 1;
	my_it = std_cont.end().base() - 1;	
	//post decrement
	//here both the iteraro have reach end.
	for (size_t i = size ; i > 0; i--)
	{
		assert(*std_it-- == *my_it--);	 //checking the content is the same
	}

	//pre decrement
	std_it = std_cont.end();
	my_it = std_cont.end().base();	
	for (size_t i = size - 1; i > 0; i--)
	{
		assert(*--std_it == *--my_it);	 //checking the content is the same
	}

	//+= operator
	std_it = std_cont.begin();
	my_it = std_cont.begin().base();	
	for (size_t i = 0; i < size - 1; i++)
	{
		std_it += 1;
		my_it += 1;
		assert(*std_it == *my_it);	 //checking the content is the same
	}

	//+ operator
	std_it = std_cont.begin();
	my_it = std_cont.begin().base();	
	for (size_t i = 0; i < size - 1; i++)
	{
		std_it =  std_it + 1;
		my_it = my_it + 1;
		assert(*std_it == *my_it);	 //checking the content is the same
	}
	
	//+ operator when the iterator is on the right hand side
	std_it = std_cont.begin();
	my_it = std_cont.begin().base();	
	for (size_t i = 0; i < size - 1; i++)
	{
		std_it = 1 + std_it;
		my_it = 1 + my_it;
		assert(*std_it == *my_it);	 //checking the content is the same
	}

	//-= operator
	std_it = std_cont.end();
	my_it = std_cont.end().base();	
	for (size_t i = size; i > 0; i--)
	{
		std_it -= 1;
		my_it -= 1;
		assert(*std_it == *my_it);	 //checking the content is the same
	}

	//- operator
	std_it = std_cont.end();
	my_it = std_cont.end().base();	
	for (size_t i = size; i > 0; i--)
	{
		std_it =  std_it - 1;
		my_it = my_it - 1;
		assert(*std_it == *my_it);	 //checking the content is the same
	}	

	//-operator substracting two iterators.
	assert (my_it - (my_it + 2) == std_it - (std_it + 2));

	//comparison operators
	ft::random_access_iterator<int> my_it2;
	my_it2 = my_it - 1;
	assert (my_it2 < my_it);
	assert (my_it2 <= my_it);
	assert (my_it > my_it2);
	assert (my_it >= my_it2);
	assert (my_it >= my_it);
	assert (my_it <= my_it);

	//[]operator
	std_it = std_cont.begin();
	my_it = std_cont.begin().base();	
	for (size_t i = 0; i < std_cont.size(); i--)
		assert(std_it[i] == my_it[i]);
}

void test_arrow_operator(void)
{
	test_class instance1;
	instance1.haha = 42;
	std::vector<test_class> cont(1, instance1);
	std::vector<test_class>::iterator std_it = cont.begin();

	ft::random_access_iterator<test_class> my_it;
	my_it = cont.begin().base();
	std_it->haha = 43;
	assert(std_it->haha == 43);
	my_it->haha = 44;
	assert(std_it->haha == 44);
	assert(std_it->haha == my_it->haha);
}

void test_const_non_const_restrictions(void)
{
	//creation of two containers: std and ft
	ft::vector<int> ft_cont1(2,3);
	std::vector<int> std_cont1(2,3);

	ft::vector<int>::iterator ft_it1 = ft_cont1.begin();
	std::vector<int>::iterator std_it1 = std_cont1.begin();

	ft_it1++;   
	std_it1++; 

	*ft_it1 = 1;
	*std_it1 = 1;

	ft::vector<int>::const_iterator ft_const_it1 = ft_it1; 
	std::vector<int>::const_iterator std_const_it1 = std_it1; 

	*std_const_it1;

	//*ft_const_it1 = 12; Cant dereference: OK
	//*std_const_it1 = 12; Cant dereference: OK

	ft_const_it1++; //OK
	std_const_it1++; //OK

	//ft::vector<int>::iterator ft_it2 = ft_const_it1;
	//std::vector<int>::iterator std_it2 = std_const_it1;

	ft::vector<const int> ft_cont2(2, 3);
	std::vector<const int> std_cont2(2, 3);

	ft::vector<const int>::iterator ft_it4 = ft_cont2.begin();
	std::vector<const int>::iterator std_it4 = std_cont2.begin();

	//*ft_it4 = 3;
	//*std_it4 = 3;

	int a = *ft_it4;
	 a = *std_it4;
}

void test_conparison_between_const_and_non_const(void)
{
	//with STL version
	std::vector<int> std_cont1(2,3);

	std::vector<int>::iterator std_it1 = std_cont1.begin();
	std::vector<int>::const_iterator std_const_it1 = std_it1; 

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

	ft::vector<int>::iterator ft_it1 = ft_cont1.begin();
	ft::vector<int>::const_iterator ft_const_it1 = ft_it1; 

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

void	test_random_access_iterator(void)
{
	test_operators();
	test_arrow_operator();
	test_const_non_const_restrictions();
	test_conparison_between_const_and_non_const();
}
