cmake_minimum_required(VERSION 3.10)
project(sorting)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

add_executable(sorting main.cpp sorting.hpp)