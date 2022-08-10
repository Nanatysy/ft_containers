//
// Created by Debby Willette on 12/14/21.
//

#include "map.hpp"
#include <vector>
#include <string>
#include <iostream>

int main()
{
	{
		ft::map<std::string, std::string> first;
		std::vector<ft::pair<std::string, std::string> > ref;
		ref.push_back(ft::make_pair("a", "a"));
		ref.push_back(ft::make_pair("b", "b"));
		ref.push_back(ft::make_pair("c", "c"));
		ref.push_back(ft::make_pair("d", "d"));
		ref.push_back(ft::make_pair("ab", "ab"));
		ft::map<std::string, std::string> second(ref.begin(), ref.end());

		std::cout << "First: ";
		for (ft::map<std::string, std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;
		std::cout << "Second: ";
		for (ft::map<std::string, std::string>::iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;

		{
			ft::map<std::string, std::string> third(second);
			std::cout << "Third: ";
			for (ft::map<std::string, std::string>::iterator it = third.begin(); it != third.end(); ++it) {
				std::cout << it->first << "-" << it->second << " ";
			}
			std::cout << std::endl;

			ft::map<std::string, std::string> fourth = third;
			std::cout << "Fourth: ";
			for (ft::map<std::string, std::string>::iterator it = fourth.begin(); it != fourth.end(); ++it) {
				std::cout << it->first << "-" << it->second << " ";
			}
			std::cout << std::endl;
		}
		std::cout << "Second: ";
		for (ft::map<std::string, std::string>::iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;

		std::cout << "second size: " << second.size() << std::endl;
		std::cout << "is second empty: " << ((second.empty()) ? "yes" : "no");
		std::cout << std::endl;


		second["a"] = "z";
		second["z"] = "a";
		std::cout << second.size() << ", second after 2 operator[] : ";
		for (ft::map<std::string, std::string>::iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;

		first.swap(second);
		std::cout << "First after swap with second, size " << first.size() << " : ";
		for (ft::map<std::string, std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;
		std::cout << "Second after swap with first, size " << second.size() << " : ";
		for (ft::map<std::string, std::string>::iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;

		ft::map<std::string, std::string>::iterator itq = first.find("q");
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
			ft::map<char, int> mymap;
			ft::map<char, int>::iterator itlow, itup;

			mymap['a'] = 20;
			mymap['b'] = 40;
			mymap['c'] = 60;
			mymap['d'] = 80;
			mymap['e'] = 100;

			for (ft::map<char, int>::iterator f = mymap.begin(); f != mymap.end(); ++f) {
				std::cout << f->first << "-" << f->second << " ";
			}
			std::cout << std::endl;

			itlow = mymap.lower_bound('b');  // itlow points to b
			itup = mymap.upper_bound('d');   // itup points to e (not d!)

			mymap.erase(itlow,itup);        // erases [itlow,itup)

			// print content:
			for (ft::map<char, int>::iterator itm = mymap.begin(); itm != mymap.end(); ++itm)
				std::cout << itm->first << " => " << itm->second << std::endl;
		}

		{
			std::cout << "key compare check" << std::endl;
			ft::map<char,int> mymap;

			ft::map<char,int>::key_compare mycomp = mymap.key_comp();

			mymap['a']=100;
			mymap['b']=200;
			mymap['c']=300;

			std::cout << "mymap contains:" << std::endl;

			char highest = 'c';     // key value of last element

			ft::map<char,int>::iterator itm = mymap.begin();
			do {
				std::cout << itm->first << " => " << itm->second << std::endl;
			} while ( mycomp((*itm++).first, highest) );

			std::cout << std::endl;
		}

		first.insert(ft::make_pair("g", "g"));
		std::cout << "First after insert 'g', size " << first.size() << " : ";
		for (ft::map<std::string, std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;

		first.insert(first.begin(), ft::make_pair("s", "s"));
		std::cout << "First after insert 's', size " << first.size() << " : ";
		for (ft::map<std::string, std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;

		second["qwerty"] = "qwert";
		second["wsx"] = "wsx";
		second["poi"] = "poi";

		first.insert(second.begin(), second.end());
		std::cout << "First after insert second map, size " << first.size() << " : ";
		for (ft::map<std::string, std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;

		first.erase("a");
		std::cout << "First after erase 'a', size " << first.size() << " : ";
		for (ft::map<std::string, std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;
		first.erase("a");
		std::cout << "First after erase 'a' again, size " << first.size() << " : ";
		for (ft::map<std::string, std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;

		first.erase(first.begin());
		std::cout << "First after erase first elem, size " << first.size() << " : ";
		for (ft::map<std::string, std::string>::iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << it->first << "-" << it->second << " ";
		}
		std::cout << std::endl;

		first.clear();
		std::cout << "first size after clear: " << first.size() << std::endl;
		std::cout << "is first empty: " << ((first.empty()) ? "yes" : "no");
		std::cout << std::endl;

	}

	return (0);
}