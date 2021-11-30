//
// Created by Debby Willette on 10/19/21.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "enable_if.hpp"

// TODO: enable_if для методов с итераторами (assign, insert, constructor),
//  swap, const reverse iterator, create _copy method

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector
	{

	public:
		typedef T value_type;
		typedef Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;
		typedef typename std::ptrdiff_t difference_type;
		typedef size_t size_type;


		typedef ft::_iterator<pointer> iterator;
		typedef ft::_iterator<const_pointer> const_iterator;
		typedef ft::_reverse_iterator<iterator> reverse_iterator;
		typedef ft::_reverse_iterator<const_iterator> const_reverse_iterator;


		// constructor
		explicit vector(const allocator_type &alloc = allocator_type()) :
				_size(0), _mem_size(0), _alloc(alloc)
		{}
		explicit vector(size_type n, const value_type& val = value_type(),
						const allocator_type& alloc = allocator_type()) :
						 _size(n), _mem_size(n * 2), _alloc(alloc)
		{
			size_t i;

			try
			{
				_vector_base = _alloc.allocate(_mem_size);
				for (i = 0; i < n; i++)
					_alloc.construct(&_vector_base[i], val);
			}
			catch (std::bad_alloc & e)
			{
				throw e;
			}
		}
		template<class InputIterator>
		vector(InputIterator first, typename
		ft::enable_if<std::__is_input_iterator <InputIterator>::value, InputIterator>::type
		last, const allocator_type & alloc =
				allocator_type()) : _alloc(alloc)
		{
			if (first > last)
			{
				throw std::length_error("vector");
			}
			try
			{
				size_t count;
				count = std::abs(last - first);
				_size = count;
				_mem_size = count * 2;
				_vector_base = _alloc.allocate(_mem_size);
				count = 0;
				for (; first != last; first++)
					_alloc.construct(&_vector_base[count++], *first);
			}
			catch (std::bad_alloc & e)
			{
				throw e;
			}
		}
		vector(const vector<T, Alloc> & x) : _size(0), _mem_size(0), _alloc(x
		._alloc)
		{
			*this = x;
		}

		// destructor
		virtual ~vector()
		{
			_delete_old(_vector_base);
//			for (size_t i = 0; i < _size; i++)
//				_alloc.destroy(&_vector_base[i]);
//			_alloc.deallocate(_vector_base, _mem_size);
		}

		// operator = overload
		vector<T, Alloc> & operator=(const vector<T, Alloc> & src)
		{
			if (this == &src)
				return (*this);

			pointer old_base;

			old_base = _vector_base;
			try
			{
				_delete_old(old_base);
				_alloc = src._alloc;
				_mem_size = src._mem_size;
				_size = src._size;
				_vector_base = _alloc.allocate(_mem_size);
				for (size_t i = 0; i < _size; i++)
					_alloc.construct(&_vector_base[i], src._vector_base[i]);
			}
			catch (std::bad_alloc & e)
			{
				throw e;
			}
			return (*this);
		}

		// iterators
		iterator begin()
		{
			return (iterator(&_vector_base[0]));
		}
		const_iterator begin() const
		{
			return (const_iterator(&_vector_base[0]));
		}
		iterator end()
		{
			return (iterator(&_vector_base[_size]));
		}
		const_iterator end() const
		{
			return (const_iterator(&_vector_base[_size]));
		}
		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end() - 1));
		}
		const_reverse_iterator rbegin() const
		{
			return (const_reverse_iterator(this->end() - 1));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin() - 1));
		}
		const_reverse_iterator rend() const
		{
			return (const_reverse_iterator(this->begin() - 1));
		}

		// capacity
		size_type size() const
		{
			return (_size);
		}
		size_type max_size() const
		{
			return (_alloc.max_size());
		}
		void resize(size_type n, value_type val = value_type())
		{
			if (n > this->max_size())
				throw std::length_error("length_error");
			if (n < _size)
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(&_vector_base[i]);
			} else if (n < _mem_size)
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(&_vector_base[i], val);
			} else
			{
				pointer	old_base;

				old_base = _vector_base;
				try
				{
					_vector_base = _alloc.allocate(n * 2);
					for (size_type i = 0; i < n; i++)
					{
						if (i < _size)
							_alloc.construct(&_vector_base[i], old_base[i]);
						else
							_alloc.construct(&_vector_base[i], val);
					}
					_delete_old(old_base);
					_mem_size = n * 2;
				}
				catch (std::bad_alloc & e)
				{
					_vector_base = old_base;
					throw e;
				}
			}
			_size = n;
		}
		size_type capacity() const
		{
			return (_mem_size);
		}
		bool empty() const
		{
			return (_size == 0);
		}
		void reserve(size_type n)
		{
			pointer old_base;

			if (n <= _mem_size)
				return ;
			if (n > this->max_size())
				throw std::length_error("length_error");

			old_base = _vector_base;
			try
			{
				_vector_base = _alloc.allocate(n);
				for (size_type i = 0; i < _size; i++)
					_alloc.construct(&_vector_base[i], old_base[i]);
				_delete_old(old_base);
				_mem_size = n;
			}
			catch (std::bad_alloc & e)
			{
				_vector_base = old_base;
				throw e;
			}
		}

		// element access
		reference operator[](size_type n)
		{
			return (_vector_base[n]);
		}
		const_reference operator[](size_type n) const
		{
			return (_vector_base[n]);
		}
		reference at(size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("out_of_range");
			return (_vector_base[n]);
		}
		const_reference at(size_type n) const
		{
			if (n >= _size)
				throw std::out_of_range("out_of_range");
			return (_vector_base[n]);
		}
		reference front()
		{
			return (_vector_base[0]);
		}
		const_reference front() const
		{
			return (_vector_base[0]);
		}
		reference back()
		{
			return (_vector_base[_size - 1]);
		}
		const_reference back() const
		{
			return (_vector_base[_size - 1]);
		}

		// modifiers
		template <class InputIterator>
		void assign(InputIterator first, typename
		ft::enable_if<std::__is_input_iterator <InputIterator>::value,
		InputIterator>::type last)
		{
			size_type	i;
			size_type	count;

			count = std::abs(last - first);
			if (count > this->max_size())
				throw std::length_error("length_error");
			if (count < _mem_size)
			{
				for (i = 0; i < _size; i++)
					_alloc.destroy(&_vector_base[i]);
			} else
			{
				pointer old_base;

				old_base = _vector_base;
				try
				{
					_vector_base = _alloc.allocate(count * 2);
					_delete_old(old_base);
					_mem_size = count * 2;
				}
				catch (std::bad_alloc & e)
				{
					_vector_base = old_base;
					throw e;
				}
			}
			i = 0;
			for ( ; first != last; ++first)
				_alloc.construct(&_vector_base[i++], *first);
		}
		void assign(size_type n, const value_type& val)
		{
			if (n > this->max_size())
				throw std::length_error("length_error");
			if (n < _mem_size)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_vector_base[i]);
			} else
			{
				pointer old_base;

				old_base = _vector_base;
				try
				{
					_vector_base = _alloc.allocate(n * 2);
					_delete_old(old_base);
					_mem_size = n * 2;
				}
				catch (std::bad_alloc & e)
				{
					_vector_base = old_base;
					throw e;
				}
			}
			for (size_type i = 0; i < n; i++)
				_alloc.construct(&_vector_base[i], val);
			_size = n;
		}
		void push_back(const value_type& val)
		{
			if (_size == _mem_size)
			{
				pointer old_base;

				old_base = _vector_base;
				try
				{
					_vector_base = _alloc.allocate(_size * 2);
					for (size_type i = 0; i < _size; i++)
						_alloc.construct(&_vector_base[i], old_base[i]);

					_delete_old(old_base);
					_mem_size = _size * 2;
				}
				catch (std::bad_alloc & e)
				{
					_vector_base = old_base;
					throw e;
				}
			}
			_alloc.construct(&_vector_base[_size++], val);
		}
		void pop_back()
		{
			if (!this->empty())
				_alloc.destroy(&_vector_base[--_size]);
		}
		iterator insert(iterator position, const value_type &val)
		{
			iterator	res;
			size_type	i;

			if (_size < _mem_size)
			{
				i = _size;
				while (position != &_vector_base[i])
				{
					_alloc.destroy(&_vector_base[i]);
					_alloc.construct(&_vector_base[i], _vector_base[i - 1]);
					i--;
				}
				_alloc.destroy(&_vector_base[i]);
				_alloc.construct(&_vector_base[i], val);
				res = iterator(&_vector_base[i]);
			} else
			{
				pointer old_base;
				iterator it = this->begin();
				iterator ite = this->end();

				old_base = _vector_base;
				try
				{
					_vector_base = _alloc.allocate(_mem_size * 2);
					i = 0;
					for ( ; it != position; ++it)
						_alloc.construct(&_vector_base[i++], *it);
					_alloc.construct(&_vector_base[i++], val);
					res = iterator(&_vector_base[i - 1]);
					for ( ; it != ite; ++it)
						_alloc.construct(&_vector_base[i++], *it);
					_delete_old(old_base);
					_mem_size = _mem_size * 2;
				}
				catch (std::bad_alloc & e)
				{
					_vector_base = old_base;
					throw e;
				}
			}
			_size++;
			return (res);
		}
		void insert(iterator position, size_type n, const value_type &val)
		{
			size_type i;

			if (_size + n > this->max_size())
				throw std::length_error("length_error");

			if (_size + n <= _mem_size)
			{
				i = _size + n - 1;
				while (position.operator->() != &_vector_base[i - n + 1])
					//todo Изменил position -> position.operator->()
				{
					_alloc.destroy(&_vector_base[i]);
					_alloc.construct(&_vector_base[i], _vector_base[i - n]);
					i--;
				}
				for (size_type j = 0; j < n; j++)
				{
					_alloc.destroy(&_vector_base[i]);
					_alloc.construct(&_vector_base[i--], val);
				}
			} else
			{
				pointer old_base;
				iterator it = this->begin();
				iterator ite = this->end();

				old_base = _vector_base;
				try
				{
					_vector_base = _alloc.allocate((_size + n) * 2);
					i = 0;
					for ( ; it != position; ++it)
						_alloc.construct(&_vector_base[i++], *it);
					for (size_type j = 0; j < n; j++)
						_alloc.construct(&_vector_base[i++], val);
					for ( ; it != ite; ++it)
						_alloc.construct(&_vector_base[i++], *it);
					_delete_old(old_base);
					_mem_size = (_size + n) * 2;
				}
				catch (std::bad_alloc & e)
				{
					_vector_base = old_base;
					throw e;
				}
			}
			_size += n;
		}
		template <class InputIterator>
		void insert(iterator position, InputIterator first, typename
		ft::enable_if<std::__is_input_iterator <InputIterator>::value,
		InputIterator>::type last)
		{
			pointer		old_base;
			iterator	current;
			iterator	current_end;
			size_type	i;
			size_type	count = std::abs(last - first);

			if (_size + count > this->max_size())
				throw std::length_error("length_error");

			if (_size + count + 1 < _mem_size)
			{
				current = this->end();
				i = _size + count - 1;

				while (current != position)
				{
					--current;
					_alloc.destroy(&_vector_base[i]);
					_alloc.construct(&_vector_base[i--], *current);
				}
				while (last != first)
				{
					--last;
					_alloc.destroy(&_vector_base[i]);
					_alloc.construct(&_vector_base[i--], *last);
				}
			} else
			{
				old_base = _vector_base;

				try
				{
					current = this->begin();
					current_end = this->end();
					i = 0;

					_vector_base = _alloc.allocate((_size + count) * 2);
					for ( ; current != position; ++current)
						_alloc.construct(&_vector_base[i++], *current);
					for ( ; first != last; ++first)
						_alloc.construct(&_vector_base[i++], *first);
					for ( ; position != current_end; ++position)
						_alloc.construct(&_vector_base[i++], *position);
					_delete_old(old_base);
					_mem_size = (_size + count) * 2;
				}
				catch (std::bad_alloc & e)
				{
					_vector_base = old_base;
					throw e;
				}
			}
			_size += count;
		}
		iterator erase(iterator position)
		{
			size_type i;
			iterator ite = this->end();

			i = std::abs(position - this->begin());
			if (position != ite)
				++position;
			for ( ; position != ite; ++position)
			{
				_alloc.destroy(&_vector_base[i]);
				_alloc.construct(&_vector_base[i], *position);
				i++;
			}
			_alloc.destroy(&_vector_base[i]);
			_size--;
			return (position);
		}
		iterator erase(iterator first, iterator last)
		{
			size_type count;
			size_type i;
			iterator ite = this->end();

			count = std::abs(last - first);
			i = std::abs(first - this->begin());
			for ( ; last != ite; ++last)
			{
				_alloc.destroy(&_vector_base[i]);
				_alloc.construct(&_vector_base[i++], *last);
			}
			_size -= count;
			while (count > 0)
			{
				_alloc.destroy(&_vector_base[i++]);
				count--;
			}
			return (first);
		}
		void swap(vector& x)
		{
			pointer tmp;

			tmp = this->_vector_base;
			this->_vector_base = x._vector_base;
			x._vector_base = tmp;
		}
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&_vector_base[i]);
			_size = 0;
		}

		// allocator
		allocator_type get_allocator() const
		{
			return (_alloc);
		}


	private:
		pointer			_vector_base;
		size_type		_size;
		size_type		_mem_size;
		allocator_type	_alloc;

		void	_delete_old(pointer old_vector)
		{
			for (size_type j = 0; j < _size; j++)
				_alloc.destroy(&old_vector[j]);
			if (_mem_size != 0)
				_alloc.deallocate(old_vector, _mem_size);
		}
		template<typename InputIterator>
		void	_copy(int start, InputIterator first, InputIterator last)
		{
			for ( ; first != last; ++first)
				_alloc.construct(&_vector_base[start++], *first);
		}
		void	_copy(int start, int count, value_type val)
		{
			for (int i = 0; i < count; i++)
				_alloc.construct(&_vector_base[start + i], val);
		}
		void	_copy(int start, int count, pointer src)
		{
			for (int i = 0; i < count; i++)
				_alloc.construct(&_vector_base[start + i], src[i]);
		}
	};

	// non-member functions overloads
	template <class T, class Alloc>
	bool operator== (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		if (lhs.size() == rhs.size())
		{
			for (size_t i = 0; i < lhs.size(); i++)
			{
				if (lhs[i] != rhs[i])
					return (false);
			}
			return (true);
		}
		return (false);
	}
	template <class T, class Alloc>
	bool operator!= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (!(lhs==rhs));
	}
	template <class T, class Alloc>
	bool operator< (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		size_t	i;

		i = 0;
		while (i < lhs.size() && i < rhs.size())
		{
			//todo lhs[i] < rhs[i] всегда true
			if (lhs[i] < rhs[i])
				return true;
			if (lhs[i] >= rhs[i])
				return (false);
			i++;
		}
		return (true);
	}
	template <class T, class Alloc>
	bool operator<= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (lhs < rhs || lhs == rhs);
	}
	template <class T, class Alloc>
	bool operator> (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs < lhs);
	}
	template <class T, class Alloc>
	bool operator>= (const vector<T,Alloc>& lhs, const vector<T,Alloc>& rhs)
	{
		return (rhs <= lhs);
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif //FT_CONTAINERS_VECTOR_HPP
