//
// Created by Debby Willette on 10/26/21.
//

#ifndef FT_CONTAINERS_MAP_HPP
#define FT_CONTAINERS_MAP_HPP

#define RED 1
#define BLACK 2

#include "pair.hpp"
#include "enable_if.hpp"
#include "iterator.hpp"
#include <queue>

namespace ft
{

	template < class Key, class T, class Compare = std::less<Key>, class Alloc =
			std::allocator<ft::pair<const Key,T> > >
	class map
	{
	private:
		template <class Iter>
		class _map_iterator
		{
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

	public:
		typedef Key key_type;
		typedef T mapped_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::value_type value_type;
		typedef Compare key_compare;
//		typedef value_compare;

		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename std::ptrdiff_t difference_type;
		typedef size_t size_type;

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

	public:
		typedef _map_iterator<t_node *> iterator;
		typedef _map_iterator<const t_node *> const_iterator;
//		typedef typename ft::_reverse_iterator<iterator> reverse_iterator;
//		typedef typename ft::_reverse_iterator<const_iterator> const_reverse_iterator;


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
			 const allocator_type& alloc = allocator_type()) : _compare(comp), _alloc(alloc), _size(0)
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
//		const_iterator begin() const;
		iterator end()
		{
			return (iterator(_end, this));
		}
//		const_iterator end() const;

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
			t_node	*tmp;
			t_node	*parent;

			tmp = _root;
			parent = _root->parent;
			while (!_is_end(*tmp))
			{
				if (_compare(k, tmp->val.first))
					tmp = tmp->left;
				else
				{
					if (!_compare(tmp->val.first, k))
						return (tmp->val.second);
					tmp = tmp->right;
				}
				parent = tmp->parent;
			}
			// return (insert (parent, k))
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

