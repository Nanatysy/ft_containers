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