#pragma once

#include <cstddef>
#include <array>

namespace algorithms {
namespace graph {

const int32_t INFINITE{std::numeric_limits<int32_t >::max()};

template<size_t SIZE>
using matrix_t = std::array<std::array<int32_t, SIZE>, SIZE>;

template<size_t SIZE>
std::array<int32_t, SIZE> dijkstra_distance(const matrix_t<SIZE> &matrix,  size_t source);

} // namespace graph
} // graph

#include "dijkstra.cpp"