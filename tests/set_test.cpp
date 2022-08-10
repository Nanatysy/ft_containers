#include <iostream>
#include "set.hpp"

int main()
{
	{
		ft::set<std::string> first;
		std::vector<std::string> ref;
		ref.push_back("a");
		ref.push_back("b");
		ref.push_back("c");
		ref.push_back("d");
		ref.push_back("ab");
		ft::set<std::string> second(ref.begin(), ref.end());

		std::cout << "First: ";
		for (ft::set<std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Second: ";
		for (ft::set<std::string>::iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		{
			ft::set<std::string> third(second);
			std::cout << "Third: ";
			for (ft::set<std::string>::iterator it = third.begin(); it != third.end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;

			ft::set<std::string> fourth = third;
			std::cout << "Fourth: ";
			for (ft::set<std::string>::iterator it = fourth.begin(); it != fourth.end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "Second: ";
		for (ft::set<std::string>::iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "second size: " << second.size() << std::endl;
		std::cout << "second max_size: " << second.max_size() << std::endl;
		std::cout << "is second empty: " << ((second.empty()) ? "yes" : "no");
		std::cout << std::endl;


		second["a"] = "z";
		second["z"] = "a";
		std::cout << second.size() << ", second after 2 operator[] : ";
		for (ft::set<std::string>::iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		first.swap(second);
		std::cout << "First after swap with second, size " << first.size() << " : ";
		for (ft::set<std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Second after swap with first, size " << second.size() << " : ";
		for (ft::set<std::string>::iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		ft::set<std::string>::iterator itq = first.find("q");
		if (itq != first.end()) {
			std::cout << "Method find: First contains 'q' key" << std::endl;
		}
		else {
			std::cout << "Method find: First does not contains 'q' key" << std::endl;
		}
		itq = first.find("z");
		if (itq != first.end()) {
			std::cout << "Method find: First contains 'z' key" << std::endl;
		}
		else {
			std::cout << "Method find: First does not contains 'z' key" << std::endl;
		}

		if (first.count("q") != 0) {
			std::cout << "Method count: First contains 'q' key" << std::endl;
		}
		else {
			std::cout << "Method count: First does not contains 'q' key" << std::endl;
		}
		if (first.count("z") != 0) {
			std::cout << "Method count: First contains 'z' key" << std::endl;
		}
		else {
			std::cout << "Method count: First does not contains 'z' key" << std::endl;
		}

		{
			std::cout << "lower_bound and upper_bound check" << std::endl;
			ft::set<int> myset;
			ft::set<int>::iterator itlow, itup;

			myset['a'] = 20;
			myset['b'] = 40;
			myset['c'] = 60;
			myset['d'] = 80;
			myset['e'] = 100;

			for (ft::set<int>::iterator f = myset.begin(); f != myset.end(); ++f) {
				std::cout << *f << " ";
			}
			std::cout << std::endl;

			itlow = myset.lower_bound('b');  // itlow points to b
			itup = myset.upper_bound('d');   // itup points to e (not d!)

			myset.erase(itlow,itup);        // erases [itlow,itup)

			// print content:
			for (ft::set<int>::iterator itm = myset.begin(); itm != myset.end(); ++itm)
				std::cout << *itm << std::endl;
		}

		{
			std::cout << "key compare check" << std::endl;
			ft::set<int> myset;

			ft::set<int>::key_compare mycomp = myset.key_comp();

			myset['a']=100;
			myset['b']=200;
			myset['c']=300;

			std::cout << "myset contains:" << std::endl;

			char highest = 'c';     // key value of last element

			ft::set<int>::iterator itm = myset.begin();
			do {
				std::cout << *itm << std::endl;
			} while ( mycomp((*itm++), highest) );

			std::cout << std::endl;
		}

		first.insert("g");
		std::cout << "First after insert 'g', size " << first.size() << " : ";
		for (ft::set<std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		first.insert(first.begin(), "s");
		std::cout << "First after insert 's', size " << first.size() << " : ";
		for (ft::set<std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		second["qwerty"] = "qwert";
		second["wsx"] = "wsx";
		second["poi"] = "poi";

		first.insert(second.begin(), second.end());
		std::cout << "First after insert second set, size " << first.size() << " : ";
		for (ft::set<std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		first.erase("a");
		std::cout << "First after erase 'a', size " << first.size() << " : ";
		for (ft::set<std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		first.erase("a");
		std::cout << "First after erase 'a' again, size " << first.size() << " : ";
		for (ft::set<std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		first.erase(first.begin());
		std::cout << "First after erase first elem, size " << first.size() << " : ";
		for (ft::set<std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		first.clear();
		std::cout << "first size after clear: " << first.size() << std::endl;
		std::cout << "is first empty: " << ((first.empty()) ? "yes" : "no");
		std::cout << std::endl;

	}

	return (0);
}
