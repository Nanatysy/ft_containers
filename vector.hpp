//
// Created by Debby Willette on 10/19/21.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

# include <iostream>
# include "iterator.hpp"
# include "enable_if.hpp"


// TODO: проверить изменение _size после каждого метода влияющего н аэту
//  переменную, проверить входит ли Last в диапазон, кидать исключение если
//  не отработал allocator

// insert(позиция, диапазон) не совпадает со стандартным


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
		explicit vector(const allocator_type& alloc = allocator_type()) :
		_size(0), _mem_size(1), _alloc(alloc)
		{
			_vector_base = _alloc.allocate(_mem_size);
		}
//		explicit vector(size_type n, const value_type& val = value_type(),
//						const allocator_type& alloc = allocator_type()) :
//						 _size(n), _mem_size(n * 2), _alloc(alloc)
//		{
//			size_t i;
//
//			_vector_base = _alloc.allocate(_mem_size);
//			for (i = 0; i < n; i++)
//				_alloc.construct(&_vector_base[i], val);
//		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type&
		alloc = allocator_type()) :
		_alloc(alloc)
		{
			try
			{
				if (first > last)
				{
					_size = 0;
					_mem_size = 2;
					_vector_base = _alloc.allocate(_mem_size);
				} else
				{
					size_t count = _count_range(first, last);

//				for( ; tmp != last; tmp++)
//					count++;
					_size = count;
					_mem_size = count * 2;
					_vector_base = _alloc.allocate(_mem_size);
					count = 0;
					for (; first != last; first++)
						_alloc.construct(&_vector_base[count++], *first);
				}
			}
			catch (__unused std::bad_alloc & e)
			{
				throw std::bad_alloc();
			}

		}
		vector(const vector<T, Alloc> & x)
		{
			*this = x;
		}

		// destructor
		virtual ~vector()
		{
			for (size_t i = 0; i < _size; i++)
				_alloc.destroy(&_vector_base[i]);
			_alloc.deallocate(_vector_base, _mem_size);
		}

		// operator = overload
		vector<T, Alloc> & operator=(const vector<T, Alloc> & src)
		{
			if (this == &src)
				return (*this);

			for (size_t i = 0; i < _size; i++)
				_alloc.destroy(&_vector_base[i]);
			_alloc.deallocate(_vector_base, _mem_size);

			_size = src._size;
			_mem_size = src._mem_size;
			_alloc = src._alloc;
			_vector_base = _alloc.allocate(_mem_size); // exception???
			for (size_t i = 0; i < _size; i++)
				_alloc.construct(&_vector_base[i], src._vector_base[i]);
			return (*this);
		}

		// iterators
		iterator begin()
		{
			return (iterator(&_vector_base[0]));
		}
		const_iterator begin() const
		{
			return (iterator(&_vector_base[0]));
		}
		iterator end()
		{
			return (iterator(&_vector_base[_size]));
		}
		const_iterator end() const
		{
			return (iterator(&_vector_base[_size]));
		}
		reverse_iterator rbegin()
		{
			return (reverse_iterator(this->end()));
		}
		const_reverse_iterator rbegin() const
		{
			return (reverse_iterator(this->end()));
		}
		reverse_iterator rend()
		{
			return (reverse_iterator(this->begin()));
		}
		const_reverse_iterator rend() const
		{
			return (reverse_iterator(this->begin()));
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
		void resize (size_type n, value_type val = value_type())
		{
			if (n < _size)
			{
				for (size_type i = n; i < _size; i++)
					_alloc.destroy(&_vector_base[i]);
			}
			else if (n < _mem_size)
			{
				for (size_type i = _size; i < n; i++)
					_alloc.construct(&_vector_base[i], val);
			}
			else
			{
				value_type *tmp;

				tmp = _vector_base;
				_vector_base = _alloc.allocate(n * 2);
				for (size_type i = 0; i < n; i++)
				{
					if (i < _size)
						_alloc.construct(&_vector_base[i], tmp[i]);
					else
						_alloc.construct(&_vector_base[i], val);
				}

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&tmp[i]);
				_alloc.deallocate(tmp, _mem_size);
				_mem_size = n * 2;
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
		void reserve (size_type n)
		{
			value_type *tmp;

			if (n <= _mem_size)
				return ;

			tmp = _vector_base;
			_vector_base = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_vector_base[i], tmp[i]);

			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&tmp[i]);
			_alloc.deallocate(tmp, _mem_size);
			_mem_size = n;
		}

		// element access
		reference operator[] (size_type n)
		{
				return (_vector_base[n]);
		}
		const_reference operator[] (size_type n) const
		{
			return (_vector_base[n]);
		}
		reference at (size_type n)
		{
			if (n >= _size)
				throw std::out_of_range("out_of_range");
			return (_vector_base[n]);
		}
		const_reference at (size_type n) const
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
//		template <class InputIterator>
//		void assign (InputIterator first, InputIterator last) // TODO: check
		// if  first is in cur vector, enable if(only for iterators)
