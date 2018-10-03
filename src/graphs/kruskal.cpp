#include "kruskal.hpp"

#include <utility>
#include <unordered_set>
#include <map>

template<size_t SIZE>
algorithms::graph::matrix_t<SIZE> algorithms::graph::kruskal_mst(const algorithms::graph::matrix_t<SIZE> &matrix) {
  using edge = std::pair<size_t, size_t>;
  matrix_t<SIZE> mst{};

  std::multimap<int32_t, edge> edge_queue;
  for(size_t line{0}; line < SIZE; ++line) {
    for (size_t col{0}; col < SIZE; ++col) {
      if(matrix[line][col] != INFINITE && line != col) edge_queue.insert(std::pair(matrix[line][col], edge(line, col)));
    }
  }

  std::unordered_set<size_t> mst_vertices;
  mst_vertices.reserve(SIZE);

  while(mst_vertices.size() < SIZE) {
    auto edge{edge_queue.begin()};
    if(mst_vertices.find(edge->second.first) == mst_vertices.end() || mst_vertices.find(edge->second.second) == mst_vertices.end()) {
      mst[edge->second.first][edge->second.second] = matrix[edge->second.first][edge->second.second];
      mst[edge->second.second][edge->second.first] = matrix[edge->second.second][edge->second.first];
      mst_vertices.insert(edge->second.first);
      mst_vertices.insert(edge->second.second);
    }
    edge_queue.erase(edge);
  }

  return mst;
}