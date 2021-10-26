//
// Created by Debby Willette on 10/26/21.
//

#ifndef FT_CONTAINERS_STACK_HPP
#define FT_CONTAINERS_STACK_HPP

namespase ft
{

	template <typename T, typename Container = ft::vector<T> >
	class stack
	{
	public:
		typedef value_type T;
		typedef container_type Container;
		typedef size_type size_t;

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
		return (!(lhs.c == rhs.c));
	}
	template <class T, class Container>
	bool operator<  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c< rhs.c)
	}
	template <class T, class Container>
	bool operator<= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c<= rhs.c)
	}
	template <class T, class Container>
	bool operator>  (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c> rhs.c)
	}
	template <class T, class Container>
	bool operator>= (const stack<T,Container>& lhs, const stack<T,Container>& rhs)
	{
		return (lhs.c>= rhs.c)
	}

};

#endif //FT_CONTAINERS_STACK_HPP
