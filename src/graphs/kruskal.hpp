#pragma once

#include "dijkstra.hpp"

#include <cstddef>
#include <array>

namespace algorithms {
namespace graph {

template<size_t SIZE>
matrix_t<SIZE> kruskal_mst(const matrix_t<SIZE> &matrix);

} // namespace graph
} // namespace algorithms

#include "kruskal.cpp"