//
// Created by Debby Willette on 12/14/21.
//

#include "map.hpp"
#include <map>

typedef int maped_type;

int main()
{
	ft::map<int, maped_type> first;
//	first.print_tree();


	ft::map<int, maped_type>::iterator it = first.begin();
	ft::map<int, maped_type>::iterator ite = first.end();

	while (it != ite)
	{
		std::cout << it->second << " ";
		++it;
	}
	std::cout << std::endl;


	std::cout << std::endl << "---------------------" << std::endl;


	std::vector<ft::pair<int, maped_type> > ref;
	for (int i = 1; i < 11; i++)
	{
		ref.push_back(ft::make_pair(i, i));
		ref.push_back(ft::make_pair(50 + i, 50 + i));
	}
	ft::map<int, maped_type> second(ref.begin(), ref.end());

	std::cout << std::endl << "---------------------" << std::endl;

	second.print_tree();
	std::cout << std::endl;

	ft::map<int, maped_type>::iterator it2 = second.begin();
	ft::map<int, maped_type>::iterator ite2 = second.end();
	while(it2 != ite2)
	{
		std::cout << it2->second << " ";
		it2++;
	}
	std::cout << std::endl;

	std::cout << std::endl << "----------&----------" << std::endl;

//	ft::map<int, int>::iterator td = second.find(10);
	second.erase(51);

	second.print_tree();
	std::cout << std::endl;

	it2 = second.begin();
	ite2 = second.end();
	while(it2 != ite2)
	{
		std::cout << it2->second << " ";
		it2++;
	}
	std::cout << std::endl;

//	it2 = second.begin();
//	while(it2 != second.end())
//	{
//		std::cout << it2->second << " ";
//		it2++;
//	}
//	std::cout << std::endl;


//	ft::map<int, int> second;
//	second = first;
//	second.print_tree();
//
//	ft::map<int, int>::value_type
//
//
//	std::map
//	ft::map<int, int> second(first);
//	second.print_tree();

	{
		ft::map<char,int> mymap;
		ft::map<char,int>::const_iterator itlow,itup;

		mymap['a']=20;
		mymap['b']=40;
		mymap['c']=60;
		mymap['d']=80;
		mymap['e']=100;

		for (ft::map<char,int>::iterator f = mymap.begin(); f != mymap.end(); ++f) {
			std::cout << f->first << "-" << f->second << " ";
		}
		std::cout << std::endl;

		itlow=mymap.lower_bound ('b');  // itlow points to b
		itup=mymap.upper_bound ('d');   // itup points to e (not d!)

//		mymap.erase(itlow,itup);        // erases [itlow,itup)

		// print content:
		for (ft::map<char,int>::const_iterator itm=mymap.begin(); itm!=mymap.end(); ++itm)
			std::cout << " => "  << '\n';
	}
	return (0);
}