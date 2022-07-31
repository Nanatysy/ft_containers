#include <iostream>

#include <vector>
#include "vector.hpp"

#define RED "\x1b[31m"
#define GREEN "\x1b[32m"
#define YELLOW "\x1b[33m"
#define CIAN "\x1b[36m"
#define BLANK "\x1b[0m"

int main()
{
    {
        std::cout << YELLOW << "Int vector tests" << BLANK << std::endl;

        std::vector<int> v_i;

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

        std::vector<std::string> v_s;

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
        for (std::vector<std::string>::iterator it = v_s.begin(); it != v_s.end(); ++it)
        {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        std::cout << "using " << CIAN << "`reverse iterator`" << BLANK<< " to print elements" << std::endl;
        for (std::vector<std::string>::reverse_iterator it = v_s.rbegin(); it != v_s.rend(); ++it)
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
        std::vector<int> foo;
        std::vector<int> bar;

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

    {
        std::cout << "----------------------------------" << std::endl;

        std::vector<std::string> first;
        std::vector<std::string> second(5, "hi");
        std::vector<std::string> third(second.begin(), second.end());

        std::cout << "First: ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        std::cout << "Second: ";
        for (std::vector<std::string>::const_iterator it = second.begin(); it != second.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        std::cout << "Third: ";
        for (std::vector<std::string>::const_iterator it = third.begin(); it != third.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        {
            std::cout << "Fourth: ";
            std::vector<std::string> fourth(second);
            for (std::vector<std::string>::const_iterator it = fourth.begin(); it != fourth.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
        {
            std::cout << "Fifth: ";
            std::vector<std::string> fifth = second;
            for (std::vector<std::string>::const_iterator it = fifth.begin(); it != fifth.end(); ++it) {
                std::cout << *it << " ";
            }
            std::cout << std::endl;
        }
        std::cout << "second size: " << second.size() << std::endl;

        std::cout << "second max_size: " << second.max_size() << std::endl;

        first.resize(2, "hello");

        std::cout << first.size() << ", first after resize : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

//        std::cout << "first capacity: " << first.capacity() << std::endl;

        first.reserve(10);
        std::cout << "first capacity after reserve: " << first.capacity() << std::endl;

        first[1] = "peer";
        std::cout << first.size() << ", first after operator[] : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        try {
            std::cout << first.at(5) << " - element at 5th position" <<std::endl;
        }
        catch (std::exception& e) {
            std::cout << "Expected exception" << std::endl;
        }

        first.swap(second);
        std::cout << "First after swap with second, size " << first.size() << " : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        std::cout << "Second after swap with first, size " << second.size() << " : ";
        for (std::vector<std::string>::const_iterator it = second.begin(); it != second.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        first.clear();
        std::cout << "first size after clear method: " << first.size() << std::endl;
        std::cout << ((first.empty()) ? "empty" : "not empty") << std::endl;

        first.insert(first.begin(), "hello");
        std::cout << "First after first insert, size " << first.size() << " : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        first.insert(first.begin(), 3, ".");
        std::cout << "First after second insert, size " << first.size() << " : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        first.insert(first.end() - 1, second.begin(), second.end());
        std::cout << "First after third insert, size " << first.size() << " : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        first.erase(first.end() - 1);
        std::cout << "First after erase of last element, size " << first.size() << " : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        first.erase(first.begin() + 1, first.end());
        std::cout << "First after erase of all elems beside first, size " << first.size() << " : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;

        first.assign(3, ")");
        std::cout << "First after assign, size " << first.size() << " : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
        first.assign(third.begin(), third.end());
        std::cout << "First after second assign, size " << first.size() << " : ";
        for (std::vector<std::string>::const_iterator it = first.begin(); it != first.end(); ++it) {
            std::cout << *it << " ";
        }
        std::cout << std::endl;
    }


	{
		std::vector<int> first(3, 5);
		std::vector<int> second(first.begin(), first.end());
		std::vector<int> third;
		for (int i = 0; i < 5; ++i) {
			third.push_back(i + 1);
		}

		std::cout << "First: ";
		for (std::vector<int>::const_iterator it = first.begin(); it != first.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Second: ";
		for (std::vector<int>::const_iterator it = second.begin(); it != second.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;
		std::cout << "Third: ";
		for (std::vector<int>::const_iterator it = third.begin(); it != third.end(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::cout << "Third vector output using const reverse iterator: ";
		for (std::vector<int>::const_reverse_iterator it = third.rbegin(); it != third.rend(); ++it) {
			std::cout << *it << " ";
		}
		std::cout << std::endl;

		std::vector<int>::iterator middle = std::find(third.begin(), third.end(), 3);
		if (middle != first.end()) {
			third.insert(middle, third.begin(), third.end());
			std::cout << "Third after inserting third in the middle: ";
			for (std::vector<int>::iterator it = third.begin(); it != third.end(); ++it) {
				std::cout << *it << " ";
			}
			std::cout << std::endl;
		} else {
			std::cout << "failed to find middle element" << std::endl;
		}

		middle = std::find(third.begin(), third.end(), 3);
		if (middle == first.end()) {
			std::cout << "failed to find middle element" << std::endl;
		} else {
			std::cout << *middle-- << " " << *middle << " " << *(--middle) << std::endl;
			middle += 2;
			std::cout << *middle++ << " " << *middle << " " << *(++middle) << std::endl;
			std::cout << *(middle - 1) << std::endl;
		}

	}

    return (0);
}