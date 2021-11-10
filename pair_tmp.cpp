//
// Created by Debby Willette on 11/10/21.
//

#include <iostream>
#include <iomanip>
#include <utility>
#include <vector>
#include <algorithm>
#include <string>

#include "pair.hpp"

int main()
{
	std::vector<ft::pair<int, std::string> > v;

	v.push_back(ft::make_pair(2, "baz"));
	v.push_back(ft::make_pair(2, "bar"));
	v.push_back(ft::make_pair(1, "foo"));

	std::sort(v.begin(), v.end());

	for(auto p: v) {
		std::cout << "{" << p.first << ", " << p.second << "}\n";
	}
}