//
// Created by Debby Willette on 11/11/21.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

//TODO: const_reverse_iterator (no constructor)

namespace ft {

	template< class Iter >
	struct iterator_traits {
		typedef typename Iter::iterator_category iterator_category;
		typedef typename Iter::value_type value_type;
		typedef typename Iter::difference_type difference_type;
		typedef typename Iter::pointer pointer;
		typedef typename Iter::reference reference;
	};

	template< class T >
	struct iterator_traits<T*>
	{
		typedef std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef T* pointer;
		typedef T& reference;
	};

	template< class T >
	struct iterator_traits<const T*>
	{
		typedef std::random_access_iterator_tag iterator_category;
		typedef T value_type;
		typedef ptrdiff_t difference_type;
		typedef const T* pointer;
		typedef const T& reference;
	};

	template<class Iter>
	class _iterator
	{
	public:

		typedef Iter iterator_type;
		typedef typename ft::iterator_traits<Iter>::iterator_category iterator_category;
		typedef typename ft::iterator_traits<Iter>::value_type value_type;
		typedef typename ft::iterator_traits<Iter>::difference_type difference_type;
		typedef typename ft::iterator_traits<Iter>::pointer pointer;
		typedef typename ft::iterator_traits<Iter>::reference reference;

		_iterator() : _ptr(nullptr) {}
		explicit _iterator(Iter data) : _ptr(data) {}
		_iterator(const _iterator & src)
		{
			*this = src;
		}
		_iterator(_iterator<value_type *> iterator)
		{
			_ptr = iterator.operator->();
		}
		virtual ~_iterator() {}

		_iterator &operator=(const _iterator<Iter> & src)
		{
			if (this == &src)
				return (*this);

			_ptr = src._ptr;
			return (*this);
		}

		bool operator==(const _iterator<Iter> & src) const
		{
			return (this->_ptr == src._ptr);
		}
		bool operator!=(const _iterator<Iter> & src) const
		{
			return (this->_ptr != src._ptr);
		}
		reference operator*() const
		{
			return (*_ptr);
		}
		pointer operator->() const
		{
			return (_ptr);
		}
		_iterator<Iter> &operator++()
		{
			_ptr++;
			return (*this);
		}
		_iterator<Iter> operator++(int)
		{
			_iterator<Iter> tmp(*this);

			++(*this);
			return (tmp);
		}
		_iterator<Iter> &operator--()
		{
			_ptr--;
			return (*this);
		}
		_iterator<Iter> operator--(int)
		{
			_iterator<Iter> tmp(*this);

			--(*this);
			return (tmp);
		}
		_iterator<Iter> operator+(difference_type n) const
		{
			_iterator<Iter> tmp(_ptr + n);
			return (tmp);
		}
		friend _iterator<Iter> operator+(difference_type n, _iterator it)
		{
			return (it + n);
		}
		_iterator<Iter> operator-(difference_type n) const
		{
			_iterator<Iter> tmp(_ptr - n);
			return (tmp);
		}
		friend difference_type operator-(_iterator left, _iterator right)
		{
			return (left._ptr - right._ptr);
		}
		bool operator<(const _iterator<Iter> & src) const
		{
			return (this->_ptr < src._ptr);
		}
		bool operator>(const _iterator<Iter> & src) const
		{
			return (this->_ptr > src._ptr);
		}
		bool operator<=(const _iterator<Iter> & src) const
		{
			return (*this < src || *this == src);
		}
		bool operator>=(const _iterator<Iter> & src) const
		{
			return (*this > src || *this == src);
		}
		_iterator<Iter> &operator+=(difference_type n)
		{
			_ptr += n;
			return (*this);
		}
		_iterator<Iter> &operator-=(difference_type n)
		{
			_ptr -= n;
			return (*this);
		}
		reference operator[](difference_type n) const
		{
			return (*(_ptr + n));
		}

	private:
		iterator_type _ptr;
	};

	template<class Iter>
	class _reverse_iterator
	{
	public:
		typedef Iter iterator_type;
		typedef typename iterator_traits<Iter>::iterator_category
				iterator_category;
		typedef typename iterator_traits<Iter>::difference_type
				difference_type;
		typedef typename iterator_traits<Iter>::value_type value_type;
		typedef typename iterator_traits<Iter>::pointer pointer;
		typedef typename iterator_traits<Iter>::reference reference;

		_reverse_iterator() : _ptr() {}
		explicit _reverse_iterator(Iter position) : _ptr(position) {}
		_reverse_iterator(const _reverse_iterator & src)
		{
			*this = src;
		}
		_reverse_iterator(_reverse_iterator<_iterator < value_type *> > iterator)
		{
			_ptr = _iterator<const value_type *>(iterator.operator->());
		}
		virtual ~_reverse_iterator() {}

		_reverse_iterator & operator=(const _reverse_iterator & src)
		{
			if (this == &src)
				return (*this);

			_ptr = src._ptr;
			return (*this);
		}

		bool operator==(const _reverse_iterator<Iter> & src) const
		{
			return (this->_ptr == src._ptr);
		}
		bool operator!=(const _reverse_iterator<Iter> & src) const
		{
			return (this->_ptr != src._ptr);
		}
		reference operator*() const
		{
			return (*_ptr);
		}
		pointer operator->() const
		{
			return (_ptr.operator->());
		}
		_reverse_iterator<Iter> &operator++()
		{
			--_ptr;
			return (*this);
		}
		_reverse_iterator<Iter> operator++(int)
		{
			_reverse_iterator<Iter> tmp(*this);

			--(_ptr);
			return (tmp);
		}
		_reverse_iterator<Iter> &operator--()
		{
			++_ptr;
			return (*this);
		}
		_reverse_iterator<Iter> operator--(int)
		{
			_reverse_iterator<Iter> tmp(*this);

			++(_ptr);
			return (tmp);
		}
		_reverse_iterator<Iter> operator+(difference_type n) const
		{
			_reverse_iterator<Iter> tmp(_ptr - n);
			return (tmp);
		}
		friend _reverse_iterator<Iter> operator+(difference_type n, _reverse_iterator it)
		{
			return (n + it._ptr);
		}
		_reverse_iterator<Iter> operator-(difference_type n) const
		{
			_reverse_iterator<Iter> tmp(_ptr + n);
			return (tmp);
		}
		friend difference_type operator-(_reverse_iterator left, _reverse_iterator right)
		{
			return (left._ptr - right._ptr);
		}
		bool operator<(const _reverse_iterator<Iter> & src) const
		{
			return (this->_ptr > src._ptr);
		}
		bool operator>(const _reverse_iterator<Iter> & src) const
		{
			return (this->_ptr < src._ptr);
		}
		bool operator<=(const _reverse_iterator<Iter> & src) const
		{
			return (!(*this > src));
		}
		bool operator>=(const _reverse_iterator<Iter> & src) const
		{
			return (!(*this < src));
		}
		_reverse_iterator<Iter> &operator+=(difference_type n)
		{
			_ptr -= n;
			return (*this);
		}
		_reverse_iterator<Iter> &operator-=(difference_type n)
		{
			_ptr += n;
			return (*this);
		}
		reference operator[](difference_type n) const
		{
			return (*(_ptr - n));
		}

	private:
		iterator_type _ptr;
	};

}

#endif //FT_CONTAINERS_ITERATOR_HPP
