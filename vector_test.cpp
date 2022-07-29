#include <iostream>

#include <vector>
#include "vector.hpp"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define CIAN "\x1b[36m"
#define BLANK "\x1b[0m"

// todo
//  3 types of constructor
//  operator =
//  size
//  max_size
//  resize
//  capacity
//  reserve
//  operator[]
//  at
//  assign
//  insert
//  erase
//  swap
//  clear

int main()
{
	{
		std::cout << YELLOW << "Int vector tests" << BLANK << std::endl;

		ft::vector<int> v_i;

		std::cout << "using method " << CIAN << "`push_back`" << BLANK<< " to add 10 elements to the vector" << std::endl;
		for (int i = 0; i < 10; ++i)
			v_i.push_back(i);

		v_i.empty() ? std::cout << "vector is empty" : std::cout
				<< "vector isn't "
				   "empty, size ="
				   " " << v_i.size();
		std::cout << std::endl;
		std::cout << CIAN << "`size`" << BLANK << " method: ";
		(v_i.size() == 10) ? std::cout << GREEN << "OK" : std::cout << RED << "FAIL";
		std::cout << BLANK << std::endl;

		std::cout << "using method " << CIAN << "`back`" << BLANK<< " to print elements" << std::endl;
		std::cout << "using method " << CIAN << "`pop_back`" << BLANK<< " to delete elements" << std::endl;
		while (!v_i.empty())
		{
			std::cout << v_i.back() << " ";
			v_i.pop_back();
		}
		std::cout << std::endl;

		v_i.empty() ? std::cout << "vector is empty" : std::cout
				<< "vector isn't "
				   "empty, size ="
				   " " << v_i.size();
		std::cout << std::endl;
		std::cout << CIAN << "`empty`" << BLANK << " method: ";
		(v_i.empty()) ? std::cout << GREEN << "OK" : std::cout << RED << "FAIL";
		std::cout << BLANK << std::endl;
	}

	{
		std::cout << YELLOW << "String vector tests" << BLANK << std::endl;

		ft::vector<std::string> v_s;

		v_s.push_back("Hello");
		v_s.push_back("world");
		v_s.push_back("!");
		v_s.push_back("My");
		v_s.push_back("name");
		v_s.push_back("is");
		v_s.push_back("Nastya");

		v_s.empty() ? std::cout << "vector is empty" : std::cout
				<< "vector isn't "
				   "empty, size ="
				   " " << v_s.size();
		std::cout << std::endl;

		std::cout << "using method " << CIAN << "`front`" << BLANK<< " to change first element to Good bay" << std::endl;
		v_s.front() = "Good bay";

		std::cout << "using " << CIAN << "`iterator`" << BLANK<< " to print elements" << std::endl;
		for (ft::vector<std::string>::iterator it = v_s.begin(); it != v_s.end(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "using " << CIAN << "`reverse iterator`" << BLANK<< " to print elements" << std::endl;
		for (ft::vector<std::string>::reverse_iterator it = v_s.rbegin(); it != v_s.rend(); ++it)
		{
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		v_s.empty() ? std::cout << "vector is empty" : std::cout
				<< "vector isn't "
				   "empty, size ="
				   " " << v_s.size();
	}

	{
		std::cout << std::endl << "----------->  Compare operators test  "
								  "<-------------"	<< std::endl;

		std::vector<int> fo;
		std::vector<int> ba;
		ft::vector<int> foo;
		ft::vector<int> bar;

		fo.push_back(0);
		foo.push_back(0);
		fo.push_back(1);
		foo.push_back(1);

		ba.push_back(0);
		bar.push_back(0);
		ba.push_back(2);
		bar.push_back(2);

		((foo==bar) == (fo==ba)) ? std::cout << "true ==" << std::endl : std::cout << "false ==" << std::endl;
		((foo!=bar) == (fo!=ba)) ? std::cout << "true !=" << std::endl : std::cout << "false !=" << std::endl;
		((foo<bar) == (fo<ba)) ? std::cout << "true <" << std::endl : std::cout << "false <" << std::endl;
		((foo<=bar) == (fo<=ba)) ? std::cout << "true <=" << std::endl : std::cout << "false <=" << std::endl;
		((foo>bar) == (fo>ba)) ? std::cout << "true >" << std::endl : std::cout << "false >" << std::endl;
		((foo>=bar) == (fo>=ba)) ? std::cout << "true >=" << std::endl : std::cout << "false >=" << std::endl;
	}

	return (0);
}