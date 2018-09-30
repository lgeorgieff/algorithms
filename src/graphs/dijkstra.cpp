#pragma once

#include "dijkstra.hpp"
#include <map>
#include <utility>
#include <limits>
#include <queue>

template<size_t SIZE>
std::array<size_t, SIZE> algorithms::graph::dijkstra_distance(const graph_matrix<SIZE> &matrix,
    size_t source) {
  if(source >= SIZE) throw std::out_of_range{"source index is out of graph's range"};

  std::array<size_t, SIZE> distances;
  for(auto iter{distances.begin()}; iter < distances.end(); ++iter) *iter = INFINITE;
  distances[source] = 0;

  using pair_t = std::pair<size_t, size_t>;
  std::priority_queue<pair_t, std::vector<pair_t>, std::greater<pair_t>> priority_queue;
  priority_queue.push(pair_t(0, source));

  while(!priority_queue.empty()) {
    auto next = priority_queue.top();
    priority_queue.pop();

    auto links{matrix[next.second]};
    for(size_t other_node{0}; other_node < links.size(); ++other_node) {
      // First check for INFINITE to avoid overflows
      if(distances[next.second] != INFINITE && matrix[next.second][other_node] != INFINITE &&
          distances[other_node] > distances[next.second] + matrix[next.second][other_node]) {
        distances[other_node] = distances[next.second] + matrix[next.second][other_node];
        priority_queue.push(pair_t(distances[other_node], other_node));
      }
    }
  }

  return distances;
}