/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tests_list.cpp                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: charmstr <charmstr@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/02/09 16:25:20 by charmstr          #+#    #+#             */
/*   Updated: 2021/02/14 02:36:49 by charmstr         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "functions_tests.hpp"
#include <iterator>

template< typename T >
void	compare_list(std::list<T> &std_cont, ft::list<T> &ft_cont)
{
	assert(ft_cont.size() == std_cont.size());
	assert(ft_cont.empty() == std_cont.empty());

	typename ft::list<T>::iterator ft_it = ft_cont.begin();
	typename std::list<T>::iterator std_it = std_cont.begin();

	for (; ft_it != ft_cont.end(); ft_it++)
	{
		assert(*ft_it == *std_it);
		std_it++;
	}
}

template <typename T>
void display_ft_list(ft::list<T> &ft_cont)
{
	std::cout << std::endl << "FT CONTENT:" << std::endl;
	std::cout << "size: " << ft_cont.size() << std::endl;
	std::cout << "empty: " << ft_cont.empty() << std::endl;
	typename ft::list<T>::iterator ft_it = ft_cont.begin();
	for (; ft_it != ft_cont.end(); ft_it++)
	{
		std::cout << *ft_it	<< " ";
	}
	std::cout << std::endl;
}

template <typename T>
void display_std_list(std::list<T> &std_cont)
{
	std::cout << std::endl << "STD CONTENT:" << std::endl;
	std::cout << "size: " << std_cont.size() << std::endl;
	std::cout << "empty: " << std_cont.empty() << std::endl;
	typename std::list<T>::iterator std_it = std_cont.begin();
	for (; std_it != std_cont.end(); std_it++)
	{
		std::cout << *std_it	<< " ";
	}
	std::cout << std::endl;
}

void	test_list_default_constructor(void)
{
	ft::list<test_class> ft_cont;	
	std::list<test_class> std_cont;

	assert(ft_cont.size() == std_cont.size());
	assert(ft_cont.max_size() == std_cont.max_size());
}

void	test_list_fill_contstructor(size_t size)
{
	ft::list<int> ft_cont(size, 42);
	std::list<int> std_cont(size, 42);

	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);
	compare_list<int>(std_cont, ft_cont);
}

void	test_list_range_constructor(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_back(i + 42);	
		std_cont.push_back(i + 42);	
	}

	ft::list<int>::iterator ft_it = ft_cont.begin();
	std::list<int>::iterator std_it = std_cont.begin();

	//from start to end;
	ft::list<int> ft_cont2(ft_it, ft_cont.end());
	std::list<int> std_cont2(std_it, std_cont.end());
	compare_list<int>(std_cont2, ft_cont2);

	if (size >= 1)
	{
		ft_it++;
		ft_it++;
	}
	if (size >= 2)
	{
		std_it++;
		std_it++;
	}
	//from non start to end
	ft::list<int> ft_cont3(ft_it, ft_cont.end());
	std::list<int> std_cont3(std_it, std_cont.end());
	compare_list<int>(std_cont3, ft_cont3);
}

void 	test_list_copy_constructor(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_back(i + 42);	
		std_cont.push_back(i + 42);	
	}

	ft::list<int> ft_cont2(ft_cont);
	std::list<int> std_cont2(std_cont);
	compare_list<int>(std_cont2, ft_cont2);
}

void	tests_list_constructors(void)
{
	test_list_default_constructor();

	test_list_fill_contstructor(0);
	test_list_fill_contstructor(1);
	test_list_fill_contstructor(12);

	test_list_range_constructor(0);
	test_list_range_constructor(1);
	test_list_range_constructor(14);

	test_list_copy_constructor(0);
	test_list_copy_constructor(1);
	test_list_copy_constructor(13);
}


void test_list_push_back(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_back(i);	
		std_cont.push_back(i);	
	}
	compare_list<int>(std_cont, ft_cont);
	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);
}

void test_list_push_front(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
	}
	compare_list<int>(std_cont, ft_cont);
	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);
}

void tests_list_push_back_and_front(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
		ft_cont.push_back(i);	
		std_cont.push_back(i);	
	}
	compare_list<int>(std_cont, ft_cont);
	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);
}


void tests_list_push_back_and_front(void)
{
	test_list_push_front(0);		
	test_list_push_front(1);		
	test_list_push_front(7);		
	test_list_push_back(0);		
	test_list_push_back(1);		
	test_list_push_back(7);		

	tests_list_push_back_and_front(0);
	tests_list_push_back_and_front(1);
	tests_list_push_back_and_front(10);
}

void	tests_list_pop_front(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
		ft_cont.push_back(i);	
		std_cont.push_back(i);	
	}
	for (size_t i = 0; i < size * 2; i++)
	{
		ft_cont.pop_front();	
		std_cont.pop_front();	
		//display_ft_list<int>(ft_cont);
		//display_std_list<int>(std_cont);
		compare_list<int>(std_cont, ft_cont);
	}
}

void	tests_list_pop_back(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
		ft_cont.push_back(i);	
		std_cont.push_back(i);	
	}
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.pop_back();	
		std_cont.pop_back();	
		//display_ft_list<int>(ft_cont);
		//display_std_list<int>(std_cont);
		compare_list<int>(std_cont, ft_cont);
	}
}
void tests_list_pop_back_and_front(void)
{
	tests_list_pop_back(0);	
	tests_list_pop_back(1);	
	tests_list_pop_back(8);	
	tests_list_pop_front(0);	
	tests_list_pop_front(1);	
	tests_list_pop_front(8);	
}

void	tests_iterator_conversions(void)
{
	std::list<int> std_cont1;
	std::list<const int> std_cont2;

	std::list<int>::iterator it;
	std::list<const int>::iterator it_const;
	it = std_cont1.begin();
//	it = std_cont2.begin(); 		//cannot compile: OK
	it_const = std_cont2.begin();
	*it = 12;
//	*it_const = 12;					//cannot assign: OK
//	it_const = std_cont1.begin();	//cannot compile: OK
//	it = it_const;					//cannot compile: OK
	//conversion from a const to a non const.
	std::list<int>::const_iterator it_const2(it); //conversion OK
	assert(*it_const2 == 12);
	//*it_const2 = 13; // not assignable, OK
	//std::list<int>::iterator it2(it_const2); //no conversion OK

	//////////////////////////////////////////////////////////
	ft::list<int> ft_cont1(2, 3);
	ft::list<const int> ft_cont2(3, 3);

	ft::list<int>::iterator ft_it = ft_cont1.begin();
	ft::list<const int>::iterator ft_it_const = ft_cont2.begin();
	ft_it = ft_cont1.begin();
//	ft_it = ft_cont2.begin();		//cannot compile: OK
	ft_it_const = ft_cont2.begin();
	*ft_it = 12;
//	*ft_it_const = 12;				//cannot assign: OK
//	ft_it_const = ft_cont1.begin();	//cannot compile: OK
//	ft_it = ft_it_const;			//cannot compile: OK
	//conversion from a const to a non const.
	ft::list<int>::const_iterator ft_it_const2(ft_it);
	assert(*ft_it_const2 == 12); // OK
	// *ft_it_const2 = 13; // not assigble, OK
	//ft::list<int>::iterator ft_it3(ft_it_const2); //no conversion OK
}

void 	test_reverse_iteration(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
	}
	ft::list<int>::reverse_iterator ft_it = ft_cont.rbegin();
	std::list<int>::reverse_iterator std_it = std_cont.rbegin();
	for (;ft_it != ft_cont.rend(); ft_it++)
	{
		assert(*ft_it == *std_it);		
		std_it++;
	}
}

void 	test_front_and_back(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
	}	
	assert(ft_cont.front() == std_cont.front());
	assert(ft_cont.back() == std_cont.back());
	ft_cont.front() = 42;
	std_cont.front() = 42;
	assert(ft_cont.front() == std_cont.front());

	//same but with a const content
	ft::list<const int> ft_cont2;	
	std::list<const int> std_cont2;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont2.push_front(i);	
		std_cont2.push_front(i);	
	}	
	//ft_cont2.front() = 42;	//OK, does not compile
	//std_cont2.front() = 42;	//OK, does not compile
}

void	tests_front_and_back(void)
{
//	test_front_and_back(0);
	test_front_and_back(1);
	test_front_and_back(2);
	test_front_and_back(7);
}

void 	tests_assign(size_t size)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
	}	

	ft::list<int> ft_cont2;
	std::list<int> std_cont2;
	//assign with n and vall
	ft_cont2.assign(3, 100);
	std_cont2.assign(3, 100);

	//assign with inputiterators.
	ft_cont2.assign(ft_cont.begin(), ft_cont.end());
	std_cont2.assign(std_cont.begin(), std_cont.end());
	compare_list<int>(std_cont, ft_cont);
}

void tests_assign(void)
{
	tests_assign(0);
	tests_assign(1);
	tests_assign(13);
}

void tests_insert_one(size_t size, size_t offset)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
	}	
	offset = std::min(offset, size);

	ft::list<int>::iterator ft_it = ft_cont.begin();
	std::list<int>::iterator std_it = std_cont.begin();
	for (size_t i = 0; i < offset; i++)
	{
		ft_it++;
		std_it++;
	}
	ft_it = ft_cont.insert(ft_it, 42);
	std_it = std_cont.insert(std_it, 42);
	assert(*ft_it == *std_it);
	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);
	compare_list<int>(std_cont, ft_cont);
}

void tests_insert_fill(size_t size, size_t offset, size_t size_fill)
{
	ft::list<int> ft_cont;	
	std::list<int> std_cont;
	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
	}	
	offset = std::min(offset, size);

	ft::list<int>::iterator ft_it = ft_cont.begin();
	std::list<int>::iterator std_it = std_cont.begin();
	for (size_t i = 0; i < offset; i++)
	{
		ft_it++;
		std_it++;
	}
	//insertion with fill
	ft_cont.insert(ft_it, size_fill, 42);
	std_cont.insert(std_it, size_fill, 42);
	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);
	compare_list<int>(std_cont, ft_cont);
}

void tests_insert_range(size_t size, size_t position, size_t size2, size_t offset1, size_t offset2)
{
	//container 1
	ft::list<int> ft_cont;
	std::list<int> std_cont;	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
	}	

	//container 2
	ft::list<int> ft_cont2;
	std::list<int> std_cont2;
	for (size_t i = 0; i < size2; i++)
	{
		ft_cont2.push_front(i);	
		std_cont2.push_front(i);	
	}	

	//set position in container 1
	position = std::min(position, size);
	ft::list<int>::iterator ft_it = ft_cont.begin();
	std::list<int>::iterator std_it = std_cont.begin();
	for (size_t i = 0; i < position; i++)
	{
		ft_it++;
		std_it++;
	}

	//set the range iterators in the container 2
	ft::list<int>::iterator ft_it1 = ft_cont2.begin();
	std::list<int>::iterator std_it1 = std_cont2.begin();
	ft::list<int>::iterator ft_it2 = ft_cont2.begin();
	std::list<int>::iterator std_it2 = std_cont2.begin();
	offset2 = std::min(offset2, size2);
	offset1 = std::min(offset1, offset2);	
	for (size_t i = 0; i < offset1; i++)
	{
		ft_it1++;
		std_it1++;
	}
	for (size_t i = 0; i < offset2; i++)
	{
		ft_it2++;
		std_it2++;
	}
	//insertion with range
	ft_cont.insert(ft_it, ft_it1, ft_it2);
	std_cont.insert(std_it, std_it1, std_it2);

	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);
	compare_list<int>(std_cont, ft_cont);
}


void tests_insert(void)
{
	//ONE INSERTION
	//inserting in an empty list
	tests_insert_one(0,0);
	//insert_oneing in a non empty list at the begining.
	tests_insert_one(1,0);
	tests_insert_one(2,0);
	//insert_oneing in a non empty list, in the middle.
	tests_insert_one(1,1);
	tests_insert_one(2,1);
	tests_insert_one(3,2);
	//insert_oneing in a non empty list, at the end.
	tests_insert_one(2,2);
	tests_insert_one(3,3);

	//FILL INSERTION
	//inserting in an empty list: 0
	tests_insert_fill(0, 0, 0);
	//inserting in an empty list: 3
	tests_insert_fill(0, 0, 3);
	//inserting in a non empty list at the begining: 0
	tests_insert_fill(2, 0, 0);
	//inserting in a non empty list at the begining: 3
	tests_insert_fill(2, 0, 3);
	//inserting in a non empty list, in the middle: 0
	tests_insert_fill(2, 1, 0);
	//inserting in a non empty list, in the middle: 3
	tests_insert_fill(2, 1, 3);
	//inserting in a non empty list, at the end: 0
	tests_insert_fill(2, 2, 0);
	//inserting in a non empty list, at the end: 3
	tests_insert_fill(2, 2, 3);

	//RANGE INSERTION
	//inserting in an empty list from an empty list:
//void tests_insert_range(size_t size, size_t position, size_t size2, size_t offset1, size_t offset2)
	tests_insert_range(0, 0, 0, 0, 0);
	//inserting in an empty list from an non empty list:
	tests_insert_range(0, 0, 3, 0, 3);
	//inserting in an non empty list from an empty list:
	tests_insert_range(3, 0, 0, 0, 0);
	//inserting in an non empty list from an non empty list: at start
	tests_insert_range(4, 0, 6, 1, 3);
	//inserting in an non empty list from an non empty list: in the middle
	tests_insert_range(4, 2, 6, 1, 3);
	//inserting in an non empty list from an non empty list: at the end
	tests_insert_range(4, 4, 6, 0, 5);
}

//note: std fails when trying to erase the begin of an empty list, or if we try
//	to erase the end of an non empty list.
void  test_list_erase_one(size_t size, size_t position)
{
	ft::list<int> ft_cont;
	std::list<int> std_cont;	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_back(i);	
		std_cont.push_back(i);	
	}	
	position = std::min(position, size);
	if (position == size) //make sure the position is not set to the end.
		position--;
	ft::list<int>::iterator ft_it = ft_cont.begin();
	std::list<int>::iterator std_it = std_cont.begin();
	for (size_t i = 0; i < position; i++)
	{
		ft_it++;
		std_it++;
	}
	std_it = std_cont.erase(std_it);
	ft_it = ft_cont.erase(ft_it);
	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);	
	if (std_it != std_cont.end())
		assert(*std_it == *ft_it);
	compare_list<int>(std_cont, ft_cont);
}

//note: std fails when trying to erase the begin of an empty list, or if we try
//	to erase the end of an non empty list.
void  test_list_erase_range(size_t size, size_t position1, size_t position2)
{
	ft::list<int> ft_cont;
	std::list<int> std_cont;	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont.push_back(i);	
		std_cont.push_back(i);	
	}	
	position2 = std::min(position2, size);
	position1 = std::min(position1, position2);

	//set the first iterator of the range
	ft::list<int>::iterator ft_it = ft_cont.begin();
	std::list<int>::iterator std_it = std_cont.begin();
	for (size_t i = 0; i < position1; i++)
	{
		ft_it++;
		std_it++;
	}
	//set the second iterator of the range
	ft::list<int>::iterator ft_it2 = ft_cont.begin();
	std::list<int>::iterator std_it2 = std_cont.begin();
	for (size_t i = 0; i < position2; i++)
	{
		ft_it2++;
		std_it2++;
	}
	std_it = std_cont.erase(std_it, std_it2);
	ft_it = ft_cont.erase(ft_it, ft_it2);
	if (std_it != std_cont.end())
		assert(*std_it == *ft_it);
	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);	
	compare_list<int>(std_cont, ft_cont);
}
void	tests_erase()
{
	//ERASING ONE
	//erasing in an empty container, std fails
	//test_list_erase_one(0, 0);
	//erasing  in a non empty container: std fails if we try to erase end()
	test_list_erase_one(1, 0);	
	test_list_erase_one(1, 1);
	test_list_erase_one(3, 0);
	test_list_erase_one(3, 1);
	test_list_erase_one(3, 2);
	test_list_erase_one(6, 3);

	//ERASING RANGE
	//erasing in an empty container
	test_list_erase_range(0, 1, 2);
	//erasing in a non empty container, but nill range
	test_list_erase_range(1, 1, 1);
	test_list_erase_range(2, 1, 1);
	test_list_erase_range(3, 1, 1);
	//erasing in a non empty container, with valid range
	test_list_erase_range(3, 0, 1);
	test_list_erase_range(3, 0, 2);
	test_list_erase_range(3, 0, 3);
	test_list_erase_range(3, 2, 3);
}

void tests_swap(void)
{
	//container 1
	ft::list<int> ft_cont;
	std::list<int> std_cont;	
	for (size_t i = 0; i < 12; i++)
	{
		ft_cont.push_front(i);	
		std_cont.push_front(i);	
	}	

	//container 2
	ft::list<int> ft_cont2;
	std::list<int> std_cont2;
	for (size_t i = 0; i < 16; i++)
	{
		ft_cont2.push_front(i + 42);	
		std_cont2.push_front(i + 42);	
	}

	ft_cont.swap(ft_cont2);
	std_cont.swap(std_cont2);
	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);	
	compare_list<int>(std_cont, ft_cont);
	compare_list<int>(std_cont2, ft_cont2);
}

void	test_list_resize(size_t initial_size, size_t new_size)
{
	ft::list<int> ft_cont;
	std::list<int> std_cont;	
	for (size_t i = 0; i < initial_size; i++)
	{
		ft_cont.push_back(i);	
		std_cont.push_back(i);	
	}	
	ft_cont.resize(new_size, 42);
	std_cont.resize(new_size, 42);
	//display_ft_list<int>(ft_cont);
	//display_std_list<int>(std_cont);	
	compare_list<int>(std_cont, ft_cont);
}


void	tests_resize(void)
{
	//container is first 0, then 0 after resizing
	test_list_resize(0, 0);
	//container is first 0, then 12 after resizing
	test_list_resize(0, 12);
	//container is first 12, then 0 after resizing
	test_list_resize(12, 0);
	//container is first 12, then 14 after resizing
	test_list_resize(12, 14);
	//container is first 14, then 12 after resizing
	test_list_resize(14, 12);
}

void 	test_splice1(size_t initial_size1, size_t initial_size2, size_t position1)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < initial_size1; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
	}	

	ft::list<int> ft_cont2;
	std::list<int> std_cont2;	
	for (size_t i = 0; i < initial_size2; i++)
	{
		ft_cont2.push_back(i + 42);	
		std_cont2.push_back(i + 42);	
	}	
	//make sure position is not out of range.d
	position1 = std::min(position1, initial_size1);

	ft::list<int>::iterator ft_it = ft_cont1.begin();
	std::list<int>::iterator std_it = std_cont1.begin();
	for (size_t i = 0; i < position1; i++)
	{
		ft_it++;
		std_it++;
	}
	ft_cont1.splice(ft_it, ft_cont2);
	std_cont1.splice(std_it, std_cont2);
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
	//display_ft_list<int>(ft_cont2);
	//display_std_list<int>(std_cont2);	
	compare_list<int>(std_cont2, ft_cont2);
}

void 	test_splice2(size_t initial_size1, size_t initial_size2, \
		size_t position1, size_t position2)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < initial_size1; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
	}	

	ft::list<int> ft_cont2;
	std::list<int> std_cont2;	
	for (size_t i = 0; i < initial_size2; i++)
	{
		ft_cont2.push_back(i + 42);	
		std_cont2.push_back(i + 42);	
	}	
	//make sure position is not out of range.
	position1 = std::min(position1, initial_size1);
	ft::list<int>::iterator ft_it = ft_cont1.begin();
	std::list<int>::iterator std_it = std_cont1.begin();
	for (size_t i = 0; i < position1; i++)
	{
		ft_it++;
		std_it++;
	}

	//make sure position is not out of range.
	position2= std::min(position2, initial_size2);
	if (position2 == initial_size2 && initial_size2 != 0)
		position2--; //avoid using end as the element we extract from list2.
	ft::list<int>::iterator ft_it2 = ft_cont2.begin();
	std::list<int>::iterator std_it2 = std_cont2.begin();
	for (size_t i = 0; i < position2; i++)
	{
		ft_it2++;
		std_it2++;
	}
	ft_cont1.splice(ft_it, ft_cont2, ft_it2);
	std_cont1.splice(std_it, std_cont2, std_it2);
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
	//display_ft_list<int>(ft_cont2);
	//display_std_list<int>(std_cont2);	
	compare_list<int>(std_cont2, ft_cont2);
}

void 	test_splice3(size_t initial_size1, size_t initial_size2, \
		size_t position1, size_t range1, size_t range2)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < initial_size1; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
	}	

	ft::list<int> ft_cont2;
	std::list<int> std_cont2;	
	for (size_t i = 0; i < initial_size2; i++)
	{
		ft_cont2.push_back(i + 42);	
		std_cont2.push_back(i + 42);	
	}	
	//make sure position is not out of range.
	position1 = std::min(position1, initial_size1);
	ft::list<int>::iterator ft_it = ft_cont1.begin();
	std::list<int>::iterator std_it = std_cont1.begin();
	for (size_t i = 0; i < position1; i++)
	{
		ft_it++;
		std_it++;
	}

	//make sure the range1 and range2 are within the initial_size2.
	range2 = std::min(range2, initial_size2);
	range1 = std::min(range2, range1);
	ft::list<int>::iterator ft_start = ft_cont2.begin();
	std::list<int>::iterator std_start = std_cont2.begin();
	for (size_t i = 0; i < range1; i++)
	{
		ft_start++;
		std_start++;
	}
	ft::list<int>::iterator ft_end  = ft_cont2.begin();
	std::list<int>::iterator std_end = std_cont2.begin();
	for (size_t i = 0; i < range2; i++)
	{
		ft_end ++;
		std_end++;
	}
	ft_cont1.splice(ft_it, ft_cont2, ft_start, ft_end);
	std_cont1.splice(std_it, std_cont2, std_start, std_end);
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
	//display_ft_list<int>(ft_cont2);
	//display_std_list<int>(std_cont2);	
	compare_list<int>(std_cont2, ft_cont2);
}

void	tests_splice(void)
{
	// (1) //
	//first container is EMPTY, second is EMPTY
	test_splice1(0, 0, 1);	
	//first container is NOT empty, second is EMPTY
	test_splice1(1, 0, 1);	
	//first container is EMPTY, second is NOT empty
	test_splice1(0, 1, 1);	
	//first container is NOT empty, second is NOT empty
	test_splice1(1, 1, 0);	 //insert at the begining
	test_splice1(1, 1, 1);	 //insert at the end
	test_splice1(3, 2, 1);	 //insert in the middle

	// (2) // args: size1, size2, position1, position2
	//first container is EMPTY, second container is EMPTY
	//note: the std list goes wrong if we provide an empty container2
	//test_splice2(0, 0, 1, 0);	
	//first container is EMPTY, second container is NOT empty.
	test_splice2(0, 3, 0, 0);	
	test_splice2(0, 3, 0, 1);	
	test_splice2(0, 3, 0, 2);	
	//first container is NOT empty, second container is NOT empty
	test_splice2(5, 3, 0, 0);	
	test_splice2(5, 3, 2, 1);	
	test_splice2(5, 3, 5, 2);	

	// (3) 
	//first container is EMPTY, second container is EMPTY
	test_splice3(0, 0, 0, 0, 0);
	//first container is EMPTY, second container is NOT empty, null range
	test_splice3(0, 1, 0, 0, 0);
	//first container is EMPTY, second container is NOT empty, valid range
	test_splice3(0, 1, 0, 0, 1);
	//first container is NOT empty, second container is NOT empty, valid range
	test_splice3(3, 1, 0, 0, 1);
	test_splice3(3, 1, 2, 0, 1);
	test_splice3(3, 1, 3, 0, 1);
	//first container is NOT empty, second is NOT empty, range in the middle
	test_splice3(3, 5, 0, 0, 2);
	test_splice3(3, 5, 2, 2, 4);
	test_splice3(3, 5, 3, 2, 5);
}

void	test_remove_val(size_t size, int val)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
		ft_cont1.push_front(i);	
		std_cont1.push_front(i);	
	}	
	ft_cont1.remove(val);
	std_cont1.remove(val);
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
}

template < typename T >
bool remove_if(T  i)
{
	return ( i >= 2 && i < 5);	
}


void test_remove_if(size_t size)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
		ft_cont1.push_front(i);	
		std_cont1.push_front(i);	
	}	
	ft_cont1.remove_if(remove_if<int>);
	std_cont1.remove_if(remove_if<int>);
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
}

void	tests_remove(void)
{
	//NORMAL REMOVE
	//trying to remove on the extremities
	test_remove_val(13, 12);	
	//trying to remove in the middle
	test_remove_val(13, 10);	
	//trying to remove but not found
	test_remove_val(12, 13);	
	//trying to remove in an empty container
	test_remove_val(0, 1);

	//REMOVE IF ( removing between 2 and 5).
	test_remove_if(13);	
	test_remove_if(6);	
	test_remove_if(5);	
	test_remove_if(3);	
	test_remove_if(2);	
	test_remove_if(1);
}

void test_list_reverse(size_t size)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
	}	
	ft_cont1.reverse();
	std_cont1.reverse();
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
	if (size > 0)
	{
		assert(ft_cont1.front() == std_cont1.front());
		assert(ft_cont1.back() == std_cont1.back());
	}
}

void tests_list_reverse(void)
{
	//should not do anything when size is less than two
	test_list_reverse(0);
	test_list_reverse(1);
	test_list_reverse(2);
	test_list_reverse(8);
}

void	test_list_sort(size_t initial_size)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < initial_size; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
		ft_cont1.push_front(i);	
		std_cont1.push_front(i);	
	}		
	std_cont1.sort();
	ft_cont1.sort();
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
}

template< typename T >
bool comparison(T i1, T &i2)
{
	return (i1 < i2);
}

void test_list_sort_cmp(size_t initial_size)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < initial_size; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
		ft_cont1.push_front(i);	
		std_cont1.push_front(i);	
	}		
	std_cont1.sort(comparison<int>);
	ft_cont1.sort(comparison<int>);
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
}

void tests_list_sort(void)
{
	//test_list_sort(0); //nothing should happen if size is less than 2.
	test_list_sort(1);
	test_list_sort(2);
	test_list_sort(4);
	test_list_sort(9);
	test_list_sort_cmp(1);
	test_list_sort_cmp(2);
	test_list_sort_cmp(4);
	test_list_sort_cmp(9);
}

void test_unique(size_t size)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
		ft_cont1.push_front(i);	
		std_cont1.push_front(i);	
	}
	std_cont1.sort();
	ft_cont1.sort();
	std_cont1.unique();
	ft_cont1.unique();
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
}

bool unique_pred(int i, int j)
{
	return (i == j + 1);
}

void test_unique_pred(size_t size)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < size; i++)
	{
		ft_cont1.push_back(i);	
		std_cont1.push_back(i);	
		ft_cont1.push_front(i);	
		std_cont1.push_front(i);	
	}
	std_cont1.unique(unique_pred);
	ft_cont1.unique(unique_pred);
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
}

void tests_unique(void)
{
	test_unique(0);	
	test_unique(1);	
	test_unique(2);	
	test_unique(6);	

	test_unique_pred(0);
	test_unique_pred(1);
	test_unique_pred(2);
	test_unique_pred(6);
}

void test_list_merge(size_t size1, size_t size2)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = 0; i < size1; i++)
	{
		ft_cont1.push_back(i * 2);	
		std_cont1.push_back(i * 2);	
	}
	ft::list<int> ft_cont2;
	std::list<int> std_cont2;	
	for (size_t i = 0; i < size2; i++)
	{
		ft_cont2.push_back(i * 3);	
		std_cont2.push_back(i * 3);	
	}
	std_cont1.merge(std_cont2);
	ft_cont1.merge(ft_cont2);
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
	compare_list<int>(std_cont2, ft_cont2);
}

template< typename T >
bool comparison2(T i1, T &i2)
{
	return (i1 < i2);
}

void test_list_merge_comp(size_t size1, size_t size2, size_t offset1, \
		size_t offset2)
{
	ft::list<int> ft_cont1;
	std::list<int> std_cont1;	
	for (size_t i = offset1; i < (size1 * 2) + offset1; i += 2)
	{
		ft_cont1.push_back(i + 2);	
		std_cont1.push_back(i + 2);	
	}
	ft::list<int> ft_cont2;
	std::list<int> std_cont2;	
	for (size_t i = offset2; i < size2 * 2 + offset2; i += 2)
	{
		ft_cont2.push_back(i + 2);	
		std_cont2.push_back(i + 2);	
	}
	//display_ft_list<int>(ft_cont1);
	std_cont1.merge(std_cont2, comparison2<int>);
	ft_cont1.merge(ft_cont2, comparison2<int>);
	//display_ft_list<int>(ft_cont1);
	//display_std_list<int>(std_cont1);	
	compare_list<int>(std_cont1, ft_cont1);
	compare_list<int>(std_cont2, ft_cont2);
}

void tests_list_merge(void)
{
	//just merge
	test_list_merge(0, 0);
	test_list_merge(0, 1);
	test_list_merge(0, 2);
	test_list_merge(1, 0);
	test_list_merge(2, 0);
	test_list_merge(1, 1);
	test_list_merge(2, 2);
	test_list_merge(3, 2);
	test_list_merge(2, 3);
	test_list_merge(3, 3);

	//merge with predicate
	test_list_merge_comp(2, 3, 0, 0);
	test_list_merge_comp(2, 3, 1, 0);
	test_list_merge_comp(2, 3, 2, 0);
	test_list_merge_comp(2, 3, 3, 0);
	test_list_merge_comp(2, 3, 4, 0);
	test_list_merge_comp(2, 3, 0, 1);
	test_list_merge_comp(2, 3, 0, 2);
	test_list_merge_comp(2, 3, 0, 3);
	test_list_merge_comp(2, 3, 0, 4);
}


void list_test_relational_operators(size_t initial_size)
{	
	std::list<int> std_cont1;
	std::list<int> std_cont2;
	ft::list<int> ft_cont1;
	ft::list<int> ft_cont2;

	for (size_t i = 0; i < initial_size; i++)
	{
		std_cont1.push_back(42 + i);	
		ft_cont1.push_back(42 + i);
		std_cont2.push_back(42 + i);	
		ft_cont2.push_back(42 + i);
	}	
	assert(std_cont1 == std_cont2);
	assert(ft_cont1 == ft_cont2);

	assert(std_cont1 <= std_cont2);
	assert(ft_cont1 <= ft_cont2);

	assert(std_cont1 >= std_cont2);
	assert(ft_cont1 >= ft_cont2);

	std_cont1.push_back(2);
	ft_cont1.push_back(2);

	assert(std_cont1 != std_cont2);
	assert(ft_cont1 != ft_cont2);

	assert(std_cont1 > std_cont2);
	assert(ft_cont1 > ft_cont2);

	assert(std_cont2 < std_cont1);
	assert(ft_cont2 < ft_cont1);

	assert(std_cont2 <= std_cont1);
	assert(ft_cont2 <= ft_cont1);

	std_cont2.push_back(2);
	ft_cont2.push_back(2);
	std_cont2.push_back(2);
	ft_cont2.push_back(2);

	assert(std_cont1 != std_cont2);
	assert(ft_cont1 != ft_cont2);

	assert(std_cont1 < std_cont2);
	assert(ft_cont1 < ft_cont2);

	assert(std_cont2 > std_cont1);
	assert(ft_cont2 > ft_cont1);

	assert(std_cont2 >= std_cont1);
	assert(ft_cont2 >= ft_cont1);
}

void tests_list(void)
{	
	tests_iterator_conversions();
	tests_list_constructors();
	test_reverse_iteration(0);
	test_reverse_iteration(12);
	tests_list_push_back_and_front();
	tests_list_pop_back_and_front();
	tests_front_and_back();
	tests_assign();
	tests_insert();
	tests_erase();
	tests_swap();
	tests_resize();
	tests_splice();
	tests_remove();
	tests_list_reverse();
	tests_list_sort();
	tests_unique();
	tests_list_merge();
	list_test_relational_operators(12);

	std::cout << "\033[32m [ OK ]\033[m" << std::endl;	
}
