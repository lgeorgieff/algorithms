#include "kruskal.hpp"

#include <utility>
#include <unordered_set>
#include <map>

namespace {
struct pair_hash {
  size_t operator()(const std::pair<size_t, size_t> &elem) const {
    return elem.first ^ elem.second;
  }
};

} // anonymous namespace

template<size_t SIZE>
algorithms::graph::matrix_t<SIZE> algorithms::graph::kruskal_mst(const algorithms::graph::matrix_t<SIZE> &matrix) {
  using edge = std::pair<size_t, size_t>;
  matrix_t<SIZE> mst{};

  std::multimap<int32_t, edge> edge_queue;
  for(size_t line{0}; line < SIZE; ++line) {
    for (size_t col{0}; col < SIZE; ++col) {
      if(matrix[line][col] != INFINITE) edge_queue.insert(std::pair(matrix[line][col], edge(line, col)));
    }
  }

  std::unordered_set<edge, pair_hash> mst_edges;
  mst_edges.reserve(SIZE - 1);

  while(mst_edges.size() < SIZE - 1) {
    mst_edges.insert(edge_queue.begin()->second);
    edge_queue.erase(edge_queue.begin());
  }

  return mst;
}