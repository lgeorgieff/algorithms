#pragma once

#include "dijkstra.hpp"
#include <map>
#include <utility>
#include <limits>
#include <queue>
#include <bitset>
#include <string>

namespace {
std::string to_string(int32_t item, unsigned short item_width, bool centered = true) {
  std::string str{std::to_string(item)};
  if(str.size() > item_width) str = "";
  while(str.size() < item_width) {
    str += " ";
    if(centered && str.size() < item_width) str = " " + str;
  }
  return str;
}
} // anonymous namespace

template<size_t SIZE>
void algorithms::graph::print_matrix(std::ostream &out, const matrix_t<SIZE> &graph, unsigned short item_width) {
  out << std::string(item_width + 1, ' ');
  for(size_t line{0}; line < SIZE; ++line) out << to_string(line, item_width, false) << " ";
  out << std::endl;

  for(size_t line{0}; line < SIZE; ++line) {
    out << to_string(line, item_width) << " ";
    for(size_t col{0}; col < SIZE; ++col) {
      out << to_string(graph[line][col], item_width) << " ";
    }
    out << std::endl;
  }
}

template<size_t SIZE>
std::array<int32_t, SIZE> algorithms::graph::dijkstra_distance(const matrix_t<SIZE> &matrix, size_t source) {
  if(source >= SIZE) throw std::out_of_range{"source index is out of graph's range"};

  std::array<int32_t, SIZE> distances;
  std::bitset<SIZE> calculated_nodes;
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
        if(!calculated_nodes[other_node]) {
          priority_queue.push(pair_t(distances[other_node], other_node));
          calculated_nodes.set(other_node);
        }
      }
    }
  }

  return distances;
}