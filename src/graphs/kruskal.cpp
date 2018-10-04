#pragma once

#include "kruskal.hpp"

#include <utility>
#include <unordered_set>
#include <map>
#include <algorithm>

template<size_t SIZE>
algorithms::graph::disjoint_set<SIZE>::disjoint_set() :parents_{}, ranks_{} {
  for(size_t idx{0}; idx < SIZE; ++idx) parents_[idx] = idx;
}

template<size_t SIZE>
size_t algorithms::graph::disjoint_set<SIZE>::find_parent(size_t node) noexcept {
  if(parents_[node] != node) {
    parents_[node] = find_parent(parents_[parents_[node]]);
    return parents_[node];
  }
  return parents_[node];
}

template<size_t SIZE>
bool algorithms::graph::disjoint_set<SIZE>::merge(size_t node1, size_t node2) noexcept {
  auto parent1{find_parent(node1)}, parent2{find_parent(node2)};
  if(parent1 == parent2) return false;

  if(ranks_[parent1] > ranks_[parent2]) parents_[parent2] = parents_[parent1];
  else parents_[parent1] = parents_[parent2];

  if(ranks_[parent1] == ranks_[parent2]) ++ranks_[std::max(parent1, parent2)];

  return true;
}

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

  disjoint_set<SIZE> node_sets;
  size_t mst_size{0};

  while(mst_size < SIZE - 1) {
    auto edge{edge_queue.begin()};
    if(node_sets.merge(edge->second.first, edge->second.second)) {
      mst[edge->second.first][edge->second.second] = matrix[edge->second.first][edge->second.second];
      mst[edge->second.second][edge->second.first] = matrix[edge->second.second][edge->second.first];
      ++mst_size;
    }
    edge_queue.erase(edge);
  }

  return mst;
}