#pragma once

#include "dijkstra.hpp"

namespace algorithms {
namespace graph {

template<size_t SIZE>
std::array<int32_t, SIZE> bellman_ford_distance(const matrix_t<SIZE> &matrix,  size_t source, bool throw_if_cycle);

} // namespace graph
} // namespace algorithms

#include "bellman_ford.cpp"