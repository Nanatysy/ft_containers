//
// Created by Debby Willette on 10/26/21.
//

#ifndef FT_CONTAINERS_MY_PRINT_HPP
#define FT_CONTAINERS_MY_PRINT_HPP

#include "vector.hpp"

template <typename T>
void	my_print(const T & src)
{
	std::cout << src << " ";
}

template <typename T>
void	print_info(const ft::vector<T> & src)
{
	if (src.empty())
		std::cout << "Vector is empty";
	else
		std::cout << "Vector isn't empty. Size: " << src.size() << ", Capacity: "
		<< src.capacity();
	std::cout << std::endl;
}

#endif //FT_CONTAINERS_MY_PRINT_HPP
