#pragma once

#include "dijkstra.hpp"
#include <map>
#include <utility>
#include <limits>

namespace {
using algorithms::graph::INFINITE;

template<size_t SIZE>
std::map<size_t, size_t> find_direct_neighbours(const algorithms::graph::graph_matrix<SIZE> &matrix,
    size_t node, size_t node_distance, const std::map<size_t, size_t> &queue) {
  std::map<size_t, size_t> result;
  auto row{matrix[node]};
  for(size_t current_node{0}; current_node < row.size(); ++current_node) {
    auto node_in_queue{queue.find(current_node)};
    if(row[current_node] != INFINITE && current_node != node && node_in_queue != queue.cend()) {
      result[current_node] = std::min(node_in_queue->second, row[current_node] + node_distance);
    }
  }
  return result;
}

size_t find_min_node(const std::map<size_t, size_t> &queue) {
  size_t node{0}, min{INFINITE};
  for(auto const &entry : queue) {
    if(entry.second <= min) {
      node = entry.first;
      min = entry.second;
      if(min == 0) return node;
    }
  }
  return node;
}
} // anonymous namespace

template<size_t SIZE>
std::array<size_t, SIZE> algorithms::graph::dijkstra_distance(const graph_matrix<SIZE> &matrix,
    size_t source) {
  // node to distance
  std::array<size_t, SIZE> visited;
  // node to distance
  std::map<size_t, size_t> queue;

  for(size_t node{0}; node < SIZE; ++node) queue[node] = source == node ? 0 : INFINITE;

  while(!queue.empty()) {
    auto node{find_min_node(queue)};
    auto weight{queue[node]};
    queue.erase(node);
    visited[node] = weight;
    auto neighbour_weights{find_direct_neighbours(matrix, node, weight, queue)};
    for(auto const &neighbour_weight : neighbour_weights) queue[neighbour_weight.first] = neighbour_weight.second;
  }

  return visited;
}