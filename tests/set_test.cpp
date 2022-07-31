#include <iostream>
#include "set.hpp"


int main(void) {
	ft::set<int> first;
//	first.print_tree();


	ft::set<int>::iterator it = first.begin();
	ft::set<int>::iterator ite = first.end();

	while (it != ite)
	{
		std::cout << *it << " ";
		++it;
	}
	std::cout << std::endl;


	std::cout << std::endl << "---------------------" << std::endl;


	std::vector<int> ref;
	for (int i = 1; i < 11; i++)
	{
		ref.push_back(i);
		ref.push_back(50 + i);
	}
	ft::set<int> second(ref.begin(), ref.end());

	std::cout << std::endl << "---------------------" << std::endl;

	second.print_tree();
	std::cout << std::endl;

	ft::set<int>::iterator it2 = second.begin();
	ft::set<int>::iterator ite2 = second.end();
	while(it2 != ite2)
	{
		std::cout << *it2 << " ";
		it2++;
	}
	std::cout << std::endl;

	std::cout << std::endl << "----------&----------" << std::endl;

//	ft::set<int, int>::iterator td = second.find(10);
	second.erase(51);
	second.print_tree();

	std::cout << std::endl;

	it2 = second.begin();
	ite2 = second.end();
	while(it2 != ite2)
	{
		std::cout << *it2 << " ";
		it2++;
	}
	std::cout << std::endl;


}
