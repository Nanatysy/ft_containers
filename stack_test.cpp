//
// Created by Debby Willette on 11/29/21.
//

#include <iostream>
#include <string>
#include <stack>
#include "stack.hpp"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define CIAN "\x1b[36m"
#define BlANK "\x1b[0m"

int main()
{
	{
		std::cout << YELLOW << "Int stack tests" << BlANK << std::endl;

		ft::stack<int> s_i;

		for (int i = 0; i < 10; ++i)
			s_i.push(i);

		s_i.empty() ? std::cout << "Stack is empty" : std::cout
				<< "Stack isn't "
				   "empty, size ="
				   " " << s_i.size();
		std::cout << std::endl;

//		s_i.top() = 99;

		while (!s_i.empty())
		{
			std::cout << s_i.top() << " ";
			s_i.pop();
		}
		std::cout << std::endl;

		s_i.empty() ? std::cout << "Stack is empty" : std::cout
				<< "Stack isn't "
				   "empty, size ="
				   " " << s_i.size();
		std::cout << std::endl;
	}

	{
		std::cout << YELLOW << "String stack tests" << BlANK << std::endl;

		ft::stack<std::string> s_s;

		s_s.push("Hello");
		s_s.push("world");
		s_s.push("!");
		s_s.push("My");
		s_s.push("name");
		s_s.push("is");
		s_s.push("Nastya");

		s_s.empty() ? std::cout << "Stack is empty" : std::cout
				<< "Stack isn't "
				   "empty, size ="
				   " " << s_s.size();
		std::cout << std::endl;

		s_s.top() = "Yoda";

		while (!s_s.empty())
		{
			std::cout << s_s.top() << " ";
			s_s.pop();
		}
		std::cout << std::endl;

		s_s.empty() ? std::cout << "Stack is empty" : std::cout
				<< "Stack isn't "
				   "empty, size ="
				   " " << s_s.size();
	}

	{
		std::cout << std::endl << "----------->  Compare operators test  "
								  "<-------------"	<< std::endl;

		std::stack<int> fo;
		std::stack<int> ba;

		ft::stack<int> foo;
		ft::stack<int> bar;

		fo.push(0);
		foo.push(0);
		fo.push(1);
		foo.push(1);

		ba.push(0);
		bar.push(0);
		ba.push(2);
		bar.push(2);

		if (foo==bar) std::cout << "foo and bar are equal - ";
		if (fo==ba) std::cout << "fo and ba are equal" << std::endl;
		if (foo!=bar) std::cout << "foo and bar are not equal - ";
		if (fo!=ba) std::cout << "fo and ba are not equal" << std::endl;
		if (foo< bar) std::cout << "foo is less than bar - ";
		if (fo< ba) std::cout << "fo is less than ba" << std::endl;
		if (foo> bar) std::cout << "foo is greater than bar - ";
		if (fo> ba) std::cout << "fo is greater than ba" << std::endl;
		if (foo<=bar) std::cout << "foo is less than or equal to bar - ";
		if (fo<=ba) std::cout << "fo is less than or equal to ba" << std::endl;
		if (foo>=bar) std::cout << "foo is greater than or equal to bar - ";
		if (fo>=ba) std::cout << "fo is greater than or equal to ba" << std::endl;
	}

	return (0);
}