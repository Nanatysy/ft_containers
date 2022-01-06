//
// Created by Debby Willette on 12/14/21.
//

#include "map.hpp"
#include <map>

int main()
{
	ft::map<int, int> first;
//	first.print_tree();


	ft::map<int, int>::iterator it = first.begin();
	ft::map<int, int>::iterator ite = first.end();

	while (it != ite)
	{
		std::cout << it->second << " ";
		++it;
	}
	std::cout << std::endl;


	std::cout << std::endl << "---------------------" << std::endl;


	std::vector<ft::pair<int, int> > ref;
	for (int i = 1; i < 11; i++)
	{
		ref.push_back(ft::make_pair(i, i));
		ref.push_back(ft::make_pair(50 + i, 50 + i));
	}
	ft::map<int, int> second(ref.begin(), ref.end());

	std::cout << std::endl << "---------------------" << std::endl;

	second.print_tree();
	std::cout << std::endl;

	ft::map<int, int>::iterator it2 = second.begin();
	ft::map<int, int>::iterator ite2 = second.end();
	while(it2 != ite2)
	{
		std::cout << it2->second << " ";
		it2++;
	}
	std::cout << std::endl;

	std::cout << std::endl << "----------&----------" << std::endl;

//	ft::map<int, int>::iterator td = second.find(10);
	second.erase(8);

	second.print_tree();
	std::cout << std::endl;

//	it2 = second.begin();
//	while(it2 != second.end())
//	{
//		std::cout << it2->second << " ";
//		it2++;
//	}
//	std::cout << std::endl;


//	ft::map<int, int> second;
//	second = first;
//	second.print_tree();
//
//	ft::map<int, int>::value_type
//
//
//	std::map
//	ft::map<int, int> second(first);
//	second.print_tree();
	return (0);
}