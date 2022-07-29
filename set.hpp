//
// Created by Nastya on 23.07.2022.
//

#ifndef FT_CONTAINERS_SET_HPP
#define FT_CONTAINERS_SET_HPP

#include "map.hpp"

namespace ft
{
	template < class T, class Compare = std::less<T>, class Alloc =
	std::allocator<ft::pair<const T,T> > >
	class set : public map<T, T> {
	};
}

#endif //FT_CONTAINERS_SET_HPP
