//
// Created by Debby Willette on 10/26/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#define RED 1
#define BLACK 2
#define LEFT true
#define RIGHT false

#include "pair.hpp"
#include "enable_if.hpp"
#include "iterator.hpp"
#include "vector.hpp"
#include <queue>

// TODO: reverse_iterator, cbegin, cend, lower_bound, upper_bound (with const iterator), const iterator

namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc =
			std::allocator<ft::pair<const Key,T> > >
	class map
	{
	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::value_type value_type;
		typedef Compare key_compare;

	private:
		typedef struct	s_node
		{
			typedef value_type value;

			struct s_node	*left;
			struct s_node	*right;
			struct s_node	*parent;
			int				color;
			value_type		val;
		}				t_node;

	private:
		template <class Iter>
		class _map_const_iterator;


		template <class Iter>
		class _map_iterator
		{
		friend class _map_const_iterator<Iter>;

		public:
			typedef Iter iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type::value value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer pointer;
			typedef typename ft::iterator_traits<Iter>::reference reference;

			_map_iterator() : _ptr(nullptr), _tree(nullptr) {}
			explicit _map_iterator(Iter data, const map<Key, T> *x) : _ptr(data), _tree(x) {}
			_map_iterator(const _map_iterator & src)
			{
				*this = src;
			}
//			_map_iterator(_map_iterator<t_node *> iterator) {
//				_ptr = iterator._ptr;
//				_tree = iterator._tree;
//			}

			_map_iterator &operator=(const _map_iterator & src)
			{
				if (this == &src)
					return (*this);

				_ptr = src._ptr;
				_tree = src._tree;
				return (*this);
			}

			bool operator==(const _map_iterator & src)
			{
				return (this->_ptr == src._ptr);
			}
			bool operator!=(const _map_iterator & src)
			{
				return (this->_ptr != src._ptr);
			}

			_map_iterator<Iter> &operator++()
			{
				pointer parent;

				if (_ptr == _tree->_end)
					return (*this);
				if (_ptr->right == _tree->_leaf || _ptr->right == _tree->_begin)
				{
					parent = _ptr->parent;
					while (parent && parent->right == _ptr)
					{
						_ptr = parent;
						parent = parent->parent;
					}
					_ptr = parent;
				}
				else
				{
					_ptr = _ptr->right;
					while (_ptr != _tree->_end && _ptr->left != _tree->_leaf)
						_ptr = _ptr->left;
				}
				return (*this);
			}

			_map_iterator<Iter> operator++(int)
			{
				_map_iterator<Iter> tmp(*this);

				++(*this);
				return (tmp);
			}

			_map_iterator<Iter> &operator--()
			{
				pointer parent;

				if (_ptr == _tree->_end)
					return (*this);
				if (_ptr->left == _tree->_leaf || _ptr->left == _tree->_enf)
				{
					parent = _ptr->parent;
					while (parent && parent->left == _ptr)
					{
						_ptr = parent;
						parent = parent->parent;
					}
					_ptr = parent;
				}
				else
				{
					_ptr = _ptr->left;
					while (_ptr != _tree->_begin && _ptr->left != _tree->_leaf)
						_ptr = _ptr->left;
				}
				return (*this);
			}

			_map_iterator<Iter> operator--(int)
			{
				_map_iterator<Iter> tmp(*this);

				--(*this);
				return (tmp);
			}

			value_type &operator*() const
			{
				return (_ptr->val);
			}
			value_type *operator->() const
			{
				return (&_ptr->val);
			}

		private:
			iterator_type		_ptr;
			const map<Key, T>	*_tree;
		};

		template <class Iter>
		class _map_const_iterator
		{
		public:
			typedef Iter iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type::value value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer pointer;
			typedef typename ft::iterator_traits<Iter>::reference reference;

			_map_const_iterator() : _ptr(nullptr), _tree(nullptr) {}
			explicit _map_const_iterator(Iter data, const map<Key, T> *x) : _ptr(data), _tree(x) {}
			_map_const_iterator(const _map_const_iterator & src)
			{
				*this = src;
			}
			_map_const_iterator(const _map_iterator<Iter>& src) {
				_ptr = src._ptr;
				_tree = src._tree;
			}

			_map_const_iterator &operator=(const _map_const_iterator & src)
			{
				if (this == &src)
					return (*this);

				_ptr = src._ptr;
				_tree = src._tree;
				return (*this);
			}

			_map_const_iterator &operator=(const _map_iterator<Iter> & src) {
				_ptr = src._ptr;
				_tree = src._tree;
				return (*this);
			}

			bool operator==(const _map_const_iterator & src)
			{
				return (this->_ptr == src._ptr);
			}
			bool operator!=(const _map_const_iterator & src)
			{
				return (this->_ptr != src._ptr);
			}

			_map_const_iterator<Iter> &operator++()
			{
				pointer parent;

				if (_ptr == _tree->_end)
					return (*this);
				if (_ptr->right == _tree->_leaf || _ptr->right == _tree->_begin)
				{
					parent = _ptr->parent;
					while (parent && parent->right == _ptr)
					{
						_ptr = parent;
						parent = parent->parent;
					}
					_ptr = parent;
				}
				else
				{
					_ptr = _ptr->right;
					while (_ptr != _tree->_end && _ptr->left != _tree->_leaf)
						_ptr = _ptr->left;
				}
				return (*this);
			}

			_map_const_iterator<Iter> operator++(int)
			{
				_map_const_iterator<Iter> tmp(*this);

				++(*this);
				return (tmp);
			}

			_map_const_iterator<Iter> &operator--()
			{
				pointer parent;

				if (_ptr == _tree->_end)
					return (*this);
				if (_ptr->left == _tree->_leaf || _ptr->left == _tree->_enf)
				{
					parent = _ptr->parent;
					while (parent && parent->left == _ptr)
					{
						_ptr = parent;
						parent = parent->parent;
					}
					_ptr = parent;
				}
				else
				{
					_ptr = _ptr->left;
					while (_ptr != _tree->_begin && _ptr->left != _tree->_leaf)
						_ptr = _ptr->left;
				}
				return (*this);
			}

			_map_const_iterator<Iter> operator--(int)
			{
				_map_const_iterator<Iter> tmp(*this);

				--(*this);
				return (tmp);
			}

			value_type &operator*() const
			{
				return (_ptr->val);
			}
			value_type *operator->() const
			{
				return (&_ptr->val);
			}

		private:
			iterator_type		_ptr;
			const map<Key, T>	*_tree;
		};

		template <class Iter>
		class _map_reverse_iterator {
		public:
			typedef Iter iterator_type;
			typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
			typedef typename ft::iterator_traits<Iter>::value_type::value value_type;
			typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
			typedef typename ft::iterator_traits<Iter>::pointer pointer;
			typedef typename ft::iterator_traits<Iter>::reference reference;

			_map_reverse_iterator() : _ptr(nullptr), _tree(nullptr) {}
			explicit _map_reverse_iterator (iterator_type it, const map<Key, T> *x) : _ptr(it), _tree(x) {}
			_map_reverse_iterator (const _map_reverse_iterator<Iter>& rev_it) {
				*this = rev_it;
			}

			_map_reverse_iterator &operator=(const _map_reverse_iterator & src)
			{
				if (this == &src)
					return (*this);

				_ptr = src._ptr;
				_tree = src._tree;
				return (*this);
			}

			bool operator==(const _map_reverse_iterator & src)
			{
				return (this->_ptr == src._ptr);
			}
			bool operator!=(const _map_reverse_iterator & src)
			{
				return (this->_ptr != src._ptr);
			}

			_map_reverse_iterator<Iter> operator++()
			{
				this->ptr--;
				return(this);
			}
			_map_reverse_iterator<Iter> operator++(int)
			{
				_map_reverse_iterator<Iter> tmp(*this);

				++(*this);
				return (tmp);
			}
			_map_reverse_iterator<Iter> operator--()
			{
				this->ptr++;
				return(this);
			}
			_map_reverse_iterator<Iter> operator--(int)
			{
				_map_reverse_iterator<Iter> tmp(*this);

				++(*this);
				return (tmp);
			}
			value_type &operator*() const
			{
				return (_ptr->val);
			}
			value_type *operator->() const
			{
				return (&_ptr->val);
			}

		private:
			iterator_type		_ptr;
			const map<Key, T>	*_tree;
		};

	public:
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename std::ptrdiff_t difference_type;
		typedef size_t size_type;

	private:
		class _value_compare : public  std::binary_function<value_type,value_type,bool>
		{
		protected:
			key_compare comp;
			_value_compare (key_compare c) : comp(c) {}
		public:
			bool operator() (const value_type& x, const value_type& y) const
			{
				return comp(x.first, y.first);
			}
		};

	public:
		typedef _map_iterator<t_node *> iterator;
		typedef _map_const_iterator<const t_node *> const_iterator;
		typedef typename ft::_reverse_iterator<iterator> reverse_iterator;
		typedef typename ft::_reverse_iterator<const_iterator> const_reverse_iterator;
		typedef _value_compare value_compare;


		explicit map (const key_compare& comp = key_compare(),
					  const allocator_type& alloc = allocator_type()) :
					  _alloc(alloc), _compare(comp), _size(0)
		{
			_leaf = _new_node();
			_begin = _new_node();
			_end = _new_node();
			_root = _leaf;
			_root->parent = _leaf;
		}
		template <class InputIterator>
		map (InputIterator first, typename ft::enable_if<ft::is_iterator <InputIterator>::value, InputIterator>::type last,
			 const key_compare& comp = key_compare(),
			 const allocator_type& alloc = allocator_type()) : _alloc(alloc), _compare(comp), _size(0)
		{
			_leaf = _new_node();
			_begin = _new_node();
			_end = _new_node();
			_root = _leaf;
			_root->parent = _leaf;

			this->insert(first, last);
		}
		map (const map<Key, T> & x) : _size(0)
		{
			_leaf = _new_node();
			_begin = _new_node();
			_end = _new_node();
			_root = _leaf;
			_root->parent = _leaf;
			*this = x;
		}

		map & operator= (const map<Key, T> & x)
		{
			if (this == &x)
				return (*this);

			_delete_tree(_root);
			delete _leaf;
			delete _begin;
			delete _end;
			this->_size = x._size;
			this->_compare = x._compare;
			this->_alloc = x._alloc;
			_leaf = _new_node();
			_begin = _new_node();
			_end = _new_node();
			_root = _new_node(*x._root, x);
			_root->parent = _leaf;
			return (*this);
		}

		virtual ~map()
		{
			_delete_tree(_root);
			delete _leaf;
			delete _begin;
			delete _end;
		}

//		iterator
		iterator begin()
		{
			if (_size == 0)
				return (iterator(_end, this));
			return (iterator(_begin->parent, this));
		}
		// todo
		const_iterator begin() const
		{
			if (_size == 0)
				return (iterator(_end, this));
			return (iterator(_begin->parent, this));
		}
		reverse_iterator rbegin()
		{
			iterator it = end();
			return (reverse_iterator(--it));
		}
		const_reverse_iterator rbegin() const
		{
			const_iterator it = end();
			return (const_reverse_iterator (--it));
		}
		iterator end()
		{
			return (iterator(_end, this));
		}
		// todo
		const_iterator end() const
		{
			return (iterator(_end, this));
		}
		reverse_iterator rend()
		{
			iterator it = begin();
			return (reverse_iterator(--it));
		}
		const_reverse_iterator rend() const
		{
			const_iterator it = begin();
			return (const_reverse_iterator(--it));
		}

//		capacity
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

//		Element access
		mapped_type& operator[] (const key_type& k)
		{
			pair<iterator,bool> insert_result = insert(ft::make_pair(k, mapped_type()));
			iterator it = insert_result.first;
			return (it->second);
		}

//		modifiers
		pair<iterator,bool> insert (const value_type& val)
		{
			t_node	*parent;
			t_node	*grandgrandparent;
			t_node	*grandparent;
			t_node	*child;
			t_node	*uncle;
			bool	direction;
			ft::pair<t_node *, bool> pos;

			t_node *new_elem = _new_node(val);

			if (this->empty()) {
				_root = _case_root(new_elem);
				_size++;
				return ft::make_pair(iterator(_root, this), true);
			}

			// search for insertion place, somehow check if key already exist
			pos = _find_position_for_new_node(new_elem->val.first);
			parent = pos.first;
			direction = pos.second;
			if (!direction && _compare(pos.first->val.first, new_elem->val.first) == false)
			{
				_delete_tree(new_elem);
				pair<iterator,bool> res = ft::make_pair(iterator(pos.first, this), pos.second);
				return (res); // already exist
			}
			child = (direction) ? parent->left : parent->right;
			pos.first = child;
			pos.second = true;

			// insert red node
			if (child == _begin)
			{
				new_elem->left = _begin;
				_begin->parent = new_elem;
			}
			else if (child == _end)
			{
				new_elem->right = _end;
				_end->parent = new_elem;
			}
			direction ? parent->left = new_elem : parent->right = new_elem;
			new_elem->parent = parent;
			child = new_elem;
			t_node* new_pos = child;

			//check if tree isn't balanced
			while (parent->color == RED && child->color == RED)
			{
				// balance
				grandparent = parent->parent;
				uncle = (grandparent->right == parent) ? grandparent->left : grandparent->right;
				if (uncle->color == RED)
					child = _case_uncle_red(child);
				else if ((parent->parent->left == parent && parent->left == child) || (parent->parent->right == parent && parent->right == child))
				{
					if (grandparent == _root)
					{
						child = _case_uncle_black_line(child);
						child->parent = _leaf;
						_root = child;
					}
					else
					{
						if (grandparent == grandparent->parent->left)
						{
							grandgrandparent = grandparent->parent;
							child = _case_uncle_black_line(child);
							grandgrandparent->left = child;
							child->parent = grandgrandparent;
						}
						else
						{
							grandgrandparent = grandparent->parent;
							child = _case_uncle_black_line(child);
							grandgrandparent->right = child;
							child->parent = grandgrandparent;
						}
					}
				}
				else
				{
					child = _case_uncle_black_triangle(child);
				}
				parent = child->parent;
			}
			_size++;
			pair<iterator,bool> res = ft::make_pair(iterator(new_pos, this), pos.second);
			return (res);
		}
		iterator insert (iterator position, const value_type& val)
		{
			(void)position;
			return (this->insert(val).first);
		}
		template <class InputIterator>
		void insert (InputIterator first, typename ft::enable_if<ft::is_iterator <InputIterator>::value, InputIterator>::type last)
		{
			t_node	*parent;
			t_node	*grandgrandparent;
			t_node	*grandparent;
			t_node	*child;
			t_node	*uncle;
			bool	direction;
			ft::pair<t_node *, bool> pos;

			while (first != last)
			{
				t_node *new_elem = _new_node(*first);

				if (this->empty()) {
					_root = _case_root(new_elem);
					_size++;
					first++;
					continue;
				}

				// search for insertion place, somehow check if key already exist
				pos = _find_position_for_new_node(new_elem->val.first);
				parent = pos.first;
				direction = pos.second;
				if (direction == false && _compare(pos.first->val.first, new_elem->val.first) == false)
				{
					_delete_tree(new_elem);
					first++;
					continue ; // already exist
				}
				child = (direction) ? parent->left : parent->right;

				// insert red node
				if (child == _begin)
				{
					new_elem->left = _begin;
					_begin->parent = new_elem;
				}
				else if (child == _end)
				{
					new_elem->right = _end;
					_end->parent = new_elem;
				}
				direction ? parent->left = new_elem : parent->right = new_elem;
				new_elem->parent = parent;
				child = new_elem;

				//check if tree isn't balanced
				while (parent->color == RED && child->color == RED)
				{
					// balance
					grandparent = parent->parent;
					uncle = (grandparent->right == parent) ? grandparent->left : grandparent->right;
					if (uncle->color == RED)
						child = _case_uncle_red(child);
					else if ((parent->parent->left == parent && parent->left == child) || (parent->parent->right == parent && parent->right == child))
					{
						if (grandparent == _root)
						{
							child = _case_uncle_black_line(child);
							child->parent = _leaf;
							_root = child;
						}
						else
						{
							if (grandparent == grandparent->parent->left)
							{
								grandgrandparent = grandparent->parent;
								child = _case_uncle_black_line(child);
								grandgrandparent->left = child;
								child->parent = grandgrandparent;
							}
							else
							{
								grandgrandparent = grandparent->parent;
								child = _case_uncle_black_line(child);
								grandgrandparent->right = child;
								child->parent = grandgrandparent;
							}
						}
					}
					else
					{
						child = _case_uncle_black_triangle(child);
					}
					parent = child->parent;
				}
				first++;
				_size++;
			}
		}
		void erase (iterator position)
		{
			key_type key = (*position)->first;
			erase(key);
		}
		size_type erase (const key_type& k)
		{
			t_node	*to_be_removed;
			t_node	*new_child;
			t_node	*parent;
			bool	direction;
			ft::pair<t_node *, bool> pos;

			if (_is_end(*_root)) // tree is empty
				return (0); // return the number of erased nodes

			pos = _find_position_for_new_node(k);
			if (pos.second == true || (pos.second == false && pos.first->val.first != k)) // key doesn't exist
				return (0);

			to_be_removed = pos.first;
			if (!_is_end(*to_be_removed->left) && !_is_end(*to_be_removed->right)) // two children
			{
				// find smallest in right subtree
				new_child = to_be_removed->right;
				while (!_is_end(*new_child->left))
					new_child = new_child->left;

				// copy smallest
				_alloc.destroy(&to_be_removed->val);
				_alloc.construct(&to_be_removed->val, new_child->val);
				to_be_removed = new_child;
			}

			// now to_be_remove has no more than 1 child
			parent = to_be_removed->parent;
			direction = (parent->left == to_be_removed) ? LEFT : RIGHT;
			// choosing inheritor
			if (!_is_end(*to_be_removed->left)) {
				new_child = to_be_removed->left;
				if (to_be_removed->right == _end) {
					new_child->right = _end;
					_end->parent = new_child;
				}
			}
			else {
				new_child = to_be_removed->right;
				// случай с to_be_removed == root рассмотрен отдельно ( это исключает left == begin && right == end)
				if (to_be_removed->left == _begin) {
					if (!_is_end(*new_child)) {
						new_child->left = _begin;
						_begin->parent = new_child;
					}
					else {
						new_child = _begin;
					}
				}
			}

			if (to_be_removed->color == RED) {
				_e_case_parent_red_child_black(parent, to_be_removed, new_child, direction);
			}
			else {
				if (new_child->color == RED) {
					new_child->color = BLACK;
					_e_case_parent_red_child_black(parent, to_be_removed, new_child, direction);
				}
				else {
					if (direction == RIGHT) {
						parent->right = new_child;
					} else {
						parent->left = new_child;
					}
					new_child->parent = parent;
					_alloc.destroy(&to_be_removed->val);
					delete to_be_removed;

					_erase_balance(new_child);
				}
			}
			_size--;
			return (1); // return the number of erased nodes
		}
		void erase (iterator first, iterator last)
		{
			ft::vector<value_type> elements_to_be_deleted;
			for (; first != last; ++first) {
				elements_to_be_deleted.push_back(*first);
			}
			typename ft::vector<value_type>::const_iterator it = elements_to_be_deleted.begin();
			for (; it != elements_to_be_deleted.end(); ++it) {
				erase(it->first);
			}
		}
		void swap (map& x)
		{
			std::swap(this->_leaf, x._leaf);
			std::swap(this->_root, x._root);
			std::swap(this->_end, x._end);
			std::swap(this->_begin, x._begin);
			std::swap(this->_compare, x._compare);
			std::swap(this->_alloc, x._alloc);
			std::swap(this->_size, x._size);
		}
		void clear()
		{
			_delete_tree(*_root);
			_root = _leaf;
			_size = 0;
		}

//		observers
		key_compare key_comp() const
		{
			return (_compare);
		}
		value_compare value_comp() const
		{
			return _value_compare(_compare);
		}

//		operations
		iterator find (const key_type& k)
		{
			t_node	*tmp;

			tmp = _root;
			while (!_is_end(*tmp))
			{
				if (_compare(k, tmp->val.first))
					tmp = tmp->left;
				else
				{
					if (!_compare(tmp->val.first, k))
						return (iterator(tmp, this));
					tmp = tmp->right;
				}
			}
			return (this->end());
		}
		const_iterator find (const key_type& k) const
		{
			t_node	*tmp;

			tmp = _root;
			while (!_is_end(*tmp))
			{
				if (_compare(k, tmp->val.first))
					tmp = tmp->left;
				else
				{
					if (!_compare(tmp->val.first, k))
						return (const_iterator(tmp));
					tmp = tmp->right;
				}
			}
			return (this->end());
		}
		size_type count (const key_type& k) const
		{
			t_node	*tmp;

			tmp = _root;
			while (!_is_end(*tmp))
			{
				if (_compare(k, tmp->val.first))
					tmp = tmp->left;
				else
				{
					if (!_compare(tmp->val.first, k))
						return (1);
					tmp = tmp->right;
				}
			}
			return (0);
		}
		iterator lower_bound (const key_type& k)
		{
			iterator it = this->begin();
			iterator ite = this->end();

			while (it != ite)
			{
				if (!_compare(it->first, k))
					break;
				++it;
			}
			return (it);
		}
		const_iterator lower_bound (const key_type& k) const
		{
			const_iterator it = this->begin();
			const_iterator ite = this->end();

			while (it != ite)
			{
				if (!_compare(it->first, k))
					break;
				++it;
			}
			return (it);
		} // doesn't work
		iterator upper_bound (const key_type& k)
		{
			iterator it = this->begin();
			iterator ite = this->end();

			while (it != ite)
			{
				if (_compare(k, it->first))
					break;
				++it;
			}
			return (it);
		}
		const_iterator upper_bound (const key_type& k) const
		{
			const_iterator it = this->begin();
			const_iterator ite = this->end();

			while (it != ite)
			{
				if (_compare(k, it->first))
					break;
				++it;
			}
			return (it);
		} // doesn't work
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const // doesn't work
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}
		pair<iterator,iterator> equal_range (const key_type& k)
		{
			return (ft::make_pair(this->lower_bound(k), this->upper_bound(k)));
		}

