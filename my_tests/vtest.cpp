//
// Created by Debby Willette on 5/16/22.
//

#include <iostream>
#include <cassert>
#include <vector>
#include "../vector.hpp"
#include "utilities.hpp"

#ifdef MY_CONTAINER
	namespace myNameSpace = ft;
#elif
	namespace myNameSpace = std;
#endif

void basic_info_print(const std::string& container, const std::string& type)
{
	std::cout << CIAN << container << YELLOW << " TEST WITH " << CIAN << type << YELLOW << " AS VALUE TYPE" << BLANK <<std::endl << std::endl;
}

void print_error_msg(const std::string & method)
{
	std::cout << RED << "'" << method << "' method fails" << BLANK << std::endl;
}

void print_ok_msg(const std::string & method)
{
	std::cout << GREEN << "'" << method << "'" << " OK" << BLANK << std::endl;
}

int main(void)
{
	{
		basic_info_print("VECTOR", "STRING");
		std::vector<std::string> st_vc;
		ft::vector<std::string>	my_vc;

		{
			std::cout << YELLOW << "Test 'Capacity' methods" << BLANK << std::endl;
			if (!(st_vc.empty() == my_vc.empty()))
			{
				print_error_msg("empty");
			}

			// adding 1 element
			st_vc.push_back("1");
			my_vc.push_back("1");

			if (!(st_vc.empty() == my_vc.empty()))
			{
				print_error_msg("empty");
			}
			print_ok_msg("empty");

			if (!(st_vc.size() == my_vc.size()))
			{
				print_error_msg("size");
			}
			print_ok_msg("size");

			// setting capacity
			st_vc.clear();
			my_vc.clear();
			if (st_vc.empty() == my_vc.empty())
			{
				st_vc.reserve(10);
				my_vc.reserve(10);
				if (!(st_vc.capacity() == my_vc.capacity()))
				{
					print_error_msg("reserve/capacity");
				}
				print_ok_msg("reserve/capacity");
			}

			std::cout << "Maximum size of a std::vector is " << st_vc.max_size() << std::endl;
			std::cout << "Maximum size of a ft::vector is " << my_vc.max_size() << std::endl;

			st_vc.clear();
			my_vc.clear();
			std::cout << std::endl;
		}
		{
			std::cout << YELLOW << "Test 'Modifiers' methods" << BLANK << std::endl;
			// clear
			// insert
			// erase
			// push_back
			// pop_back
			// resize
			// swap
		}
		{
			std::cout << YELLOW << "Test 'Element access' methods" << BLANK << std::endl;
			// at
			// operator []
			// front
		}
	}

	return (0);
}