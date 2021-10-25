//
// Created by Debby Willette on 10/19/21.
//

#include <vector>
#include "iostream"
#include "vector.hpp"

int main(void)
{
//	std::vector<int> f;
//
//	f.push_back(2);
//	f.push_back(1);
//
//	std::vector<int>::iterator it = f.begin();
//	std::vector<int>::iterator it2 = it + 1;
//
//	if (it > it2)
//		std::cout << "true" << std::endl;
//	else
//		std::cout << "false" << std::endl;
//	return (0);

	std::vector<int> ref(4, 6);

	ft::vector<int> v_i;
	ft::vector<int> v_i_2(ref.begin(), ref.end());

	v_i_2.reserve(20);
	try {
		std::cout << "Size: " << v_i_2.size() << ", Capacity: " << v_i_2.capacity() << std::endl;
		for (int i = 0; i < 15; i++)
			std::cout << v_i_2.at(i) << " ";
		std::cout << std::endl;
	}
	catch (std::exception & e) {
		std::cout << e.what();
	}
//	ft::vector<int>::iterator it;


}