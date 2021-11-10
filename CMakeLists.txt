cmake_minimum_required(VERSION 3.20)
project(ft_containers)

set(CMAKE_CXX_STANDARD 98)

set(CMAKE_CXX_FLAGS "-Wall -Werror -Wextra -std=c++98")

include_directories(.)

add_executable(ft_containers
        tmp.cpp
        vector.hpp
        stack.hpp
        map.hpp
        pair.hpp
        my_print.hpp)

add_executable(ft_pair
        pair_tmp.cpp
        pair.hpp)