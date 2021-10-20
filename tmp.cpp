//
// Created by Debby Willette on 10/19/21.
//

#include <vector>
#include "iostream"

int main(void)
{
	std::vector<int> f;

	f.push_back(2);
	f.push_back(1);

	std::vector<int>::iterator it = f.begin();
	std::vector<int>::iterator it2 = it + 1;

	if (it > it2)
		std::cout << "true" << std::endl;
	else
		std::cout << "false" << std::endl;
	return (0);
}