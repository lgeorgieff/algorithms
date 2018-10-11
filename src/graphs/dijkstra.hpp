#pragma once

#include <cstddef>
#include <array>
#include <iostream>
#include <vector>
#include <utility>

namespace algorithms {
namespace graph {

const int32_t INFINITE{std::numeric_limits<int32_t >::max()};

template<size_t SIZE>
using matrix_t = std::array<std::array<int32_t, SIZE>, SIZE>;

template<size_t SIZE>
class graph_t {
  using link_t = std::pair<size_t, int32_t >;
 public:
  explicit graph_t(const matrix_t<SIZE> &matrix);
  graph_t() = default;
  graph_t(const graph_t &) = default;
  graph_t(graph_t &&) = default;
  graph_t &operator=(const graph_t &) = default;
  graph_t &operator=(graph_t &&) = default;
  ~graph_t() noexcept = default;

  void add_edge(size_t from, size_t to, int32_t weight);
  const std::vector<link_t> &links(size_t node) const noexcept;
  size_t size() const noexcept;
  void print(std::ostream &out, unsigned short item_width = 3) const;
  matrix_t<SIZE> to_matrix() const;
  std::array<int32_t, SIZE> dijkstra_distance(size_t source) const;

 private:
  std::array<std::vector<link_t>, SIZE> links_;
};

template<size_t SIZE>
std::array<int32_t, SIZE> dijkstra_distance(const matrix_t<SIZE> &matrix,  size_t source);

template<size_t SIZE>
void print_matrix(std::ostream &out, const matrix_t<SIZE> &graph, unsigned short item_width = 3);

} // namespace graph
} // graph

#include "dijkstra.cpp"