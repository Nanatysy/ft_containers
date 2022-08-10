//
// Created by Debby Willette on 11/10/21.
//

#ifndef FT_CONTAINERS_ENABLE_IF_HPP
#define FT_CONTAINERS_ENABLE_IF_HPP

namespace ft {

	template <bool, typename T = void>
	struct enable_if
	{};

	template <typename T>
	struct enable_if<true, T>
	{
		typedef T type;
	};


	template<typename T>
	struct is_input_iterator : public std::false_type{};
	template<>
	struct is_input_iterator<std::random_access_iterator_tag> : public
        std::true_type{};
	template<>
	struct is_input_iterator<std::bidirectional_iterator_tag> : public
	        std::true_type{};
	template<>
	struct is_input_iterator<std::forward_iterator_tag> : public std::true_type{};
	template<>
	struct is_input_iterator<std::input_iterator_tag> : public std::true_type{};

	template<class T, class U = typename T::iterator_category>
	struct is_iterator : public ft::is_input_iterator<U>
	{};

}

#endif //FT_CONTAINERS_ENABLE_IF_HPP
