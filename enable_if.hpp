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
	struct is_iterator : public std::__is_input_iterator<T>
	{};

	template<typename T>
	struct __attribute__((unused)) is_input_iterator : public std::false_type{};
	template<>
	struct __attribute__((unused)) is_input_iterator<std::random_access_iterator_tag> : public
        std::true_type{};
	template<>
	struct __attribute__((unused)) is_input_iterator<std::bidirectional_iterator_tag> : public
	        std::true_type{};
	template<>
	struct __attribute__((unused)) is_input_iterator<std::forward_iterator_tag> : public std::true_type{};
	template<>
	struct __attribute__((unused)) is_input_iterator<std::input_iterator_tag> : public std::true_type{};

}

#endif //FT_CONTAINERS_ENABLE_IF_HPP
