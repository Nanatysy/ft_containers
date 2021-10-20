//
// Created by Debby Willette on 10/19/21.
//

#ifndef FT_CONTAINERS_VECTOR_HPP
#define FT_CONTAINERS_VECTOR_HPP

# include <iostream>

namespace ft {

	template < class T, class Alloc = std::allocator<T> >
	class vector<T>
	{
	private:


	public:
		typedef typename T value_type;
		typedef typename Alloc allocator_type;
		typedef typename allocator_type::reference reference;
		typedef typename allocator_type::const_reference const_reference;
		typedef typename allocator_type::pointer pointer;
		typedef typename allocator_type::const_pointer const_pointer;

//		typedef typename reverse_iterator
//		typedef typename const_reverse_iterator
//		typedef typename difference_type
//		typedef typename size_type


		template<class T, class Distance = ptrdiff_t,
				class Pointer = T*, class Reference = T&>
		class iterator<T> // TODO: random access iterator
		{
		private:
			T* _ptr;
		public:

			typedef typename T value_type;
			typedef typename Distance difference_type;
			typedef typename Pointer pointer;
			typedef typename Reference reference;

			iterator() : _ptr(nullptr) {}
//			iterator(T *data) : _ptr(data) {}
			iterator(const interator<T> & src)
			{
				*this = src;
			}
			virtual ~iterator() {}

			iterator & operator=(const iterator & src)
			{
				if (this == &src)
					return (*this);

				_ptr = src->_ptr;
				return (*this);
			}

			bool operator==(const iterator<T> & src) const
			{
				return (this->_ptr == src->_ptr);
			}
			bool operator!=(const iterator<T> & src) const
			{
				return (this->_ptr != src->_ptr);
			}
			T &operator*()
			{
				return (*_ptr);
			}
			T &operator*() const
			{
				return (*_ptr);
			}
			T *operator->()
			{
				return (_ptr);
			}
			T *operator->() const
			{
				return (_ptr);
			}
			iterator &operator++()
			{
				_ptr++;
				return (*this);
			}
			iterator &operator++(int)
			{
				iterator<T> tmp(*this);

				++(*this);
				return (tmp);
			}
			iterator &operator--()
			{
				_ptr--;
				return (*this);
			}
			iterator &operator--(int)
			{
				iterator<T> tmp(*this);

				--(*this);
				return (tmp);
			}
			bool operator<(const iterator<T> & src) const
			{
				return (this->_ptr < src->_ptr);
			}
			bool operator>(const iterator<T> & src) const
			{
				return (this->_ptr > src->_ptr);
			}
			bool operator<=(const iterator<T> & src) const
			{
				return (*this < src || *this == src);
			}
			bool operator>=(const iterator<T> & src) const
			{
				return (*this > src || *this == src);
			}

		};

		typedef typename vector<T>::iterator iterator;
		typedef typename vector<const T>::iterator const_iterator;


		// constructor
		explicit vector(const allocator_type& alloc = allocator_type()) {}
		explicit vector(size_type n, const value_type& val = value_type(),
						 const allocator_type& alloc = allocator_type()) {}
		template <class InputIterator>
		vector(InputIterator first, InputIterator last,
				const allocator_type& alloc = allocator_type()) {}
		vector(const vector<T> & x) {}

		// destructor
		virtual ~vector() {}

		// operator = overload
		vector<T> & operator=(const vector<T> & src) {}



	};

}

#endif //FT_CONTAINERS_VECTOR_HPP