//		{
//			size_type	i;
//			InputIterator	it_tmp;
//
//			i = 0;
//			it_tmp = first;
//			while (it_tmp++ != last)
//				i++;
//			if (i < _mem_size)
//		}
		void assign (size_type n, const value_type& val)
		{
			if (n < _mem_size)
			{
				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&_vector_base[i]);
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(&_vector_base[i], val);
				}
				_size = n;
			}
			else
			{
				value_type *tmp;

				tmp = _vector_base;
				_vector_base = _alloc.allocate(n * 2);
				for (size_type i = 0; i < n; i++)
				{
					_alloc.construct(&_vector_base[i], val);
				}

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&tmp[i]);
				_alloc.deallocate(tmp, _mem_size);
				_mem_size = n * 2;
				_size = n;
			}
		}
		void push_back (const value_type& val)
		{
			if (_size >= _mem_size - 1)
			{
				value_type *tmp;

				tmp = _vector_base;
				_vector_base = _alloc.allocate(_size * 2);
				for (size_type i = 0; i < _size; i++)
				{
					_alloc.construct(&_vector_base[i], tmp[i]);
				}

				for (size_type i = 0; i < _size; i++)
					_alloc.destroy(&tmp[i]);
				_alloc.deallocate(tmp, _mem_size);
				_mem_size = _size * 2;
			}
			_alloc.construct(&_vector_base[_size++], val);
		}
		void pop_back()
		{
			if (!this->empty())
				_alloc.destroy(&_vector_base[--_size]);
		}
		iterator insert (iterator position, const value_type& val)
		{
			iterator res;

//			if (position < this->begin() || position > this->end()) //UB

			if (_size + 1 < _mem_size)
			{
//				std::cout << "not reallocated" << std::endl;

				int i;

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
				_size++;
			}
			else
			{

//				std::cout << "reallocated" << std::endl;

				int i;
				pointer tmp;
				iterator it = this->begin();
				iterator ite = this->end();

				tmp = _vector_base;
				_vector_base = _alloc.allocate(_mem_size * 2); // exception??
				i = 0;
				for ( ; it != position; ++it)
					_alloc.construct(&_vector_base[i++], *it);
				_alloc.construct(&_vector_base[i++], val);
				res = iterator(&_vector_base[i - 1]);
				for ( ; it != ite; ++it)
					_alloc.construct(&_vector_base[i++], *it);
				for (size_type j = 0; j < _size; j++)
					_alloc.destroy(&tmp[j]);
				_alloc.deallocate(tmp, _mem_size);
				_size++;
				_mem_size = _mem_size * 2;
			}
			return (res);
		}
		void insert (iterator position, size_type n, const value_type& val)
		{
//			if (position < this->begin() || position > this->end()) // UB

			if (_size + n < _mem_size)
			{
				std::cout << "not reallocated" << std::endl;

				int i;

				i = _size + n - 1;
				while (position != &_vector_base[i - n + 1])
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
				_size += n;
			}
			else
			{

				std::cout << "reallocated" << std::endl;

				int i;
				pointer old_base;
				iterator it = this->begin();
				iterator ite = this->end();

				old_base = _vector_base;
				_vector_base = _alloc.allocate((_size + n) * 2); // exception??
				i = 0;
				for ( ; it != position; ++it)
					_alloc.construct(&_vector_base[i++], *it);
				for (size_type j = 0; j < n; j++)
					_alloc.construct(&_vector_base[i++], val);
				for ( ; it != ite; ++it)
					_alloc.construct(&_vector_base[i++], *it);

//				for (size_type j = 0; j < _size; j++)
//					_alloc.destroy(&old_base[j]);
//				_alloc.deallocate(old_base, _mem_size);
				_delete_old(old_base);

				_size += n;
				_mem_size = _size * 2;
			}
		}
