#include <iostream>
#include <sstream>
#include <vector>
#include <list>
#include <queue>
#include <stack>
#include <map>
#include "../vector.hpp"
//#include "../Container/list.hpp"
//#include "../Container/stack.hpp"
//#include "../Container/queue.hpp"
//#include "../Container/map.hpp"
#include "test_color.hpp"


using std::cout;
using std::endl;

template<class T1, class T2>
bool containerEquals(T1 cont1, T2 cont2)
{
	typename T1::const_iterator begin1 = cont1.begin();
	typename T1::const_iterator end1 = cont1.end();
	typename T2::const_iterator begin2 = cont2.begin();
	typename T2::const_iterator end2 = cont2.end();

	for (; begin1 != end1 && begin2 != end2; ++begin1, ++begin2)
	{
		if (*begin1 != *begin2)
		{
			return false;
		}
	}
	if (begin1 == end1 && begin2 == end2)
		return true;
	return false;
}
template<class B1, class E1, class B2, class E2>
bool iteratorEqualsWorkedMap(B1 begin1, E1 end1, B2 begin2, E2 end2)
{
	std::stringstream ft;
	std::stringstream std;
	for (; begin1 != end1 && begin2 != end2; ++begin1, ++begin2)
	{
		if (*begin1 != *begin2)
			return false;
	}
	if (std.str() == ft.str() && (begin1 == end1 && begin2 == end2))
		return true;
	return false;
}