			// search for insertion place, somehow check if key already exist
			pos = _find_pos(new_elem->val.first);
			parent = pos.first;
			direction = pos.second;
			if (parent == _leaf)
				_root = _case_root(new_elem);
			else if (direction == false && _compare(pos.first->val.first, new_elem->val.first) == false)
			{
				_delete_tree(new_elem);
				return (pos); // already exist
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
			return (pos);
		}
		iterator insert (iterator position, const value_type& val)
		{
			t_node *child;
			bool direction;

			direction = _compare(val.first, position->val.first);
			child = (direction) ? position->left : position->right;
			if (!_is_end(*child))
				return (this->insert(val).first);
			//use hint?
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

				// search for insertion place, somehow check if key already exist
				pos = _find_pos(new_elem->val.first);
				parent = pos.first;
				direction = pos.second;
				if (parent == _leaf)
					_root = _case_root(new_elem);
				else if (direction == false && _compare(pos.first->val.first, new_elem->val.first) == false)
				{
					_delete_tree(new_elem);
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
//
//						print_tree();
//						std::cout << std::endl << "------------------" << std::endl;

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

//				print_tree();
//				std::cout << std::endl << "------------------" << std::endl;

				first++;
				_size++;
			}
		}
		void erase (iterator position)
		{
			t_node	*to_be_removed;
//			t_node	*parent;
			t_node	*new_child;
			t_node	**parent;
			bool	direction;
			bool	first;

			to_be_removed = position;
//			parent = to_be_removed->parent;
			first = (to_be_removed == _root);

			if (!first)
			{
				direction = (parent->left == to_be_removed);
				parent = (direction) ? &parent->left : &parent->right;
			}
			else
				parent = &_root;

			if (_is_end(*to_be_removed->left) && _is_end(to_be_removed->right)) // no children
			{
				if (!first)
				{
					**parent = (direction) ? to_be_removed->left : to_be_removed->right;
					(direction) ? to_be_removed->left->parent = parent : to_be_removed->right->parent = parent;
				}
				else
					_root = _leaf;
			}
			else if (_is_end(*to_be_removed->left) || _is_end(to_be_removed->right)) // 1 child
			{
				if (!_is_end(*to_be_removed->left))
				{
//					if (!first)
//					{
//						(direction) ? parent->left = to_be_removed->left : parent->right = to_be_removed->left;
						**parent = to_be_removed->left;
						to_be_removed->left->parent = (!first) ? *parent : _leaf;
						if (to_be_removed->right == _end)
							to_be_removed->left->right = _end;
//					}
//					else
//					{
//						_root = to_be_removed->left;
//					}
				}
				else
				{
					**parent = to_be_removed->right;
					to_be_removed->right->parent = (!first) ? *parent : _leaf;
					if (to_be_removed->left == _begin)
						to_be_removed->right->left = _begin;
				}
			}
			else // 2 children
			{
				new_child = to_be_removed->right;
				while (new_child->left != _leaf)
					new_child = new_child->left;
//				(direction) ? parent->left = new_child : parent->right = new_child;
				**parent = new_child;
				new_child->parent->left = new_child->right;
//				new_child->parent = parent;
				new_child->parent = (!first) ? *parent : _leaf;
				new_child->left = to_be_removed->left;
				new_child->right = to_be_removed->right;
			}
			_alloc.destroy(&to_be_removed->val);
			delete to_be_removed;
		}
		size_type erase (const key_type& k)
		{
			t_node	*to_be_removed;
			t_node	*new_child;
			t_node	**parent;
			bool	direction;
			bool	first;
			ft::pair<t_node *, bool> pos;

			pos = _find_pos(k);
			if (!pos.second)
			{
				if (_compare(pos.first->val.first, k) == _compare(k, pos.first->val.first))
				{
					to_be_removed = pos.first;
					parent = &to_be_removed->parent;
					first = (to_be_removed == _root);

					if (!first)
					{
						direction = ((*parent)->left == to_be_removed);
						parent = (direction) ? &((*parent)->left) : &((*parent)->right);
					}
					else
						parent = &_root;

					if (_is_end(*to_be_removed->left) && _is_end(*to_be_removed->right)) // no children
					{
						if (!first)
						{
							*parent = (direction) ? to_be_removed->left : to_be_removed->right;
							(direction) ? to_be_removed->left->parent = *parent : to_be_removed->right->parent = *parent;
						}
						else
							_root = _leaf;
					}
					else if (_is_end(*to_be_removed->left) || _is_end(*to_be_removed->right)) // 1 child
					{
						if (!_is_end(*to_be_removed->left))
						{
//					if (!first)
//					{
//						(direction) ? parent->left = to_be_removed->left : parent->right = to_be_removed->left;
							to_be_removed->left->parent = (!first) ? *parent : _leaf;
							*parent = to_be_removed->left;
							if (to_be_removed->right == _end)
								to_be_removed->left->right = _end;
//					}
//					else
//					{
//						_root = to_be_removed->left;
//					}
						}
						else
						{
							to_be_removed->right->parent = (!first) ? *parent : _leaf;
							*parent = to_be_removed->right;
							if (to_be_removed->left == _begin)
								to_be_removed->right->left = _begin;
						}
					}
					else // 2 children
					{
						new_child = to_be_removed->right;
						while (new_child->left != _leaf)
							new_child = new_child->left;
//				(direction) ? parent->left = new_child : parent->right = new_child;
						*parent = new_child;
						new_child->parent->left = new_child->right;
//				new_child->parent = parent;
						new_child->parent = (!first) ? *parent : _leaf;
						new_child->left = to_be_removed->left;
						new_child->right = to_be_removed->right;
					}
					_alloc.destroy(&to_be_removed->val);
					delete to_be_removed;
				}
			}


		}
		void erase (iterator first, iterator last);
		void swap (map& x);
		void clear();

//		observers
		key_compare key_comp() const;
//		value_compare value_comp() const;

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
		}
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
		}
		pair<const_iterator,const_iterator> equal_range (const key_type& k) const;
		pair<iterator,iterator>             equal_range (const key_type& k);

//		allocator
		allocator_type get_allocator() const;


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
		t_node *_new_node(ft::pair<const Key, T> value)
		{
			t_node *next = new t_node;

			next->right = _leaf;
			next->left = _leaf;
			next->parent = nullptr;
			next->color = RED;
			_alloc.construct(&next->val, value);
			return (next);
		}
		t_node *_new_node(const t_node & src, const map<Key, T> & ref)
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

		t_node *_left_rotation(t_node *parent)
		{
			t_node *tmp;

			tmp = parent->left;
			parent->left = parent->parent;
			parent->parent->parent = parent;
			parent->left->right = tmp;
			tmp->parent = parent->left;
			return (parent);
		}
		t_node *_right_rotation(t_node *parent)
		{
			t_node *tmp;

			tmp = parent->right;
			parent->right = parent->parent;
			parent->parent->parent = parent;
			parent->right->left = tmp;
			tmp->parent = parent->right;
			return (parent);
		}

		ft::pair<t_node *, bool> _find_pos(const key_type &val)
		{
			t_node	*parent;
			t_node	*tmp_r;
			t_node	*tmp_l;
			bool direction;

			parent = _root;
			if (_is_end(*parent))
				return (ft::make_pair(parent, false));

			tmp_r = parent->right;
			tmp_l = parent->left;
			direction = _compare(val, parent->val.first);
			if (direction == _compare(parent->val.first, val)) // key already exist - key
				return (ft::make_pair(parent, false));
			while ((!_is_end(*tmp_l) || direction == false) && (!_is_end(*tmp_r) || direction == true))
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
