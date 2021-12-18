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
			//TODO: breaks iterator
			t_node	*parent;
			t_node	*tmp_r;
			t_node	*tmp_l;
			t_node	*child;
			t_node	*uncle;
			bool	direction;

			_leaf = _new_node();
			_begin = _new_node();
			_end = _new_node();
			_root = _leaf;
			_root->parent = _leaf;

			while (first != last)
			{
				t_node *new_elem = _new_node(*first);
				parent = _root;
				if (!_is_end(*parent))
				{
					// search for insertion place, somehow check if key already exist
					tmp_r = parent->right;
					tmp_l = parent->left;
					direction = _compare(new_elem->val.first, parent->val.first);
					if (!direction && new_elem->val.first == parent->val.first)
						continue ; // skip if key already exist ??(or change value)
					while ((!_is_end(*tmp_l) || direction == false) && (!_is_end(*tmp_r) || direction == true))
					{
						parent = direction ? tmp_l : tmp_r;
						tmp_l = parent->left;
						tmp_r = parent->right;
						direction = _compare(new_elem->val.first, parent->val.first);
					}
					child = direction ? tmp_l : tmp_r;

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

//					print_tree();
//					std::cout << std::endl << "------------------" << std::endl;

					//check if tree isn't balanced
					while (parent->color == RED && child->color == RED)
					{
						// balance
						tmp_l = parent->parent;
						uncle = (tmp_l->right == parent) ? tmp_l->left : tmp_l->right;
						if (uncle->color == RED)
							child = _case_uncle_red(child);
						else if ((parent->parent->left == parent && parent->left == child) || (parent->parent->right == parent && parent->right == child))
						{
							if (tmp_l == _root)
							{
								child = _case_uncle_black_line(child);
								child->parent = _leaf;
								_root = child;
							}
							else
							{
								if (tmp_l == tmp_l->parent->left)
								{
									tmp_r = tmp_l->parent;
									child = _case_uncle_black_line(child);
									tmp_r->left = child;
									child->parent = tmp_r;
								}
								else
								{
									tmp_r = tmp_l->parent;
									child = _case_uncle_black_line(child);
									tmp_r->right = child;
									child->parent = tmp_r;
								}
							}
						}
						else
						{
							child = _case_uncle_black_triangle(child);
						}
						parent = child->parent;
					}

				}
				else
				{
					// new element - root
					_root = _case_root(new_elem);
				}

//				print_tree();
//				std::cout << std::endl << "------------------" << std::endl;

				first++;
				_size++;
			}

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

		void	print_tree() const
		{
			print2D(_root);
		}
#define COUNT 5

		void print2DUtil(t_node *root, int space) const
		{
			// Base case
			if (root == _leaf || root == _begin || root == _end)
			{
				for (int i = 0; i < space; i++)
					std::cout<<" ";
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

		void print2D(t_node *root) const
		{
			// Pass initial space count as 0
			print2DUtil(root, 0);
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
					*next = _begin;
				else if (&src == ref._end)
					*next = _end;
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
			child->right = _end;
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
			tmp->parent = parent->left->right;
			return (parent);
		}
		t_node *_right_rotation(t_node *parent)
		{
			t_node *tmp;

			tmp = parent->right;
			parent->right = parent->parent;
			parent->parent->parent = parent;
			parent->right->left = tmp;
			tmp->parent = parent->right->left;
			return (parent);
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
