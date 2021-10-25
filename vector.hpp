//
// Created by Debby Willette on 10/19/21.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

# include <iostream>

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

//		typedef typename reverse_iterator
//		typedef typename const_reverse_iterator
//		typedef typename difference_type
		typedef size_t size_type; // ?


//		template<class Distance = ptrdiff_t,
//				class Pointer = T*, class Reference = T&>
//		class iterator // TODO: random access iterator
//		{
//		public:
//
////			typedef T value_type;
////			typedef Distance difference_type;
////			typedef Pointer pointer;
////			typedef Reference reference;
//
//			typedef T value_type;
//			typedef ptrdiff_t difference_type;
//			typedef T* pointer;
//			typedef T& reference;
//
//			iterator() : _ptr(nullptr) {}
////			iterator(T *data) : _ptr(data) {}
//			iterator(const iterator & src)
//			{
//				*this = src;
//			}
//			virtual ~iterator() {}
//
//			iterator &operator=(const iterator<T> & src)
//			{
//				if (this == &src)
//					return (*this);
//
//				_ptr = src->_ptr;
//				return (*this);
//			}
//
//			bool operator==(const iterator<T> & src) const
//			{
//				return (this->_ptr == src->_ptr);
//			}
//			bool operator!=(const iterator<T> & src) const
//			{
//				return (this->_ptr != src->_ptr);
//			}
//			const T &operator*()
//			{
//				return (*_ptr);
//			}
//			const T &operator*() const
//			{
//				return (*_ptr);
//			}
//			T *operator->()
//			{
//				return (_ptr);
//			}
//			T *operator->() const
//			{
//				return (_ptr);
//			}
//			iterator<T> &operator++()
//			{
//				_ptr++;
//				return (*this);
//			}
//			iterator<T> &operator++(int)
//			{
//				iterator<T> tmp(*this);
//
//				++(*this);
//				return (tmp);
//			}
////			const T & operator*++(int)
////			{
////				T tmp = *_ptr;
////
////				*_ptr++;
////				return (tmp);
////			} //?
//			iterator<T> &operator--()
//			{
//				_ptr--;
//				return (*this);
//			}
//			iterator<T> &operator--(int)
//			{
//				iterator<T> tmp(*this);
//
//				--(*this);
//				return (tmp);
//			}
////			const T &operator*--(int)
////			{
////				T tmp = *_ptr;
////
////				*_ptr--;
////				return (tmp);
////			} //?
//			iterator<T> &operator+(int n) const
//			{
//				return (_ptr + n * difference_type);
//			}
//			iterator<T> &operator-(int n) const
//			{
//				return (_ptr - n * difference_type);
//			}
//			bool operator<(const iterator<T> & src) const
//			{
//				return (this->_ptr < src->_ptr);
//			}
//			bool operator>(const iterator<T> & src) const
//			{
//				return (this->_ptr > src->_ptr);
//			}
//			bool operator<=(const iterator<T> & src) const
//			{
//				return (*this < src || *this == src);
//			}
//			bool operator>=(const iterator<T> & src) const
//			{
//				return (*this > src || *this == src);
//			}
//			iterator<T> &operator+=(int n)
//			{
//				_ptr += n * difference_type ;
//				return (_ptr);
//			}
//			iterator<T> &operator-=(int n)
//			{
//				_ptr -= n * difference_type;
//				return (_ptr);
//			}
//			const T &operator[](size_t n)
//			{
//				return (*(_ptr + n * difference_type));
//			}
//			const T &operator[](size_t n) const
//			{
//				return (*(_ptr + n * difference_type));
//			}
//
//		private:
//			T* _ptr;
//		};

//		typedef typename vector<T, Alloc>::iterator iterator;
//		typedef typename vector<const T, Alloc>::iterator const_iterator;


		// constructor
		explicit vector(const allocator_type& alloc = allocator_type()) :
		_size(0), _mem_size(1), _alloc(alloc)
		{
			_array = _alloc.allocate(_mem_size);
		}
		explicit vector(size_type n, value_type& val = value_type(), const allocator_type& alloc = allocator_type()) :
						 _size(n), _mem_size(n * 2), _alloc(alloc) // TODO: doesn't work
		{
			size_t i;

			_array = _alloc.allocate(_mem_size);
			for (i = 0; i < n; i++)
				_alloc.construct(&_array[i], val);
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last, const allocator_type&
		alloc = allocator_type()) : _alloc(alloc)
		{

			if (first > last)
			{
				_size = 0;
				_mem_size = 2;
				_array = _alloc.allocate(_mem_size);
			}
			else
			{
				InputIterator tmp = first;
				size_t	count = 0;

				for( ; tmp != last; tmp++)
					count++;
				_size = count;
				_mem_size = count * 2;
				_array = _alloc.allocate(_mem_size);
				count = 0;
				for ( ; first != last; first++)
					_alloc.construct(&_array[count++], *first);
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
				_alloc.destroy(&_array[i]);
			_alloc.deallocate(_array, _mem_size);
		}

		// operator = overload
		vector<T, Alloc> & operator=(const vector<T, Alloc> & src)
		{
			if (this == &src)
				return (*this);

			for (size_t i = 0; i < _size; i++)
				_alloc.destroy(&_array[i]);
			_alloc.deallocate(_array, _mem_size);

			_size = src._size;
			_mem_size = src._mem_size;
			_alloc = src._alloc;
			_array = _alloc.allocate(_mem_size);
			for (size_t i = 0; i < _size; i++)
				_alloc.construct(&_array[i], src._array[i]);
		}

		// iterators
//		iterator begin();
//		const_iterator begin() const;
//		iterator end();
//		const_iterator end() const;
//		reverse_iterator rbegin();
//		const_reverse_iterator rbegin() const;
//		reverse_iterator rend();
//		const_reverse_iterator rend() const;

		// capacity
		size_type size() const
		{
			return (_size);
		}
		size_type max_size() const; // TODO: find max allocatable size
		void resize (size_type n, value_type val = value_type());
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

			tmp = _array;
			_array = _alloc.allocate(n);
			for (size_type i = 0; i < _size; i++)
				_alloc.construct(&_array[i], tmp[i]);

			for (size_type i = 0; i < _size; i++)
				_alloc.destroy(&tmp[i]);
			_alloc.deallocate(tmp, _mem_size);
			_mem_size = n;
		}

		// element access
		reference operator[] (size_type n)
		{
//			if (n < _size)
				return (_array[n]);
		}
		const_reference operator[] (size_type n) const
		{
			return (_array[n]);
		}
		reference at (size_type n) // TODO: out of range exception instead of std exc
		{
			if (n >= _size)
				throw std::exception();
			return (_array[n]);
		}
		const_reference at (size_type n) const
		{
			if (n >= _size)
				throw std::exception();
			return (_array[n]);
		}
		reference front()
		{
			return (_array[0]);
		}
		const_reference front() const
		{
			return (_array[0]);
		}
		reference back()
		{
			return (_array[_size - 1]);
		}
		const_reference back() const
		{
			return (_array[_size - 1]);
		}

		// modifiers
		template <class InputIterator>
		void assign (InputIterator first, InputIterator last);
		void assign (size_type n, const value_type& val);


	private:
		value_type		*_array;
		size_type		_size;
		size_type		_mem_size;
		allocator_type	_alloc;

	};

}

#endif //FT_CONTAINERS_VECTOR_HPP