template<class B1, class E1, class B2, class E2>
bool iteratorEqualsWorked(B1 begin1, E1 end1, B2 begin2, E2 end2)
{
	std::stringstream ft;
	std::stringstream std;
	for (; begin1 != end1 && begin2 != end2; ++begin1, ++begin2)
	{
		std << *begin1;
		ft << *begin2;
	}
	if (std.str() == ft.str() && (begin1 == end1 && begin2 == end2))
		return true;
	return false;
}
bool removeIfPred(double a)
{
	return a < 50;
}
bool uniquePred(double a, double b)
{
	return a > b;
}
void vectorTests()
{
	cout << "Constructor test:" << endl;
	{
		std::vector<double> stdVec;
		ft::vector<double> ftVec;
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	{
		std::vector<double> test;
		test.reserve(100);
		for (int i = 0; i < 100; ++i)
			test.push_back(i);
		std::vector<double> stdVec(test.begin(), test.end());
		ft::vector<double> ftVec(test.begin(), test.end());
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	{
		std::vector<double> stdTest;
		ft::vector<double> ftTest;
		stdTest.reserve(100);
		ftTest.reserve(100);
		for (int i = 0; i < 100; ++i)
		{
			stdTest.push_back(i);
			ftTest.push_back(i);
		}
		std::vector<double> stdVec(stdTest);
		ft::vector<double> ftVec(ftTest);
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Operator= test:" << endl;
	{
		std::vector<double> stdTest;
		ft::vector<double> ftTest;
		stdTest.reserve(100);
		ftTest.reserve(100);
		for (int i = 0; i < 100; ++i)
		{
			stdTest.push_back(i);
			ftTest.push_back(i);
		}
		std::vector<double> stdVec;
		ft::vector<double> ftVec;
		stdVec = stdTest;
		ftVec = ftTest;
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Iterator test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		if (iteratorEqualsWorked(stdVec.begin(), stdVec.end(), ftVec.begin(), ftVec.end()))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if (iteratorEqualsWorked(stdVec.rbegin(), stdVec.rend(), ftVec.rbegin(), ftVec.rend()))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if (iteratorEqualsWorked((std::vector<double>::const_iterator) stdVec.begin(), (std::vector<double>::const_iterator) stdVec.end(), (ft::vector<double>::const_iterator) ftVec.begin(), (ft::vector<double>::const_iterator) ftVec.end()))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if (iteratorEqualsWorked((std::vector<double>::const_reverse_iterator) stdVec.rbegin(), (std::vector<double>::const_reverse_iterator) stdVec.rend(), (ft::vector<double>::const_reverse_iterator) ftVec.rbegin(), (ft::vector<double>::const_reverse_iterator) ftVec.rend()))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Size test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		if (ftVec.size() == stdVec.size())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		for (int i = 0; i < 100; ++i)
		{
			ftVec.pop_back();
			stdVec.pop_back();
		}
		if (ftVec.size() == stdVec.size())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Max_size test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		if (ftVec.max_size() == stdVec.max_size())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Resize test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		if (ftVec.size() == stdVec.size())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdVec, ftVec))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
		stdVec.resize(333);
		ftVec.resize(333);
		if (ftVec.size() == stdVec.size())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdVec, ftVec))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
		stdVec.resize(222, 222);
		ftVec.resize(222, 222);
		if (ftVec.size() == stdVec.size())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdVec, ftVec))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Capacity test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		if (ftVec.capacity() == stdVec.capacity())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		for (int i = 0; i < 100; ++i)
		{
			stdVec.push_back(i);
			ftVec.push_back(i);
		}
		if (ftVec.capacity() == stdVec.capacity())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Empty test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		if (ftVec.empty() == stdVec.empty())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		ftVec.resize(0);
		stdVec.resize(0);
		if (ftVec.empty() == stdVec.empty())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Reserve test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(100, 666);
		if (ftVec.capacity() == stdVec.capacity())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		ftVec.reserve(5);
		stdVec.reserve(5);
		if (ftVec.capacity() == stdVec.capacity())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Operator[] test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		std::stringstream ft;
		std::stringstream std;
		for (int i = 0; i < 200; ++i)
		{
			ft << ftVec[i];
			std << stdVec[i];
		}
		if (ft.str() == std.str())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "At test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		std::stringstream ft;
		std::stringstream std;
		for (int i = 0; i < 200; ++i)
		{
			ft << ftVec.at(i);
			std << stdVec.at(i);
		}
		if (ft.str() == std.str())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Front test:" << endl;
	{
		std::vector<double> test;
		test.reserve(100);
		for (int i = 0; i < 100; ++i)
		{
			test.push_back(rand() % 1000);
		}
		ft::vector<double> ftVec(test.begin(), test.end());
		std::vector<double> stdVec(test.begin(), test.end());
		if (ftVec.front() == stdVec.front())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Bask test:" << endl;
	{
		std::vector<double> test;
		test.reserve(100);
		for (int i = 0; i < 100; ++i)
		{
			test.push_back(rand() % 1000);
		}
		ft::vector<double> ftVec(test.begin(), test.end());
		std::vector<double> stdVec(test.begin(), test.end());
		if (ftVec.back() == stdVec.back())
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Assign test:" << endl;
	{
		std::vector<double> test;
		test.reserve(100);
		for (int i = 0; i < 100; ++i)
		{
			test.push_back(rand() % 1000);
		}
		ft::vector<double> ftVec;
		std::vector<double> stdVec;
		ftVec.assign(test.begin(), test.end());
		stdVec.assign(test.begin(), test.end());
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		ftVec.assign(66, 33);
		stdVec.assign(66, 33);
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Push_back test:" << endl;
	{
		ft::vector<double> ftVec;
		std::vector<double> stdVec;
		double num;
		for (int i = 0; i < 100; ++i)
		{
			num = rand() % 1000;
			ftVec.push_back(num);
			stdVec.push_back(num);
		}
//		if (containerEquals(stdVec, ftVec))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Pop_back test:" << endl;
	{
		ft::vector<double> ftVec;
		std::vector<double> stdVec;
		double num;
		for (int i = 0; i < 100; ++i)
		{
			num = rand() % 1000;
			ftVec.push_back(num);
			stdVec.push_back(num);
		}
//		if (containerEquals(stdVec, ftVec))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
		for (int i = 0; i < 22; ++i)
		{
			ftVec.pop_back();
			stdVec.pop_back();
		}
//		if (containerEquals(stdVec, ftVec))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Insert test:" << endl;
	{
		std::vector<double> test;
		test.reserve(100);
		for (int i = 0; i < 100; ++i)
		{
			test.push_back(rand() % 1000);
		}
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		stdVec.insert(stdVec.begin() + 10, 2);
		ftVec.insert(ftVec.begin() + 10, 2);
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		stdVec.insert(stdVec.begin() + 66, 17, 66);
		ftVec.insert(ftVec.begin() + 66, 17, 66);
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		stdVec.insert(stdVec.begin() + 66, test.begin(), test.end());
		ftVec.insert(ftVec.begin() + 66, test.begin(), test.end());
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Erase test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		stdVec.erase(stdVec.begin() + 66);
		ftVec.erase(ftVec.begin() + 66);
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		stdVec.erase(stdVec.begin() + 66, stdVec.begin() + 166);
		ftVec.erase(ftVec.begin() + 66, ftVec.begin() + 166);
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Swap test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		std::vector<double> stdVecCopy;
		ft::vector<double> ftVecCopy;
		stdVec.swap(stdVecCopy);
		ftVec.swap(ftVecCopy);
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if (containerEquals(stdVecCopy, ftVecCopy))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Clear test:" << endl;
	{
		std::vector<double> stdVec(200, 666);
		ft::vector<double> ftVec(200, 666);
		stdVec.clear();
		ftVec.clear();
		if (containerEquals(stdVec, ftVec))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Relational operators test: (Non-member function)" << endl;
	{
		std::vector<double> stdVec1(200, 666);
		ft::vector<double> ftVec1(200, 666);
		std::vector<double> stdVec2(111, 333);
		ft::vector<double> ftVec2(111, 333);

		if ((stdVec1 == stdVec2) == (ftVec1 == ftVec2))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if ((stdVec1 != stdVec2) == (ftVec1 != ftVec2))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if ((stdVec1 < stdVec2) == (ftVec1 < ftVec2))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if ((stdVec1 > stdVec2) == (ftVec1 > ftVec2))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if ((stdVec1 <= stdVec2) == (ftVec1 <= ftVec2))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if ((stdVec1 >= stdVec2) == (ftVec1 >= ftVec2))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
	cout << endl << "Swap test: (Non-member function)" << endl;
	{
		std::vector<double> stdVec1(200, 666);
		ft::vector<double> ftVec1(200, 666);
		std::vector<double> stdVec2(111, 333);
		ft::vector<double> ftVec2(111, 333);
		ft::swap(ftVec1, ftVec2);
		std::swap(stdVec1, stdVec2);
		if (containerEquals(stdVec1, ftVec1))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
		if (containerEquals(stdVec2, ftVec2))
			cout << GREEN << "[OK]" << RESET;
		else
			cout << RED << "[FAIL]" << RESET;
	}
}

//void listTests()
//{
//	cout << "Constructor test:" << endl;
//	{
//		std::list<double> stdList;
//		ft::list<double> ftList;
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	{
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	{
//		std::list<double> test;
//		for (int i = 0; i < 100; ++i)
//			test.push_back(i);
//		std::list<double> stdList(test.begin(), test.end());
//		ft::list<double> ftList(test.begin(), test.end());
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	{
//		std::list<double> stdTest;
//		ft::list<double> ftTest;
//		for (int i = 0; i < 100; ++i)
//		{
//			stdTest.push_back(i);
//			ftTest.push_back(i);
//		}
//		std::list<double> stdList(stdTest);
//		ft::list<double> ftList(ftTest);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Operator= test:" << endl;
//	{
//		std::list<double> stdTest;
//		ft::list<double> ftTest;
//		for (int i = 0; i < 100; ++i)
//		{
//			stdTest.push_back(i);
//			ftTest.push_back(i);
//		}
//		std::list<double> stdList;
//		ft::list<double> ftList;
//		stdList = stdTest;
//		ftList = ftTest;
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Iterator test:" << endl;
//	{
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		if (iteratorEqualsWorked(stdList.begin(), stdList.end(), ftList.begin(), ftList.end()))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (iteratorEqualsWorked(stdList.rbegin(), stdList.rend(), ftList.rbegin(), ftList.rend()))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (iteratorEqualsWorked((std::list<double>::const_iterator) stdList.begin(), (std::list<double>::const_iterator) stdList.end(), (ft::list<double>::const_iterator) ftList.begin(), (ft::list<double>::const_iterator) ftList.end()))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (iteratorEqualsWorked((std::list<double>::const_reverse_iterator) stdList.rbegin(), (std::list<double>::const_reverse_iterator) stdList.rend(), (ft::list<double>::const_reverse_iterator) ftList.rbegin(), (ft::list<double>::const_reverse_iterator) ftList.rend()))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Empty test:" << endl;
//	{
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		if (ftList.empty() == stdList.empty())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		ftList.resize(0);
//		stdList.resize(0);
//		if (ftList.empty() == stdList.empty())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Size test:" << endl;
//	{
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		if (ftList.size() == stdList.size())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		for (int i = 0; i < 100; ++i)
//		{
//			ftList.pop_back();
//			stdList.pop_back();
//		}
//		if (ftList.size() == stdList.size())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Max_size test:" << endl;
//	{
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		if (ftList.max_size() == stdList.max_size())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Front test:" << endl;
//	{
//		std::list<double> test;
//		for (int i = 0; i < 100; ++i)
//		{
//			test.push_back(rand() % 1000);
//		}
//		ft::list<double> ftList(test.begin(), test.end());
//		std::list<double> stdList(test.begin(), test.end());
//		if (ftList.front() == stdList.front())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Bask test:" << endl;
//	{
//		std::list<double> test;
//		for (int i = 0; i < 100; ++i)
//		{
//			test.push_back(rand() % 1000);
//		}
//		ft::list<double> ftList(test.begin(), test.end());
//		std::list<double> stdList(test.begin(), test.end());
//		if (ftList.back() == stdList.back())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Assign test:" << endl;
//	{
//		std::list<double> test;
//		for (int i = 0; i < 100; ++i)
//		{
//			test.push_back(rand() % 1000);
//		}
//		ft::list<double> ftList;
//		std::list<double> stdList;
//		ftList.assign(test.begin(), test.end());
//		stdList.assign(test.begin(), test.end());
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		ftList.assign(66, 33);
//		stdList.assign(66, 33);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Push_back test:" << endl;
//	{
//		ft::list<double> ftList;
//		std::list<double> stdList;
//		double num;
//		for (int i = 0; i < 100; ++i)
//		{
//			num = rand() % 1000;
//			ftList.push_back(num);
//			stdList.push_back(num);
//		}
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Pop_back test:" << endl;
//	{
//		ft::list<double> ftList;
//		std::list<double> stdList;
//		double num;
//		for (int i = 0; i < 100; ++i)
//		{
//			num = rand() % 1000;
//			ftList.push_back(num);
//			stdList.push_back(num);
//		}
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		for (int i = 0; i < 22; ++i)
//		{
//			ftList.pop_back();
//			stdList.pop_back();
//		}
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Push_front test:" << endl;
//	{
//		ft::list<double> ftList;
//		std::list<double> stdList;
//		double num;
//		for (int i = 0; i < 100; ++i)
//		{
//			num = rand() % 1000;
//			ftList.push_front(num);
//			stdList.push_front(num);
//		}
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Pop_front test:" << endl;
//	{
//		ft::list<double> ftList;
//		std::list<double> stdList;
//		double num;
//		for (int i = 0; i < 100; ++i)
//		{
//			num = rand() % 1000;
//			ftList.push_back(num);
//			stdList.push_back(num);
//		}
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		for (int i = 0; i < 22; ++i)
//		{
//			ftList.pop_front();
//			stdList.pop_front();
//		}
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//
//	cout << endl << "Insert test:" << endl;
//	{
//		std::list<double> test;
//		for (int i = 0; i < 100; ++i)
//		{
//			test.push_back(rand() % 1000);
//		}
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		stdList.insert(++ ++ ++ ++ ++ ++stdList.begin(), 2);
//		ftList.insert(++ ++ ++ ++ ++ ++ftList.begin(), 2);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdList.insert(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++stdList.begin(), 17, 66);
//		ftList.insert(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ftList.begin(), 17, 66);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdList.insert(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++stdList.begin(), test.begin(), test.end());
//		ftList.insert(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ftList.begin(), test.begin(), test.end());
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Erase test:" << endl;
//	{
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		stdList.erase(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++stdList.begin());
//		ftList.erase(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ftList.begin());
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdList.erase(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++stdList.begin(), ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++stdList.begin());
//		ftList.erase(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ftList.begin(), ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ftList.begin());
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Swap test:" << endl;
//	{
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		std::list<double> stdListCopy;
//		ft::list<double> ftListCopy;
//		stdList.swap(stdListCopy);
//		ftList.swap(ftListCopy);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdListCopy, ftListCopy))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Resize test:" << endl;
//	{
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		if (ftList.size() == stdList.size())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdList.resize(333);
//		ftList.resize(333);
//		if (ftList.size() == stdList.size())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdList.resize(222, 222);
//		ftList.resize(222, 222);
//		if (ftList.size() == stdList.size())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Clear test:" << endl;
//	{
//		std::list<double> stdList(200, 666);
//		ft::list<double> ftList(200, 666);
//		stdList.clear();
//		ftList.clear();
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Splice test:" << endl;
//	{
//		{
//			std::list<double> stdList(200, 666);
//			ft::list<double> ftList(200, 666);
//			std::list<double> stdListCopy(60, 1111);
//			ft::list<double> ftListCopy(60, 1111);
//			stdList.splice(++ ++ ++ ++ ++stdList.begin(), stdListCopy);
//			ftList.splice(++ ++ ++ ++ ++ftList.begin(), ftListCopy);
//			if (containerEquals(stdList, ftList))
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//		}
//		{
//			std::list<double> stdList(200, 666);
//			ft::list<double> ftList(200, 666);
//			std::list<double> stdListCopy(60, 1111);
//			ft::list<double> ftListCopy(60, 1111);
//			stdList.splice(++ ++ ++ ++ ++stdList.begin(), stdListCopy, ++ ++ ++stdListCopy.begin());
//			ftList.splice(++ ++ ++ ++ ++ftList.begin(), ftListCopy, ++ ++ ++ftListCopy.begin());
//			if (containerEquals(stdListCopy, ftListCopy))
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//		}
//		{
//			std::list<double> stdList(200, 666);
//			ft::list<double> ftList(200, 666);
//			std::list<double> stdListCopy(60, 1111);
//			ft::list<double> ftListCopy(60, 1111);
//			stdList.splice(++ ++ ++ ++ ++stdList.begin(), stdListCopy, ++ ++ ++stdListCopy.begin(), stdListCopy.end());
//			ftList.splice(++ ++ ++ ++ ++ftList.begin(), ftListCopy, ++ ++ ++ftListCopy.begin(), ftListCopy.end());
//			if (containerEquals(stdListCopy, ftListCopy))
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//		}
//	}
//	cout << endl << "Remove test:" << endl;
//	{
//		std::list<double> stdList;
//		ft::list<double> ftList;
//		for (int i = 0; i < 100; ++i)
//		{
//			stdList.push_back(i);
//			ftList.push_back(i);
//		}
//		stdList.remove(66);
//		ftList.remove(66);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Remove if test:" << endl;
//	{
//		std::list<double> stdList;
//		ft::list<double> ftList;
//		for (int i = 0; i < 100; ++i)
//		{
//			stdList.push_back(i);
//			ftList.push_back(i);
//		}
//		stdList.remove_if(removeIfPred);
//		ftList.remove_if(removeIfPred);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Unique test:" << endl;
//	{
//		std::list<double> stdList;
//		ft::list<double> ftList;
//		for (int i = 0; i < 100; ++i)
//		{
//			stdList.push_back(i / 10);
//			ftList.push_back(i / 10);
//		}
//		stdList.unique();
//		ftList.unique();
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		for (int i = 0; i < 100; ++i)
//		{
//			stdList.push_back(i % 20);
//			ftList.push_back(i % 20);
//		}
//		stdList.unique(uniquePred);
//		ftList.unique(uniquePred);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Merge test:" << endl;
//	{
//		std::list<double> stdList;
//		ft::list<double> ftList;
//		std::list<double> stdList1(22, 66);
//		ft::list<double> ftList1(22, 66);
//		for (int i = 0; i < 100; ++i)
//		{
//			stdList.push_back(i / 10);
//			ftList.push_back(i / 10);
//		}
//		stdList.merge(stdList1);
//		ftList.merge(ftList1);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		for (int i = 0; i < 100; ++i)
//		{
//			stdList1.push_back(i % 20);
//			ftList1.push_back(i % 20);
//		}
//		stdList.merge(stdList1, uniquePred);
//		ftList.merge(ftList1, uniquePred);
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//
//
//		cout << endl << "Sort test:" << endl;
//		std::list<double> stdListCopy = stdList;
//		ft::list<double> ftListCopy = ftList;
//		if (containerEquals(stdListCopy, ftListCopy))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdList.sort();
//		ftList.sort();
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdListCopy, ftListCopy))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdListCopy.sort(uniquePred);
//		ftListCopy.sort(uniquePred);
//		if (containerEquals(stdListCopy, ftListCopy))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//
//		cout << endl << "Reverse test:" << endl;
//		stdList.reverse();
//		ftList.reverse();
//		if (containerEquals(stdList, ftList))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Relational operators test: (Non-member function)" << endl;
//	{
//		std::list<double> stdList1(200, 666);
//		ft::list<double> ftList1(200, 666);
//		std::list<double> stdList2(111, 333);
//		ft::list<double> ftList2(111, 333);
//
//		if ((stdList1 == stdList2) == (ftList1 == ftList2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdList1 != stdList2) == (ftList1 != ftList2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdList1 < stdList2) == (ftList1 < ftList2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdList1 > stdList2) == (ftList1 > ftList2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdList1 <= stdList2) == (ftList1 <= ftList2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdList1 >= stdList2) == (ftList1 >= ftList2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Swap test: (Non-member function)" << endl;
//	{
//		std::list<double> stdList1(200, 666);
//		ft::list<double> ftList1(200, 666);
//		std::list<double> stdList2(111, 333);
//		ft::list<double> ftList2(111, 333);
//		ft::swap(ftList1, ftList2);
//		std::swap(stdList1, stdList2);
//		if (containerEquals(stdList1, ftList1))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdList2, ftList2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//}
//
//void queueTest()
//{
//	cout << "Constructor test:" << endl;
//	{
//		{
//			std::queue<double> stdQueue;
//			ft::queue<double> ftQueue;
//			if (stdQueue.size() == ftQueue.size())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//		}
//		{
//			ft::list<double> ftList;
//			std::list<double> stdList;
//			double num;
//			for (int i = 0; i < 100; ++i)
//			{
//				num = rand() % 1000;
//				ftList.push_back(num);
//				stdList.push_back(num);
//			}
//			std::queue<double, std::list<double> > stdQueue(stdList);
//			ft::queue<double, ft::list<double> > ftQueue(ftList);
//			if (stdQueue.size() == ftQueue.size())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//			cout << endl << "Empty test:" << endl;
//			if (stdQueue.empty() == ftQueue.empty())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//			cout << endl << "Size test:" << endl;
//			if (stdQueue.size() == ftQueue.size())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//			cout << endl << "Front test:" << endl;
//			if (stdQueue.front() == ftQueue.front())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//			cout << endl << "Back test:" << endl;
//			if (stdQueue.back() == ftQueue.back())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//			cout << endl << "Push test:" << endl;
//			stdQueue.push(2.22);
//			ftQueue.push(2.22);
//			if (stdQueue.front() == ftQueue.front())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//			if (stdQueue.back() == ftQueue.back())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//			cout << endl << "Pop test:" << endl;
//			stdQueue.pop();
//			ftQueue.pop();
//			if (stdQueue.front() == ftQueue.front())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//			if (stdQueue.back() == ftQueue.back())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//		}
//	}
//	cout << endl << "Relational operators test: (Non-member function)" << endl;
//	{
//		std::list<double> stdList1(200, 666);
//		ft::list<double> ftList1(200, 666);
//		std::list<double> stdList2(111, 333);
//		ft::list<double> ftList2(111, 333);
//		std::queue<double, std::list<double> > stdQueue1(stdList1);
//		ft::queue<double, ft::list<double> > ftQueue1(ftList1);
//		std::queue<double, std::list<double> > stdQueue2(stdList2);
//		ft::queue<double, ft::list<double> > ftQueue2(ftList2);
//
//		if ((stdQueue1 == stdQueue2) == (ftQueue1 == ftQueue2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdQueue1 != stdQueue2) == (ftQueue1 != ftQueue2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdQueue1 < stdQueue2) == (ftQueue1 < ftQueue2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdQueue1 > stdQueue2) == (ftQueue1 > ftQueue2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdQueue1 <= stdQueue2) == (ftQueue1 <= ftQueue2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdQueue1 >= stdQueue2) == (ftQueue1 >= ftQueue2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//}
//
//void stackTest()
//{
//	cout << "Constructor test:" << endl;
//	{
//		{
//			std::stack<double> stdStack;
//			ft::stack<double> ftStack;
//			if (stdStack.size() == ftStack.size())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//		}
//		{
//			ft::list<double> ftList;
//			std::list<double> stdList;
//			double num;
//			for (int i = 0; i < 100; ++i)
//			{
//				num = rand() % 1000;
//				ftList.push_back(num);
//				stdList.push_back(num);
//			}
//			std::stack<double, std::list<double> > stdStack(stdList);
//			ft::stack<double, ft::list<double> > ftStack(ftList);
//			if (stdStack.size() == ftStack.size())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//
//			cout << endl << "Empty test:" << endl;
//			if (stdStack.empty() == ftStack.empty())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//
//			cout << endl << "Size test:" << endl;
//			if (stdStack.size() == ftStack.size())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//
//			cout << endl << "Top test:" << endl;
//			if (stdStack.top() == ftStack.top())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//
//			cout << endl << "Push test:" << endl;
//			stdStack.push(2.22);
//			ftStack.push(2.22);
//			if (stdStack.top() == ftStack.top())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//
//			cout << endl << "Pop test:" << endl;
//			stdStack.pop();
//			ftStack.pop();
//			if (stdStack.top() == ftStack.top())
//				cout << GREEN << "[OK]" << RESET;
//			else
//				cout << RED << "[FAIL]" << RESET;
//		}
//	}
//	cout << endl << "Relational operators test: (Non-member function)" << endl;
//	{
//		std::list<double> stdList1(200, 666);
//		ft::list<double> ftList1(200, 666);
//		std::list<double> stdList2(111, 333);
//		ft::list<double> ftList2(111, 333);
//		std::stack<double, std::list<double> > stdStack1(stdList1);
//		ft::stack<double, ft::list<double> > ftStack1(ftList1);
//		std::stack<double, std::list<double> > stdStack2(stdList2);
//		ft::stack<double, ft::list<double> > ftStack2(ftList2);
//
//		if ((stdStack1 == stdStack2) == (ftStack1 == ftStack2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdStack1 != stdStack2) == (ftStack1 != ftStack2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdStack1 < stdStack2) == (ftStack1 < ftStack2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdStack1 > stdStack2) == (ftStack1 > ftStack2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdStack1 <= stdStack2) == (ftStack1 <= ftStack2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdStack1 >= stdStack2) == (ftStack1 >= ftStack2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//}

//void mapTest()
//{
//	cout << "Constructor test:" << endl;
//	{
//		std::map<double, double> stdMap;
//		ft::map<double, double> ftMap;
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	{
//		std::map<double, double> test;
//		for (int i = 0; i < 100; ++i)
//			test.insert(std::pair<double, double>(i, i * 6));
//		std::map<double, double> stdMap(test.begin(), test.end());
//		ft::map<double, double> ftMap(test.begin(), test.end());
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	{
//		std::map<double, double> stdTest;
//		ft::map<double, double> ftTest;
//		for (int i = 0; i < 100; ++i)
//		{
//			stdTest.insert(std::pair<double, double>(i, i * 6));
//			ftTest.insert(std::pair<double, double>(i, i * 6));
//		}
//		std::map<double, double> stdMap(stdTest);
//		ft::map<double, double> ftMap(ftTest);
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Operator= test:" << endl;
//	{
//		std::map<double, double> stdTest;
//		ft::map<double, double> ftTest;
//		for (int i = 0; i < 100; ++i)
//		{
//			stdTest.insert(std::pair<double, double>(i, i * 6));
//			ftTest.insert(std::pair<double, double>(i, i * 6));
//		}
//		std::map<double, double> stdMap;
//		ft::map<double, double> ftMap;
//		stdMap = stdTest;
//		ftMap = ftTest;
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Iterator test:" << endl;
//	{
//		std::map<double, double> stdMap;
//		ft::map<double, double> ftMap;
//		double value;
//		for (int i = 0; i < 20; ++i)
//		{
//			value = rand() % 100;
//			stdMap.insert(std::pair<double, double>(value, i * 6));
//			ftMap.insert(std::pair<double, double>(value, i * 6));
//		}
//		if (iteratorEqualsWorkedMap(stdMap.begin(), stdMap.end(), ftMap.begin(), ftMap.end()))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (iteratorEqualsWorkedMap(stdMap.rbegin(), stdMap.rend(), ftMap.rbegin(), ftMap.rend()))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (iteratorEqualsWorkedMap((std::map<double, double>::const_iterator) stdMap.begin(), (std::map<double, double>::const_iterator) stdMap.end(), (ft::map<double, double>::const_iterator) ftMap.begin(), (ft::map<double, double>::const_iterator) ftMap.end()))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (iteratorEqualsWorkedMap((std::map<double, double>::const_reverse_iterator) stdMap.rbegin(), (std::map<double, double>::const_reverse_iterator) stdMap.rend(), (ft::map<double, double>::const_reverse_iterator) ftMap.rbegin(), (ft::map<double, double>::const_reverse_iterator) ftMap.rend()))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Size test:" << endl;
//	{
//		std::map<double, double> test;
//		for (int i = 0; i < 100; ++i)
//			test.insert(std::pair<double, double>(i, i * 6));
//		std::map<double, double> stdMap(test.begin(), test.end());
//		ft::map<double, double> ftMap(test.begin(), test.end());
//		if (ftMap.size() == stdMap.size())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Max_size test:" << endl;
//	{
//		std::map<double, double> test;
//		for (int i = 0; i < 100; ++i)
//			test.insert(std::pair<double, double>(i, i * 6));
//		std::map<double, double> stdMap(test.begin(), test.end());
//		ft::map<double, double> ftMap(test.begin(), test.end());
//		cout << GREEN << "std: " << stdMap.max_size() << YELLOW << " | ft: " << ftMap.max_size() << RESET << endl;
//	}
//	cout << "Operator[] test:" << endl;
//	{
//		std::map<double, double> test;
//		for (int i = 0; i < 100; ++i)
//			test.insert(std::pair<double, double>(i, i * 6));
//		std::map<double, double> stdMap(test.begin(), test.end());
//		ft::map<double, double> ftMap(test.begin(), test.end());
//		std::stringstream ft;
//		std::stringstream std;
//		for (int i = 0; i < 200; ++i)
//		{
//			ft << stdMap[i];
//			std << stdMap[i];
//		}
//		if (ft.str() == std.str())
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Insert test:" << endl;
//	{
//		std::map<double, double> test;
//		for (int i = 0; i < 100; ++i)
//			test.insert(std::pair<double, double>(i, i * 6));
//		std::map<double, double> stdMap(test.begin(), test.end());
//		ft::map<double, double> ftMap(test.begin(), test.end());
//		stdMap.insert(std::pair<double, double>(66, 99));
//		ftMap.insert(std::pair<double, double>(66, 99));
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdMap.insert(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++stdMap.begin(), std::pair<double, double>(66, 99));
//		ftMap.insert(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ftMap.begin(), std::pair<double, double>(66, 99));
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdMap.insert(test.begin(), test.end());
//		ftMap.insert(test.begin(), test.end());
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Erase test:" << endl;
//	{
//		std::list<double> stdMap(200, 666);
//		ft::list<double> ftMap(200, 666);
//		stdMap.erase(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++stdMap.begin());
//		ftMap.erase(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ftMap.begin());
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		stdMap.erase(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++stdMap.begin(), ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++stdMap.begin());
//		ftMap.erase(++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ftMap.begin(), ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ ++ftMap.begin());
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Swap test:" << endl;
//	{
//		std::list<double> stdMap(200, 666);
//		ft::list<double> ftMap(200, 666);
//		std::list<double> stdMapCopy;
//		ft::list<double> ftMapCopy;
//		stdMap.swap(stdMapCopy);
//		ftMap.swap(ftMapCopy);
//		if (containerEquals(stdMap, ftMap))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(stdMapCopy, ftMapCopy))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		cout << endl << "Clear test:" << endl;
//		stdMapCopy.clear();
//		ftMapCopy.clear();
//		if (containerEquals(stdMapCopy, ftMapCopy))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Key_comp test:" << endl;
//	{
//		std::map<double, double> test;
//		for (int i = 0; i < 100; ++i)
//			test.insert(std::pair<double, double>(i, i * 6));
//		std::map<double, double> stdMap(test.begin(), test.end());
//		ft::map<double, double> ftMap(test.begin(), test.end());
//		std::map<double, double>::key_compare first = stdMap.key_comp();
//		ft::map<double, double>::key_compare second = ftMap.key_comp();
//		if (first(22, 44) == second(22, 44))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Value_comp test:" << endl;
//	{
//		std::map<double, double> test;
//		for (int i = 0; i < 100; ++i)
//			test.insert(std::pair<double, double>(i, i * 6));
//		std::map<double, double> stdMap(test.begin(), test.end());
//		ft::map<double, double> ftMap(test.begin(), test.end());
//		if (stdMap.key_comp()(22, 44) == ftMap.key_comp()(22, 44))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Find test:" << endl;
//	{
//		std::map<double, double> stdMap;
//		ft::map<double, double> ftMap;
//		double value;
//		for (int i = 0; i < 20; ++i)
//		{
//			value = rand() % 100;
//			stdMap.insert(std::pair<double, double>(value, i * 6));
//			ftMap.insert(std::pair<double, double>(value, i * 6));
//		}
//		if (*(stdMap.find((++ ++ ++ ++ ++ ++stdMap.begin())->first)) == *(ftMap.find((++ ++ ++ ++ ++ ++stdMap.begin())->first)))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Count test:" << endl;
//	{
//		std::map<double, double> stdMap;
//		ft::map<double, double> ftMap;
//		double value;
//		for (int i = 0; i < 20; ++i)
//		{
//			value = rand() % 100;
//			stdMap.insert(std::pair<double, double>(value, i * 6));
//			ftMap.insert(std::pair<double, double>(value, i * 6));
//		}
//		if (stdMap.count((++ ++ ++ ++ ++ ++stdMap.begin())->first) == ftMap.count((++ ++ ++ ++ ++ ++stdMap.begin())->first))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Lower_bound test:" << endl;
//	{
//		std::map<double, double> stdMap;
//		ft::map<double, double> ftMap;
//		double value;
//		for (int i = 0; i < 20; ++i)
//		{
//			value = rand() % 100;
//			stdMap.insert(std::pair<double, double>(value, i * 6));
//			ftMap.insert(std::pair<double, double>(value, i * 6));
//		}
//		if (*(stdMap.lower_bound((++ ++ ++ ++ ++ ++stdMap.begin())->first)) ==
//		    *(ftMap.lower_bound((++ ++ ++ ++ ++ ++stdMap.begin())->first)))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Upper_bound test:" << endl;
//	{
//		std::map<double, double> stdMap;
//		ft::map<double, double> ftMap;
//		double value;
//		for (int i = 0; i < 20; ++i)
//		{
//			value = rand() % 100;
//			stdMap.insert(std::pair<double, double>(value, i * 6));
//			ftMap.insert(std::pair<double, double>(value, i * 6));
//		}
//		if (*(stdMap.upper_bound((++ ++ ++ ++ ++ ++stdMap.begin())->first)) ==
//		    *(ftMap.upper_bound((++ ++ ++ ++ ++ ++stdMap.begin())->first)))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Equal_range test:" << endl;
//	{
//		std::map<double, double> stdMap;
//		ft::map<double, double> ftMap;
//		double value;
//		for (int i = 0; i < 20; ++i)
//		{
//			value = rand() % 100;
//			stdMap.insert(std::pair<double, double>(value, i * 6));
//			ftMap.insert(std::pair<double, double>(value, i * 6));
//		}
//		std::pair<std::map<double, double>::iterator, std::map<double, double>::iterator> first = stdMap.equal_range((++ ++ ++ ++ ++ ++stdMap.begin())->first);
//		std::pair<ft::map<double, double>::iterator, ft::map<double, double>::iterator> second = ftMap.equal_range((++ ++ ++ ++ ++ ++stdMap.begin())->first);
//		if (iteratorEqualsWorkedMap(first.first, first.second, second.first, second.second))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Relational operators test: (Non-member function)" << endl;
//	{
//		std::map<double, double> stdMap1;
//		ft::map<double, double> ftMap1;
//		std::map<double, double> stdMap2;
//		ft::map<double, double> ftMap2;
//		double value;
//		for (int i = 0; i < 20; ++i)
//		{
//			value = rand() % 100;
//			stdMap1.insert(std::pair<double, double>(value, i * 6));
//			ftMap1.insert(std::pair<double, double>(value, i * 6));
//			value = rand() % 100;
//			stdMap2.insert(std::pair<double, double>(value, i * 33));
//			ftMap2.insert(std::pair<double, double>(value, i * 33));
//		}
//
//		if ((stdMap1 == stdMap2) == (ftMap1 == ftMap2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdMap1 != stdMap2) == (ftMap1 != ftMap2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdMap1 < stdMap2) == (ftMap1 < ftMap2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdMap1 > stdMap2) == (ftMap1 > ftMap2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdMap1 <= stdMap2) == (ftMap1 <= ftMap2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if ((stdMap1 >= stdMap2) == (ftMap1 >= ftMap2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//	cout << endl << "Swap test: (Non-member function)" << endl;
//	{
//		std::map<double, double> stdMap1;
//		ft::map<double, double> ftMap1;
//		std::map<double, double> stdMap2;
//		ft::map<double, double> ftMap2;
//		double value;
//		for (int i = 0; i < 20; ++i)
//		{
//			value = rand() % 100;
//			stdMap1.insert(std::pair<double, double>(value, i * 6));
//			ftMap1.insert(std::pair<double, double>(value, i * 6));
//			value = rand() % 100;
//			stdMap2.insert(std::pair<double, double>(value, i * 33));
//			ftMap2.insert(std::pair<double, double>(value, i * 33));
//		}
//		ft::swap(ftMap1, ftMap2);
//		std::swap(stdMap1, stdMap2);
//		if (containerEquals(ftMap1, stdMap1))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//		if (containerEquals(ftMap2, stdMap2))
//			cout << GREEN << "[OK]" << RESET;
//		else
//			cout << RED << "[FAIL]" << RESET;
//	}
//}

int main()
{
	srand(time(nullptr));
	cout << BLUE << "=======VECTOR=======" << RESET << endl;
	vectorTests();
//	cout << endl << BLUE << "========LIST========" << RESET << endl;
//	listTests();
//	cout << endl << BLUE << "=======QUEUE========" << RESET << endl;
//	stackTest();
//	cout << endl << BLUE << "=======STACK========" << RESET << endl;
//	stackTest();
//	cout << endl << BLUE << "========MAP=========" << RESET << endl;
//	mapTest();
	return 0;
}