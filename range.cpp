//
// Created by Debby Willette on 1/18/22.
//

#include <iostream>
#include <map>
#include "map.hpp"
#include "pair.hpp"

int main(void)
{
	std::map<int, int> ref;
	ft::map<int, int> comp;
	std::vector<ft::pair<int, int> > example;

	for (int i = 0; i < 10; i++)
	{
		ref.insert(std::make_pair(i, i));
		ref.insert(std::make_pair(i + 10, i + 10));
		example.push_back(ft::make_pair(i, i));
		example.push_back(ft::make_pair(i + 10, i + 10));
	}
	comp.insert(example.begin(), example.end());

	for (std::map<int, int>::iterator it = ref.begin(); it != ref.end(); ++it)
		std::cout << it->second << " ";
	std::cout << std::endl;

	for (ft::map<int, int>::iterator it = comp.begin(); it != comp.end(); ++it)
		std::cout << it->second << " ";
	std::cout << std::endl;

	std::cout << "---------------low------------" << std::endl;

//	std::pair<std::map<int, int>::const_iterator, std::map<int, int>::const_iterator> first;
//	ft::pair<ft::map<int, int>::const_iterator, ft::map<int, int>::const_iterator> second;
//
//	first = ref.equal_range(4);
//	second = comp.equal_range(4);
//
//	for (; first.first != first.second; ++first.first)
//		std::cout << first.first->second << " ";
//	std::cout << "|" << std::endl;
//
//	for (; second.first != second.second; ++second.first)
//		std::cout << second.first->second << " ";
//	std::cout << "|" <<std::endl;
//
//	std::cout << "----------------------------" << std::endl;
//
//	first = ref.equal_range(22);
//	second = comp.equal_range(22);
//
//	for (; first.first != first.second; ++first.first)
//		std::cout << first.first->second << " ";
//	std::cout << "|" << std::endl;
//
//	for (; second.first != second.second; ++second.first)
//		std::cout << second.first->second << " ";
//	std::cout << "|" << std::endl;

	std::map<int, int>::const_iterator first = ref.lower_bound(4);
	(first == ref.end()) ? std::cout << "not found" : std::cout << first->second;
	std::cout << std::endl;

	ft::map<int, int>::const_iterator second = comp.lower_bound(4);
	(second == comp.end()) ? std::cout << "not found" : std::cout << second->second;
	std::cout << std::endl;

	std::cout << "----------------------------" << std::endl;

	first = ref.lower_bound(22);
	(first == ref.end()) ? std::cout << "not found" : std::cout << first->second;
	std::cout << std::endl;

	second = comp.lower_bound(22);
	(second == comp.end()) ? std::cout << "not found" : std::cout << second->second;
	std::cout << std::endl;

	std::cout << "--------------upper-------------" << std::endl;

	first = ref.upper_bound(4);
	(first == ref.end()) ? std::cout << "not found" : std::cout << first->second;
	std::cout << std::endl;

	second = comp.upper_bound(4);
	(second == comp.end()) ? std::cout << "not found" : std::cout << second->second;
	std::cout << std::endl;

	std::cout << "----------------------------" << std::endl;

	first = ref.upper_bound(22);
	(first == ref.end()) ? std::cout << "not found" : std::cout << first->second;
	std::cout << std::endl;

	second = comp.upper_bound(22);
	(second == comp.end()) ? std::cout << "not found" : std::cout << second->second;
	std::cout << std::endl;


	return (0);
}