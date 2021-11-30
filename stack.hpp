//
// Created by Debby Willette on 10/26/21.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

#include <iostream>
#include "vector.hpp"

namespace ft {

	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
	public:
		typedef T value_type;
		typedef Container container_type;
		typedef size_t size_type;

		explicit stack (const container_type& ctnr = container_type()) : c(ctnr)
		{}

		virtual ~stack() {}

		bool empty() const
		{
			return (c.empty());
		}
		size_type size() const
		{
			return (c.size());
		}
		value_type& top()
		{
			return (c.back());
		}
		const value_type& top() const
		{
			return (c.back());
		}
		void push (const value_type& val)
		{
			c.push_back(val);
		}
		void pop()
		{
			c.pop_back();
		}

		template <class T1, class C1>
		friend bool operator== (const stack<T1,C1>& lhs, const stack<T1,C1>& rhs);
		template <class T1, class C1>
		friend bool operator!= (const stack<T1,C1>& lhs, const stack<T1,C1>&
		        rhs);
		template <class T1, class C1>
		friend bool operator<  (const stack<T1,C1>& lhs, const stack<T1,C1>&
		        rhs);
		template <class T1, class C1>
		friend bool operator<= (const stack<T1,C1>& lhs, const stack<T1,C1>&
		        rhs);
		template <class T1, class C1>
		friend bool operator>  (const stack<T1,C1>& lhs, const stack<T1,C1>&
		        rhs);
		template <class T1, class C1>
		friend bool operator>= (const stack<T1,C1>& lhs, const stack<T1,C1>&
		        rhs);

	protected:
		container_type	c;

	};

	template <class T, class Container>
	bool operator== (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c == rhs.c);
	}
	template <class T, class Container>
	bool operator!= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c != rhs.c);
	}
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c < rhs.c);
	}
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c <= rhs.c);
	}
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c > rhs.c);
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c >= rhs.c);
	}

};

#endif //FT_CONTAINERS_STACK_HPP
