#pragma once

#include "dijkstra.hpp"

namespace algorithms {
namespace graph {

template<size_t SIZE>
std::array<size_t, SIZE> bellman_ford_distance(const graph_matrix<SIZE> &matrix,  size_t source);

} // namespace graph
} // namespace algorithms

#include "bellman_ford.cpp"