cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_CXX_STANDARD 11)

#set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -std=c++98")

include_directories(.)

add_executable(ft_containers_vector
        tmp.cpp
        vector.hpp
        pair.hpp
        enable_if.hpp
        iterator.hpp
        my_print.hpp
        compare.hpp)

add_executable(ft_container_stack
        stack_test.cpp
        stack.hpp
        enable_if.hpp
        my_print.hpp
        )

add_executable(ft_container_map
        map.hpp
        enable_if.hpp
        pair.hpp
        map_test.cpp)

add_executable(ft_pair
        pair_tmp.cpp
        pair.hpp)

add_executable(iterator
        test.cpp)

add_executable(vector_test
        Test/tests.cpp
        Test/test_color.hpp
        vector.hpp
        enable_if.hpp
        compare.hpp
        iterator.hpp
        )

#add_executable(acid
#        acid.cpp)
