#pragma once

#include "dijkstra.hpp"

#include <cstddef>
#include <array>

namespace algorithms {
namespace graph {

template<size_t SIZE>
matrix_t<SIZE> kruskal_mst(const matrix_t<SIZE> &matrix);

template<size_t SIZE>
class disjoint_set {
 public:
  disjoint_set();
  disjoint_set(const disjoint_set &) = default;
  disjoint_set(disjoint_set &&) noexcept = default;
  disjoint_set &operator=(const disjoint_set &) = default;
  disjoint_set &operator=(disjoint_set &&) noexcept = default;
  ~disjoint_set() noexcept = default;

  size_t find_parent(size_t node) noexcept;
  bool merge(size_t node1, size_t node2) noexcept;

 private:
  std::array<size_t, SIZE> parents_;
  std::array<size_t, SIZE> ranks_;
};

} // namespace graph
} // namespace algorithms

#include "kruskal.cpp"