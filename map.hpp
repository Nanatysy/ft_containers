//
// Created by Debby Willette on 10/26/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

namespace ft
{

	template < class Key, class T, class Compare = less<Key>, class Alloc =
			allocator<pair<const Key,T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
//		typedef pair<<const key_type, mapped_type> value_type;
//		typedef key_compare;
//		typedef value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
//		typedef iterator;
//		typedef const_iterator;
//		typedef reverse_iterator;
//		typedef const_reverse_iterator;
//		typedef difference_type;
//		typedef size_type;


		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type());
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type());
		map (const map& x);


	private:

	};


}

#endif //FT_CONTAINERS_MAP_HPP
