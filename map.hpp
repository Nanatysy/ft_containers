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
		typedef ft::pair<const key_type, mapped_type> value_type;
		typedef Compare key_compare;
//		typedef value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename ft::_iterator<pointer> iterator;
		typedef typename ft::_iterator<const_pointer> const_iterator;
		typedef typename ft::_reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::_reverse_iterator<const_iterator>
		const_reverse_iterator;
		typedef typename std::ptrdiff_t difference_type;
		typedef size_t size_type;


		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) :
					  _compare(comp), _alloc(alloc), _size(0), _mem_size(1)
		{
			_map_base = _alloc.allocate(_mem_size);
		}
		template <class InputIterator>
		map (InputIterator first, InputIterator last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type());
		map (const map& x);


	private:
		pointer			_map_base;
		allocator_type	_alloc;
		key_compare		_compare;
		size_type		_size;
		size_type		_mem_size;

	};


}

#endif //FT_CONTAINERS_MAP_HPP
