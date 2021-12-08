//
// Created by Debby Willette on 11/24/21.
//

#include <iostream>
#include <vector>
#include "vector.hpp"
#include "my_print.hpp"

int main()
{
	std::vector<int> first;

	first.push_back(1);
	first.push_back(2);
	first.push_back(3);
	first.push_back(4);
	first.push_back(5);

	ft::vector<int> test(first.begin(), first.end());
//	std::for_each(test.begin(), test.end(), my_print<int>);
//	std::cout << std::endl;

	ft::vector<int>::reverse_iterator start = test.rbegin();
	ft::vector<int>::reverse_iterator it = test.rbegin();
	ft::vector<int>::reverse_iterator end = test.rend();

	std::cout << test.size() << std::endl;
	std::cout << end - start << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << *it << std::endl;
	std::cout << *(++it) << std::endl;
	std::cout << *(it++) << std::endl;
	std::cout << *it << std::endl;
	std::cout << *(--it) << std::endl;
	std::cout << *(it--) << std::endl;
	std::cout << *it << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << *(it + 2) << std::endl;
	it += 1;
	std::cout << *it << std::endl;
	std::cout << *(it - 1) << std::endl;
	it -= 1;
	std::cout << *it << std::endl;
	std::cout << "----------------" << std::endl;
	std::cout << it[2] << std::endl;
	std::cout << it.operator->() << std::endl;
	--it;
	std::cout << it.operator->() << std::endl;

	std::for_each(test.begin(), test.end(), my_print<int>);
	std::cout << std::endl;

	it[2] = 5;
	std::for_each(test.begin(), test.end(), my_print<int>);
	std::cout << std::endl;

	return (0);
}