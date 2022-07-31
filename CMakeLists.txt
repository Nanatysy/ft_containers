cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -std=c++98")

include_directories(${GTEST_INCLUDE_DIR})

include_directories(.)

add_executable(ft_containers_vector
        tmp.cpp
        vector.hpp
        pair.hpp
        enable_if.hpp
        iterator.hpp
        my_print.hpp
        compare.hpp)

#add_executable(ft_container_map
#        map.hpp
#        enable_if.hpp
#        pair.hpp
#        map_test.cpp)

add_executable(ft_pair
        pair_tmp.cpp
        pair.hpp)

add_executable(iterator
        test.cpp)

#add_executable(vector_test
#        Test/tests.cpp
#        Test/test_color.hpp
#        vector.hpp
#        enable_if.hpp
#        compare.hpp
#        iterator.hpp
#        )

add_executable(range.cpp
        map.hpp
        pair.hpp
        range.cpp
        )

add_executable(new_vector_test
        vector.hpp
        pair.hpp
        enable_if.hpp
        iterator.hpp
        compare.hpp
        tests/vector_test.cpp
        )

add_executable(set_test
        set.hpp
        map.hpp
        pair.hpp
        enable_if.hpp
        tests/set_test.cpp)

add_executable(ft_container_stack
        tests/stack_test.cpp
        stack.hpp
        enable_if.hpp
        my_print.hpp)

add_executable(std_container_stack
        tests/std_stack_test.cpp
        stack.hpp
        enable_if.hpp
        my_print.hpp)

add_executable(ft_container_vector
        tests/vector_test.cpp
        vector.hpp
        enable_if.hpp
        iterator.hpp)

add_executable(std_container_vector
        tests/std_vector_test.cpp
        vector.hpp
        enable_if.hpp
        iterator.hpp)

add_executable(ft_container_map
        map.hpp
        enable_if.hpp
        pair.hpp
        compare.hpp
        tests/map_test.cpp)

add_executable(std_container_map
        map.hpp
        enable_if.hpp
        pair.hpp
        compare.hpp
        tests/std_map_test.cpp)

add_executable(ft_container_set
        set.hpp
        enable_if.hpp
        pair.hpp
        compare.hpp
        map.hpp
        tests/set_test.cpp
        )

add_executable(std_container_set
        set.hpp
        enable_if.hpp
        pair.hpp
        compare.hpp
        map.hpp
        tests/std_set_test.cpp
        )