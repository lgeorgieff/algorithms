project(oop)

set(CMAKE_CXX_STANDARD 17)

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -Wall -pedantic -Wextra")

add_executable(oop main.cpp
        timed_base.cpp timed_base.hpp
        timed_a.cpp timed_a.hpp
        timed_b.cpp timed_b.hpp
        timed_queue.cpp timed_queue.hpp)