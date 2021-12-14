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
//			_root = _leaf;

			// todo: delete later
			_root = _new_node(ft::make_pair(3, 3));
			_root->left = _new_node(ft::make_pair(2, 2));
			_root->left->parent = _root;
			_root->left->left = _new_node(ft::make_pair(-1, -1));
			_root->left->left->parent = _root->left;
			_root->left->right = _new_node(ft::make_pair(1, 1));
			_root->left->right->parent = _root->left;
			_root->left->right->right = _new_node(ft::make_pair(0, 0));
			_root->left->right->right->parent = _root->left->right;
			_root->left->left->left = _begin;
			_begin->parent = _root->left;
			_root->right = _new_node(ft::make_pair(6, 6));
			_root->right->parent = _root;
			_root->right->left = _new_node(ft::make_pair(4, 4));
			_root->right->left->parent = _root->right;
			_root->right->right = _new_node(ft::make_pair(8, 8));
			_root->right->right->parent = _root->right;
			_root->right->right->right = _end;
			_end->parent = _root->right->right;



		}
//		template <class InputIterator>
//		map (InputIterator first, typename ft::enable_if<ft::is_iterator <InputIterator>::value, InputIterator>::type last,
//			 const key_compare& comp = key_compare(),
//			 const allocator_type& alloc = allocator_type()) : _compare(comp), _alloc(alloc)
//		{
//			_leaf = _new_node();
//			_begin = _new_node();
//			_end = _new_node();
//		}
		map (const map<Key, T> & x) : _size(0)
		{
			_leaf = _new_node();
			_begin = _new_node();
			_end = _new_node();
			_root = _leaf;
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
//			t_node *tmp;
//			int num = 0;
//			int stars = 0;
//			int row = 0;
//
//
//
//			std::queue<t_node *> next;
//
//			next.push(_root);
//
//			while (!next.empty())
//			{
//				tmp = next.front();
//				if (!_is_end(*tmp))
//				{
//					std::cout << tmp->val.second << " ";
//					num++;
//				}
//				else
//				{
//					std::cout << "* ";
//					stars++;
//				}
//				next.pop();
//				if (!_is_end(*tmp))
//				{
//					next.push(tmp->left);
//					next.push(tmp->right);
//				}
//
//			}
//			std::cout << "|" << std::endl;
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
