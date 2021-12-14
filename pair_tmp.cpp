//
// Created by Debby Willette on 11/10/21.
//

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>

#include "pair.hpp"

int main()
{
	{
		std::vector<ft::pair<int, std::string> > v;

		v.push_back(ft::make_pair(2, "baz"));
		v.push_back(ft::make_pair(2, "bar"));
		v.push_back(ft::make_pair(1, "foo"));

		std::sort(v.begin(), v.end());

		std::vector<ft::pair<int, std::string> >::iterator it = v.begin();

		for ( ; it != v.end(); it++)
		{
			std::cout << "{" << it->first << ", " << it->second << "}\n";
		}
	}

	{
		ft::pair<std::string, int> str_int("first", 1);
		ft::pair<int, float> int_float(35, 34.5);
		ft::pair<int, float> int_float2;

		int_float2 = int_float;
		ft::pair<char, int> ch_int(int_float);
		ft::pair<int, float> int_float_2(int_float);

		std::cout << "{" << str_int.first << ", " << str_int.second << "}\n";
		std::cout << "{" << int_float.first << ", " << int_float.second << "}\n";
		std::cout << "{" << int_float2.first << ", " << int_float2.second << "}\n";
		std::cout << "{" << ch_int.first << ", " << ch_int.second << "}\n";
		std::cout << "{" << int_float_2.first << ", " << int_float_2.second << "}\n";


		int_float >= int_float_2 ? std::cout << "bigger or equal" : std::cout
		<< "less";
		std::cout << std::endl;

		int_float > int_float_2 ? std::cout << "bigger" : std::cout << "less";
		std::cout << std::endl;

		int_float < int_float_2 ? std::cout << "less" : std::cout << "bigger";
		std::cout << std::endl;

		int_float <= int_float_2 ? std::cout << "less or equal" : std::cout <<
		"bigger";
		std::cout << std::endl;


	}

	{

		std::pair<int, int> ref(3, 4);
		std::pair<int, int> new_p;

		new_p = ref;
		std::cout << "{" << ref.first << ", " << ref.second << "}\n";
		std::cout << "{" << new_p.first << ", " << new_p.second << "}\n";


	}
}