//		allocator
		allocator_type get_allocator() const
		{
			return (_alloc);
		}



		void	print_tree() const
		{
			print2DUtil(_root, 0);
		}

	private:
		t_node *_new_node()
		{
			t_node *next = new t_node;

			next->right = nullptr;
			next->left = nullptr;
			next->parent = nullptr;
			next->color = BLACK;
			return (next);
		}
		t_node *_new_node(const ft::pair<const Key, T>& value)
		{
			t_node *next = new t_node;

			next->right = _leaf;
			next->left = _leaf;
			next->parent = nullptr;
			next->color = RED;
			_alloc.construct(&next->val, value);
			return (next);
		}
		t_node *_new_node(const t_node & src, const map<Key, T>& ref)
		{
			t_node *next = new t_node;

			_child_copy(&next->right, *src.right, ref);
			next->right->parent = next;
			_child_copy(&next->left, *src.left, ref);
			next->left->parent = next;
			next->parent = nullptr;
			next->color = src.color;
			_alloc.construct(&next->val, src.val);
			return (next);
		}

		void	_child_copy(t_node **next, const t_node & src, const map<Key, T> & ref)
		{
			if (&src != ref._begin && &src != ref._end && &src != ref._leaf)
				*next = _new_node(src, ref);
			else
			{
				if (&src == ref._begin)
				{
					*next = _begin;
					_begin->parent = *next;
				}
				else if (&src == ref._end)
				{
					*next = _end;
					_end->parent = *next;
				}
				else
					*next = _leaf;
			}
		}

		void	_delete_tree(t_node *old_tree)
		{
			if (!_is_end(*old_tree))
			{
				_delete_tree(old_tree->right);
				_delete_tree(old_tree->left);
				_alloc.destroy(&old_tree->val);
				delete old_tree;
			}
		}

		// returns true if src - leaf
		bool	_is_end(const t_node & src) const
		{
			if (&src == _leaf || &src == _begin || &src == _end)
				return (true);
			return (false);
		}

		t_node *_case_root(t_node *child)
		{
			child->color = BLACK;
			child->left = _begin;
			_begin->parent = child;
			child->right = _end;
			_end->parent = child;
			child->parent = _leaf;
			return (child);
		}
		t_node *_case_uncle_red(t_node *child)
		{
			t_node	*parent;
			t_node	*grandparent;

			parent = child->parent;
			grandparent = parent->parent;
			grandparent->left->color = BLACK;
			grandparent->right->color = BLACK;
			if (grandparent->parent != _leaf)
				grandparent->color = RED;
			return (grandparent);
		}
		t_node *_case_uncle_black_line(t_node *child)
		{
			t_node	*parent;
			t_node	*grandparent;

			parent = child->parent;
			grandparent = parent->parent;

			grandparent->color = RED;
			parent->color = BLACK;
			if (grandparent->right == parent)
				grandparent = _left_rotation(parent);
			else
				grandparent = _right_rotation(parent);
			return (grandparent);
		}
		t_node *_case_uncle_black_triangle(t_node *child)
		{
			t_node	*parent;
			t_node	*grandparent;

			parent = child->parent;
			grandparent = parent->parent;
			if (parent->left == child)
			{
				grandparent->right = child;
				child->parent = grandparent;
				parent->left = child->right;
				child->right->parent = parent;
				child->right = parent;
				parent->parent = child;
			}
			else
			{
				grandparent->left = child;
				child->parent = grandparent;
				parent->right = child->left;
				child->left->parent = parent;
				child->left = parent;
				parent->parent = child;
			}
			return (parent);
		}

		void	_e_case_parent_red_child_black(t_node *parent, t_node *to_be_removed, t_node *new_child, bool direction)
		{
			if (direction == RIGHT)
				parent->right = new_child;
			else
				parent->left = new_child;
			new_child->parent = parent;
			_alloc.destroy(&to_be_removed->val);
			delete to_be_removed;
		}

		static t_node *_left_rotation(t_node *parent)
		{
			t_node *tmp;

			tmp = parent->left;
			parent->left = parent->parent;
			parent->parent->parent = parent;
			parent->left->right = tmp;
			tmp->parent = parent->left;
			return (parent);
		}
		static t_node *_right_rotation(t_node *parent)
		{
			t_node *tmp;

			tmp = parent->right;
			parent->right = parent->parent;
			parent->parent->parent = parent;
			parent->right->left = tmp;
			tmp->parent = parent->right;
			return (parent);
		}

		// return value: if tree is empty - second=false and first=_root
		// 				 if node already exist - second=false and first=node
		// 				 if position was found - second=direction and first=parent
		ft::pair<t_node *, bool> _find_position_for_new_node(const key_type &val)
		{
			t_node	*parent;
			t_node	*tmp_r;
			t_node	*tmp_l;
			bool direction;

			parent = _root;
			if (_is_end(*parent))
				return (ft::make_pair<t_node *, bool>(parent, false));

			tmp_r = parent->right;
			tmp_l = parent->left;
			direction = _compare(val, parent->val.first);
			if (direction == _compare(parent->val.first, val)) // key already exist - key
				return (ft::make_pair(parent, false));
			while ((!_is_end(*tmp_l) || !direction) && (!_is_end(*tmp_r) || direction))
			{
				parent = direction ? tmp_l : tmp_r;
				tmp_l = parent->left;
				tmp_r = parent->right;
				direction = _compare(val, parent->val.first);
				if (direction == _compare(parent->val.first, val))
					return (ft::make_pair(parent, false)); // key already exist, parent - key
			}
			return (ft::make_pair(parent, direction));
		}

		void _check_wiki_case_2(t_node* new_child, t_node* parent, t_node* brother, bool direction)
		{
			// wiki case 2: sibling is red
			if (brother->color == RED) {
				parent->color = RED;
				brother->color = BLACK;

				t_node* (*rotation)(t_node*) = (direction == LEFT) ? &_left_rotation : &_right_rotation;
				if (parent == _root) {
					_root = rotation(brother);
					_root->parent = _leaf;
				}
				else {
					t_node* grandparent = parent->parent;
					if (parent == grandparent->left) {
						grandparent->left = rotation(brother);
						grandparent->left->parent = grandparent;
					} else {
						grandparent->right = rotation(brother);
						grandparent->right->parent = grandparent;
					}
				}
				brother = (direction == RIGHT) ? parent->left : parent->right;
			}
			_check_wiki_case_3(new_child, parent, brother, direction);
		}
		void _check_wiki_case_3(t_node* new_child, t_node* parent, t_node* brother, bool direction) // wiki case 3
		{
			// wiki case 3: parent, sibling and his kids are black
			if (brother->color == BLACK) {
				if (parent->color == BLACK && brother->left->color == BLACK && brother->right->color == BLACK) {
					brother->color = RED;
					new_child = parent;
					_erase_balance(new_child);
				}
			}
			_check_wiki_case_4(parent, brother, direction);
		}
		void _check_wiki_case_4(t_node* parent, t_node* brother, bool direction) // wiki 4
		{
			// wiki case 4: parent is red, but sibling and his kids are black
			if (parent->color == RED && brother->left->color == BLACK && brother->right->color == BLACK) {
				parent->color = BLACK;
				brother->color = RED;
				// done
			}
			else {
				_check_wiki_case_5(parent, brother, direction);
			}
		}
		void _check_wiki_case_5(t_node* parent, t_node* brother, bool direction) {
			// wiki case 5: sibling is black, left child is red, right child is black and new_child direction is left
			if (brother->color == BLACK && brother->left->color == RED && brother->right->color == BLACK && direction == LEFT) {
				brother->color = RED;
				brother->left->color = BLACK;

				if (parent == _root) {
					_root = _left_rotation(brother);
					_root->parent = _leaf;
				}
				else {
					t_node* grandparent = parent->parent;
					if (parent == grandparent->left) {
						grandparent->left = _left_rotation(brother);
						grandparent->left->parent = grandparent;
					} else {
						grandparent->right = _left_rotation(brother);
						grandparent->right->parent = grandparent;
					}
				}
				brother = parent->right;
			}
			else if (brother->color == BLACK && brother->left->color == BLACK && brother->right->color == RED && direction == RIGHT) {
				brother->color = RED;
				brother->left->color = BLACK;

				if (parent == _root) {
					_root = _right_rotation(brother);
					_root->parent = _leaf;
				}
				else {
					t_node* grandparent = parent->parent;
					if (parent == grandparent->left) {
						grandparent->left = _right_rotation(brother);
						grandparent->left->parent = grandparent;
					} else {
						grandparent->right = _right_rotation(brother);
						grandparent->right->parent = grandparent;
					}
				}
				brother = parent->left;
			}
			_check_wiki_case_6(parent, brother, direction);
		}
		void _check_wiki_case_6(t_node* parent, t_node* brother, bool direction) {
			// wiki case 6: sibling is black
			if (brother->color == BLACK) {
				brother->color = parent->color;
				parent->color = BLACK;

				t_node* grandparent;
				grandparent = parent->parent;
				if (direction == LEFT) {
					if (brother->right->color == RED) {
						brother->right->color = BLACK;
						if (parent == _root) {
							_root = _left_rotation(brother);
							_root->parent = _leaf;
						}
						else if (grandparent->right == parent) {
							grandparent->right = _left_rotation(brother);
							grandparent->right->parent = grandparent;
						}
						else {
							grandparent->left = _left_rotation(brother);
							grandparent->left->parent = grandparent;
						}
					}
				}
				else {
					if (brother->left->color == RED) {
						brother->left->color = BLACK;
						if (parent == _root) {
							_root = _right_rotation(brother);
							_root->parent = _leaf;
						}
						else if (grandparent->right == parent) {
							grandparent->right = _right_rotation(brother);
							grandparent->right->parent = grandparent;
						}
						else {
							grandparent->left = _right_rotation(brother);
							grandparent->left->parent = grandparent;
						}
					}
				}
			}
		}

		void _erase_balance(t_node* new_child)
		{
			if (new_child == _root) {
				return ;
			}

			t_node	*parent;
			t_node	*brother;
			bool	direction;

			parent = new_child->parent;
			direction = (new_child == parent->right) ? RIGHT : LEFT;
			brother = (direction == RIGHT) ? parent->left : parent->right;
			_check_wiki_case_2(new_child, parent, brother, direction);
		}

		#define COUNT 5
		void print2DUtil(t_node *root, int space) const
		{
			// Base case
			if (root == _leaf || root == _begin || root == _end)
			{
				for (int i = 0; i < space; i++)
					std::cout<<" ";
				if (root == _begin)
					std::cout<<"\x1b[33m" << "*" << "\x1b[0m";
				else if (root == _end)
					std::cout<<"\x1b[35m" << "*" << "\x1b[0m";
				else
					std::cout<<"\x1b[34m" << "*" << "\x1b[0m";
				return;
			}

			// Increase distance between levels
			space += COUNT;

			// Process right child first
			print2DUtil(root->right, space);

			// Print current node after space
			// count
			std::cout << std::endl;
			for (int i = COUNT; i < space; i++)
				std::cout<<" ";
			if (root->color == RED)
				std::cout << "\x1b[31m";
			else
				std::cout << "\x1b[34m";
			std::cout<<root->val.second<<"\n";
			std::cout << "\x1b[0m";

			// Process left child
			print2DUtil(root->left, space);
		}


	private:
		allocator_type	_alloc;
		key_compare		_compare;
		size_type		_size;
		t_node			*_root;
		t_node			*_leaf;
		t_node			*_begin;
		t_node			*_end;
	};


}

#endif //FT_CONTAINERS_MAP_HPP
