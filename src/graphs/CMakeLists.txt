cmake_minimum_required(VERSION 3.10)
project(graphs)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -Wextra")
set(CMAKE_CXX_STANDARD 17)

add_executable(graphs
        main.cpp
        dfs.hpp
        dijkstra.hpp
        bellman_ford.hpp
        node.hpp
        simple_node.hpp)