//		template <class InputIterator>
//		void insert (iterator position, InputIterator first, InputIterator
//		last) // enable if (iterators only)
//		{
//			pointer		old_base;
//			iterator	current;
//			iterator	current_end;
//			size_type	i;
//			size_type	count = _count_range(first, last);
//
//			if (_size + count + 1 < _mem_size)
//			{
//
//				std::cout << "not reallocated" << std::endl;
//
//				current = this->end();
//				i = _size + count - 1;
//
//				while(current != position)
//				{
//					--current;
//					_alloc.destroy(&_vector_base[i]);
//					_alloc.construct(&_vector_base[i--], *current);
//				}
//				while (last != first)
//				{
//					--last;
//					_alloc.destroy(&_vector_base[i]);
//					_alloc.construct(&_vector_base[i--], *last);
//				}
//				_size += count;
//			}
//			else
//			{
//
//				std::cout << "reallocated" << std::endl;
//
//				old_base = _vector_base;
//				current = this->begin();
//				current_end = this->end();
//
//				i = 0;
//
//				_vector_base = _alloc.allocate((_size + count) * 2);
//
//				for ( ; current != position; ++current)
//					_alloc.construct(&_vector_base[i++], *current);
//				for ( ; first != last; ++first)
//					_alloc.construct(&_vector_base[i++], *first);
//				for ( ; position != current_end; ++position)
//					_alloc.construct(&_vector_base[i++], *position);
//
//				_delete_old(old_base);
//
//				_size += count;
//				_mem_size = _size * 2;
//			}
//
//		}
		iterator erase (iterator position)
		{
//			if (position <> this) // UB

			size_type i;
			iterator ite = this->end();

			i = _count_range(this->begin(), position);
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
			return(position);
		}
		iterator erase (iterator first, iterator last)
		{
			size_type count;
			size_type i;
			iterator ite = this->end();

			count = _count_range(first, last);
			i = _count_range(this->begin(), first);
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
		void swap (vector& x);
		void clear()
		{
			for (size_type i = 0; i < _size; i++)
			{
				_alloc.destroy(&_vector_base[i]);
			}
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

		template<typename InputIterator>
		size_type _count_range(InputIterator first, InputIterator last)
		{
			size_type count;

			count = 0;
			for ( ; first != last; ++first)
				count++;
			return (count);
		}
		void	_delete_old(pointer old_vector)
		{
			for (size_type j = 0; j < _size; j++)
				_alloc.destroy(&old_vector[j]);
			_alloc.deallocate(old_vector, _mem_size);
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
			if (lhs[i] > rhs[i])
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
		return (lhs > rhs || lhs == rhs);
	}

	template <class T, class Alloc>
	void swap (vector<T,Alloc>& x, vector<T,Alloc>& y)
	{
		x.swap(y);
	}

}

#endif //FT_CONTAINERS_VECTOR_HPP
