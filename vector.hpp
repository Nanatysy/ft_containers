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
	private:
		T *_array;
		size_t _size;
		size_t _mem_size;

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
//		private:
//			T* _ptr;
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
//			iterator(const interator<T> & src)
//			{
//				*this = src;
//			}
//			virtual ~iterator() {}
//
//			iterator &operator=(const iterator & src)
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
//		};

//		typedef typename vector<T, Alloc>::iterator iterator;
//		typedef typename vector<const T, Alloc>::iterator const_iterator;


		// constructor
		explicit vector(const allocator_type & alloc = allocator_type()) :
		_size(0), _mem_size(2)
		{
			_array = alloc.allocate(_mem_size);
		}
		explicit vector(size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()) :
						 _size(n), _mem_size(n * 2)
		{
			size_t i;

			_array = alloc.allocate(_mem_size);
			for (i = 0; i < n; i++)
				alloc.construct(&_array[i], val);
		}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type & alloc = allocator_type())
		{
			if (first > last)
			{
				_size = 0;
				_mem_size = 2;
				_array = alloc.allocate(_mem_size);
			}
			else
			{
				InputIterator tmp = first;
				size_t	count = 0;

				for( ; tmp != last; tmp++)
					count++;
				_size = count;
				_mem_size = count * 2;
				_array = alloc.allocate(_mem_size);
				count = 0;
				for ( ; first != last; first++)
					alloc.construct(&_array[count++], *first);
			}
		}
		vector(const vector<T, Alloc> & x)
		{
			*this = x;
		}

		// destructor
		virtual ~vector()
		{
			allocator_type & alloc = allocator_type();

			for (size_t i = 0; i < _size; i++)
				alloc.destroy(&_array[i]);
			alloc.deallocate(_array, _mem_size);
		}

		// operator = overload
		vector<T, Alloc> & operator=(const vector<T, Alloc> & src)
		{
			allocator_type& alloc = allocator_type();

			if (this == &src)
				return (*this);

			_size = src._size;
			_mem_size = src._mem_size;
			_array = alloc.allocate(_mem_size);
			for (size_t i = 0; i < _size; i++)
				alloc.construct(&_array[i], src._array[i]);
		}



	};

}

#endif //FT_CONTAINERS_VECTOR_HPP
