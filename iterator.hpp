//
// Created by Debby Willette on 11/11/21.
//

#ifndef FT_CONTAINERS_ITERATOR_HPP
#define FT_CONTAINERS_ITERATOR_HPP

namespace ft {

//	struct input_iterator_tag {};
//	struct output_iterator_tag {};
//	struct forward_iterator_tag : public input_iterator_tag {};
//	struct bidirectional_iterator_tag : public forward_iterator_tag {};
//	struct random_access_iterator_tag : public bidirectional_iterator_tag {};

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
		typedef T* pointer;
		typedef T& reference;
	};


//	template<class Category, class T, class Distance = std::ptrdiff_t,
//			class Pointer = T*, class Reference = T&>
//	class iterator
//	{
//	public:
//		typedef Category iterator_category;
//		typedef T value_type;
//		typedef Distance difference_type;
//		typedef Pointer pointer;
//		typedef Reference reference;
//	};

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
		_iterator(Iter data) : _ptr(data) {}
		_iterator(const _iterator & src)
		{
			*this = src;
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
		const reference operator*()
		{
			return (*_ptr);
		}
		const reference operator*() const
		{
			return (*_ptr);
		}
		pointer operator->()
		{
			return (_ptr);
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
		_iterator<Iter> &operator++(int)
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
		_iterator<Iter> &operator--(int)
		{
			_iterator<Iter> tmp(*this);

			--(*this);
			return (tmp);
		}
		_iterator<Iter> &operator+(difference_type n) const
		{
			return (_ptr + n);
		}
		_iterator<Iter> &operator-(difference_type n) const
		{
			return (_ptr - n);
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
			return (_ptr);
		}
		_iterator<Iter> &operator-=(difference_type n)
		{
			_ptr -= n;
			return (_ptr);
		}
		const reference operator[](difference_type n)
		{
			return (*(_ptr + n));
		}
		const reference operator[](difference_type n) const
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
		const reference operator*()
		{
			return (*_ptr);
		}
		const reference operator*() const
		{
			return (*_ptr);
		}
		pointer operator->()
		{
			return (_ptr);
		}
		pointer operator->() const
		{
			return (_ptr);
		}
		_reverse_iterator<Iter> &operator++()
		{
			_ptr--;
			return (*this);
		}
		_reverse_iterator<Iter> &operator++(int)
		{
			_iterator<Iter> tmp(*this);

			--(*this);
			return (tmp);
		}
		_reverse_iterator<Iter> &operator--()
		{
			_ptr++;
			return (*this);
		}
		_reverse_iterator<Iter> &operator--(int)
		{
			_iterator<Iter> tmp(*this);

			++(*this);
			return (tmp);
		}
		_reverse_iterator<Iter> &operator+(difference_type n) const
		{
			return (_ptr - n);
		}
		_reverse_iterator<Iter> &operator-(difference_type n) const
		{
			return (_ptr + n);
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
			return (_ptr);
		}
		_reverse_iterator<Iter> &operator-=(difference_type n)
		{
			_ptr += n;
			return (_ptr);
		}
		const reference operator[](difference_type n)
		{
			return (*(_ptr + n));
		}
		const reference operator[](difference_type n) const
		{
			return (*(_ptr + n));
		}

	private:
		iterator_type _ptr;
	};

}

#endif //FT_CONTAINERS_ITERATOR_HPP