//
// Created by Debby Willette on 10/19/21.
//

#include <vector>
#include <algorithm>
#include <iostream>
#include <string>
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

	std::vector<float> fff(6, 5.8);

	ft::vector<int> v_i;

	std::allocator<int> __unused al = v_i.get_allocator();
	ft::vector<int> v_i_5(4, 7);
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
	v_i.resize(12, 0);
	print_info(v_i);
	for (size_t i = 0; i < v_i.size(); i++)
		std::cout << v_i[i] << " ";
	std::cout << std::endl;
	v_i.clear();
	print_info(v_i);

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
		std::cout << std::endl << "----------->  Compare operators test  "
								  "<-------------"	<< std::endl;
		std::cout << std::endl;

		std::vector<int> fo(8,100);
		std::vector<int> ba(2,100);

		ft::vector<int> foo(fo.begin(), fo.end());
		ft::vector<int> bar(ba.begin(), ba.end());

		((foo==bar) == (fo==ba)) ? std::cout << "true ==" << std::endl : std::cout << "false ==" << std::endl;
		((foo!=bar) == (fo!=ba)) ? std::cout << "true !=" << std::endl : std::cout << "false !=" << std::endl;
		((foo<bar) == (fo<ba)) ? std::cout << "true <" << std::endl : std::cout << "false <" << std::endl;
		((foo<=bar) == (fo<=ba)) ? std::cout << "true <=" << std::endl : std::cout << "false <=" << std::endl;
		((foo>bar) == (fo>ba)) ? std::cout << "true >" << std::endl : std::cout << "false >" << std::endl;
		((foo>=bar) == (fo>=ba)) ? std::cout << "true >=" << std::endl : std::cout << "false >=" << std::endl;
	}

	{

		std::cout << std::endl << "----------->    "
								  "<-------------"	<< std::endl;
		std::cout << std::endl;

		std::vector<int> fo(0);
		for (int i = 0; i < 10; i++)
			fo.push_back(i);

		ft::vector<int> foo(fo.begin(), fo.end());
		ft::vector<int>::iterator it = foo.begin();
//		ft::vector<int>::iterator ite = foo.end();

//		foo.insert(it, 5, 5);
////		it = foo.insert(it, 6);
		it = foo.insert(it, 7);
//		ft::vector<int>::iterator ite = foo.begin();
		std::for_each(it, foo.end(), my_print<int>);
		std::cout << std::endl;
		std::cout << YELLOW;
		std::for_each(fo.begin(), fo.end(), my_print<int>);
		std::cout << BlANK << std::endl;

		ft::vector<int>::iterator middle = std::find(foo.begin(), foo.end(),2);
		ft::vector<int>::iterator first = std::find(foo.begin(), foo.end(), 5);
		ft::vector<int>::iterator last = std::find(foo.begin(), foo.end(), 8);

		foo.insert(middle, first, last);
		std::for_each(foo.begin(), foo.end(), my_print<int>);
		std::cout << std::endl;

		std::vector<int>::iterator middle2 = std::find(fo.begin(), fo.end(),
													 2);
		std::vector<int>::iterator first2 = std::find(fo.begin(), fo.end(),
													  5);
		std::vector<int>::iterator last2 = std::find(fo.begin(), fo.end(), 8);

		fo.insert(middle2, first2, last2);
		std::cout << YELLOW;
		std::for_each(fo.begin(), fo.end(), my_print<int>);
		std::cout << BlANK << std::endl;

//		for ( ; it != foo.end(); ++it)
//			std::cout << *it << " ";
		std::cout << std::endl;
	}

//	{
//
//		std::cout << "-------------" << std::endl;
//		std::vector<int> foo(4, 100);
//		std::vector<int>::iterator it = foo.begin();
//		++it;
//		*it = 5;
//
//		ft::vector<int> fo(foo.begin(), foo.end());
//		ft::vector<int>::iterator fit = fo.begin();
//		for ( ; fit != fo.end(); ++fit)
//			std::cout << *fit << " ";
//		std::cout << std::endl;
//
//		ft::vector<int>::iterator fff = fo.begin();
//		++fff;
//		ft::vector<int>::iterator ff2 = fff;
//		++ff2;
//		fo.erase(fff, ff2);
//		fit = fo.begin();
//		for ( ; fit != fo.end(); ++fit)
//			std::cout << *fit << " ";
//		std::cout << std::endl;
//	}

	{
		ft::vector<std::string> v_s;

		v_s.push_back("Hello");
		v_s.push_back("world");
		v_s.push_back("!");
		std::cout << v_s[0] << std::endl;

		std::cout << v_s.back() << std::endl;
	}
	{
		std::cout << "----------->  Swap  <-----------" << std::endl;

		ft::vector<float> f1(5, 0.1);
		ft::vector<float> f2(10, 1.2);

		std::cout << "f1: ";
		std::for_each(f1.begin(), f1.end(), my_print<float>);
		print_info(f1);
		std::cout << std::endl;
		std::cout << "f2: ";
		std::for_each(f2.begin(), f2.end(), my_print<float>);
		print_info(f2);
		std::cout << std::endl;



		ft::swap(f1, f2);
		f1.swap(f2);


		std::cout << "f1: ";
		std::for_each(f1.begin(), f1.end(), my_print<float>);
		print_info(f1);
		std::cout << std::endl;
		std::cout << "f2: ";
		std::for_each(f2.begin(), f2.end(), my_print<float>);
		print_info(f2);
		std::cout << std::endl;

		ft::vector<float>::iterator it = f1.begin();
		f1[0] = 0.5;
		f1[1] = 0.6;

		std::cout << "-------------------------" << std::endl;

		std::cout << "f1: ";
		std::for_each(f1.begin(), f1.end(), my_print<float>);
		std::cout << std::endl;

		f1.erase(it);

		std::cout << "f1: ";
		std::for_each(f1.begin(), f1.end(), my_print<float>);
		print_info(f1);

		f1.erase(f1.begin(), f1.end());
		std::cout << "f1: ";
		std::for_each(f1.begin(), f1.end(), my_print<float>);
		print_info(f1);

		std::cout << "-------------------------" << std::endl;

		std::cout << "f2: ";
		std::for_each(f2.begin(), f2.end(), my_print<float>);
		print_info(f2);
		f1.assign(f2.begin(), f2.end());
		std::cout << "f1: ";
		std::for_each(f1.begin(), f1.end(), my_print<float>);
		print_info(f1);

		f1.assign(f1.begin(), f1.end() - 1);
		std::cout << "f1: ";
		std::for_each(f1.begin(), f1.end(), my_print<float>);
		print_info(f1);


		f1.assign(3, 0.8);
		std::cout << "f1: ";
		std::for_each(f1.begin(), f1.end(), my_print<float>);
		print_info(f1);

		std::cout << "-------------------------" << std::endl;

	}

	return (0);
}