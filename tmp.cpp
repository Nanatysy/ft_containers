//
// Created by Debby Willette on 10/19/21.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include "vector.hpp"

#include "my_print.hpp"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define CIAN "\x1b[36m"
#define BlANK "\x1b[0m"


int main(void)
{
	std::cout << YELLOW << "Vector tests: v_i (empty int vector), v_i_2 "
						   "(filled int vector), v_i_3 (const filled int "
						   "vector)" << BlANK << std::endl;


	std::vector<int> ref(6, 6);
	for (int i = 0; i < 6; i += 2)
		ref[i] = i;
	std::cout << CIAN << "Ref vector: ";
	std::for_each(ref.begin(), ref.end(), my_print<int>);
	std::cout << BlANK << std::endl;

	ft::vector<int> v_i;
//	ft::vector<int> v_i_5(4, 7);
	ft::vector<int> v_i_2(ref.begin(), ref.end());
	const ft::vector<int> v_i_3(ref.begin(), ref.end());


	std::cout << std::endl;
	std::cout << GREEN << "v_i_2 tests" << BlANK << std::endl;
	print_info(v_i_2);
	v_i_2.reserve(20);
	try {
		print_info(v_i_2);
		for (int i = 0; i < 15; i++)
			std::cout << v_i_2.at(i) << " ";
		std::cout << std::endl;
	}
	catch (std::exception & e) {
		std::cout << std::endl << RED << e.what() << BlANK << std::endl;
	}
	std::cout << v_i_2[2]++ << std::endl;

	for (size_t i = 0; i < v_i_2.size(); i++)
		std::cout << v_i_2[i] << " ";

	std::cout << std::endl;
	std::cout << "Front: " << v_i_2.front() << std::endl;
	std::cout << "Back: " << v_i_2.back() << std::endl;
	v_i_2.empty() ? std::cout << "Vector is empty" : std::cout << "Vector is not empty";
	std::cout << std::endl;

	std::cout << ref.max_size() << std::endl;
	std::cout << v_i_2.max_size() << std::endl;

	// copy constructor check
	std::cout << "---------------" << std::endl;

	ft::vector<int> v_i_copy(v_i_2);

	print_info(v_i_copy);
	for (size_t i = 0; i < v_i_copy.size(); i++)
		std::cout << v_i_copy[i] << " ";
	std::cout << std::endl;

	std::cout << "---------------" << std::endl;


	std::cout << std::endl << GREEN << "v_i tests" << BlANK << std::endl;
	print_info(v_i);

	//operator= check
	v_i = v_i_copy;
	print_info(v_i);
	for (size_t i = 0; i < v_i.size(); i++)
		std::cout << v_i[i] << " ";
	std::cout << std::endl;

	std::cout << std::endl << "----------->  Const test  <-------------" << std::endl;

	std::cout << std::endl << GREEN << "v_i_3 tests" << BlANK << std::endl;
//	v_i_3.reserve(20); error (method not const)
	try {
		print_info(v_i_3);
		for (int i = 0; i < 15; i++)
			std::cout << v_i_3.at(i) << " ";
		std::cout << std::endl;
	}
	catch (std::exception & e) {
		std::cout << std::endl << RED << e.what() << BlANK << std::endl;
	}

	for (size_t i = 0; i < v_i_3.size(); i++)
		std::cout << v_i_3[i] << " ";

	std::cout << std::endl;
	std::cout << "Front: " << v_i_3.front() << std::endl;
	std::cout << "Back: " << v_i_3.back() << std::endl;
	v_i_3.empty() ? std::cout << "Vector is empty" : std::cout << "Vector is not empty";
	std::cout << std::endl;


	{
		std::vector<int> fo(3,100);
		std::vector<int> ba(2,200);

		ft::vector<int> foo(fo.begin(), fo.end());
		ft::vector<int> bar(ba.begin(), ba.end());

		if (foo==bar) std::cout << "foo and bar are equal - ";
		if (fo==ba) std::cout << "fo and ba are equal" << std::endl;
		if (foo!=bar) std::cout << "foo and bar are not equal - ";
		if (fo!=ba) std::cout << "fo and ba are not equal" << std::endl;
		if (foo< bar) std::cout << "foo is less than bar - ";
		if (fo< ba) std::cout << "fo is less than ba" << std::endl;
		if (foo> bar) std::cout << "foo is greater than bar - ";
		if (fo> ba) std::cout << "fo is greater than ba" << std::endl;
		if (foo<=bar) std::cout << "foo is less than or equal to bar - ";
		if (fo<=ba) std::cout << "fo is less than or equal to ba" << std::endl;
		if (foo>=bar) std::cout << "foo is greater than or equal to bar - ";
		if (fo>=ba) std::cout << "fo is greater than or equal to ba" << std::endl;
	}

	{
		std::vector<int> fo(0);
		for (int i = 0; i < 10; i++)
			fo.push_back(i);

		ft::vector<int> foo(fo.begin(), fo.end());
		ft::vector<int>::iterator it = foo.begin();
//		ft::vector<int>::iterator ite = foo.end();

//		foo.insert(it, 5, 5);
////		it = foo.insert(it, 6);
////		it = foo.insert(it, 7);
//		ft::vector<int>::iterator ite = foo.begin();
		std::for_each(it, foo.end(), my_print<int>);
		std::cout << std::endl;
		std::cout << YELLOW;
		std::for_each(fo.begin(), fo.end(), my_print<int>);
		std::cout << BlANK << std::endl;

		ft::vector<int>::iterator middle = std::find(foo.begin(), foo.end(),
													  0);
		ft::vector<int>::iterator first = std::find(foo.begin(), foo.end(), 5);
		ft::vector<int>::iterator last = std::find(foo.begin(), foo.end(), 9);

//		foo.insert(middle, first, last);
//		std::for_each(foo.begin(), foo.end(), my_print<int>);
//		std::cout << std::endl;

		std::vector<int>::iterator middle2 = std::find(fo.begin(), fo.end(),
													 0);
		std::vector<int>::iterator first2 = std::find(fo.begin(), fo.end(),
													  5);
		std::vector<int>::iterator last2 = std::find(fo.begin(), fo.end(), 9);

		fo.insert(middle2, first2, last2);
		std::cout << YELLOW;
		std::for_each(fo.begin(), fo.end(), my_print<int>);
		std::cout << BlANK << std::endl;

//		for ( ; it != foo.end(); ++it)
//			std::cout << *it << " ";
		std::cout << std::endl;
	}

	{

		std::cout << "-------------" << std::endl;
		std::vector<int> foo(4, 100);
		std::vector<int>::iterator it = foo.begin();
		++it;
		*it = 5;

		ft::vector<int> fo(foo.begin(), foo.end());
		ft::vector<int>::iterator fit = fo.begin();
		for ( ; fit != fo.end(); ++fit)
			std::cout << *fit << " ";
		std::cout << std::endl;

		ft::vector<int>::iterator fff = fo.begin();
		++fff;
		ft::vector<int>::iterator ff2 = fff;
		++ff2;
		fo.erase(fff, ff2);
		fit = fo.begin();
		for ( ; fit != fo.end(); ++fit)
			std::cout << *fit << " ";
		std::cout << std::endl;
	}


	return (0);
}