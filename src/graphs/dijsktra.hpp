#pragma once

#include <cstddef>
#include <array>

namespace algorithms {
namespace graph {

const size_t INFINITE{std::numeric_limits<size_t>::max()};

template<size_t SIZE>
using graph_matrix = std::array<std::array<size_t, SIZE>, SIZE>;

template<size_t SIZE>
std::array<size_t, SIZE> dijkstra_distance(const graph_matrix<SIZE> &matrix,  size_t source);

} // namespace graph
} // graph

#include "dijsktra.cpp"