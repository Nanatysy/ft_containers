//
// Created by Debby Willette on 5/16/22.
//

#ifndef FT_CONTAINERS_SET_HPP
#define FT_CONTAINERS_SET_HPP

#include "compare.hpp"

namespace ft {
	template < class T,  class Compare = std::less<T>, class Alloc = std::allocator<T> >
	class set
	{
	public:
		typedef T key_type;
		typedef T value_type;
		typedef Compare key_compare;
		typedef Compare value_compare;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		// iterators
		typedef typename std::ptrdiff_t difference_type;
		typedef size_t size_type;

		// constructor
		explicit set (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) : _alloc(alloc), _compare(comp), _size(0)
		{
			// todo init tree
		}
		template <class InputIterator>
		set (InputIterator first, typename ft::enable_if<ft::is_iterator <InputIterator>::value, InputIterator>::type last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) : _alloc(alloc), _compare(comp), _size(0)
		{
			// todo init tree
			this->insert(first, last);
		}
		set (const set& x) : _size(0)
		{
			// todo tree init
			*this = x;
		}

		// destructor
		~set()
		{
			// todo delete tree
		}

		set& operator= (const set& x)
		{
			if (this == &x)
				return (*this);
			// delete old tree
			this->_size = x._size;
			this->_compare = x._compare;
			this->_alloc = x._alloc;
			// copy tree
			return (*this);
		}

		// iterators
/*		iterator begin();
		const_iterator begin() const;
		iterator end();
		const_iterator end() const;
		reverse_iterator rbegin();
		const_reverse_iterator rbegin() const;
		reverse_iterator rend();
		const_reverse_iterator rend() const;*/

		// capacity
		bool empty() const
		{
			return (_size == 0);
		}
		size_type size() const
		{
			return (_size);
		}
		size_type max_size() const
		{
			return (_alloc.max_size());
		}

		// modifiers
/*		pair<iterator,bool> insert (const value_type& val);
		iterator insert (iterator position, const value_type& val);
		template <class InputIterator>
		void insert (InputIterator first, InputIterator last);*/
/*		void erase (iterator position);
		size_type erase (const value_type& val);
		void erase (iterator first, iterator last)*/
		void swap (set& x);
		void clear();

		// observers
		key_compare key_comp() const
		{
			return (_compare);
		}
		value_compare value_comp() const
		{
			return (_compare);
		}

		// operations
//		iterator find (const value_type& val) const;
		size_type count (const value_type& val) const;
//		iterator lower_bound (const value_type& val) const;
//		iterator upper_bound (const value_type& val) const;
//		pair<iterator,iterator> equal_range (const value_type& val) const;

		// allocator
		allocator_type get_allocator() const
		{
			return (_alloc);
		}

	private:
		allocator_type	_alloc;
		key_compare		_compare;
		size_type		_size;
		// todo: tree node
	};

	// todo non-member functions

} // ft

#endif //FT_CONTAINERS_SET_HPP
