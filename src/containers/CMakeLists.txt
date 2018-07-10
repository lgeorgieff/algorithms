cmake_minimum_required(VERSION 3.10)
project(containers)

set(CMAKE_CXX_STANDARD 17)

add_executable(containers main.cpp containers.hpp containers.cpp)