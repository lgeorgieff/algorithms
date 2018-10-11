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

template<size_t SIZE>
algorithms::graph::graph_t<SIZE>::graph_t(const matrix_t<SIZE> &matrix) :links_{} {
  for(size_t line{0}; line < SIZE; ++line)
    for(size_t row{0}; row < SIZE; ++row)
      links_[line].push_back(std::pair(row, matrix[line][row]));
}

template<size_t SIZE>
void algorithms::graph::graph_t<SIZE>::add_edge(size_t from, size_t to, int32_t weight) {
  if(from >= SIZE) throw std::out_of_range{"from is out of range"};
  if(to >= SIZE) throw std::out_of_range{"to is out of range"};
  links_[from].push_back(std::pair(to, weight));
}

template<size_t SIZE>
const std::vector<std::pair<size_t, int32_t>> &algorithms::graph::graph_t<SIZE>::links(size_t node) const noexcept {
  if(node >= SIZE) throw std::out_of_range{"node is out of range"};
  return links_[node];
}

template<size_t SIZE>
size_t algorithms::graph::graph_t<SIZE>::size() const noexcept { return SIZE; }

template<size_t SIZE>
void algorithms::graph::graph_t<SIZE>::print(std::ostream &out, unsigned short item_width) const {
  print_matrix(out, to_matrix(), item_width);
}

template<size_t SIZE>
algorithms::graph::matrix_t<SIZE> algorithms::graph::graph_t<SIZE>::to_matrix() const {
  matrix_t<SIZE> result{};
  for(size_t node{0}; node < SIZE; ++node) {
    for(size_t link{0}; link < SIZE; ++link)
      result[node][link] = INFINITE;
    for(size_t link{0}; link < links_[node].size(); ++link)
      result[node][links_[node][link].first] = links_[node][link].second ;
  }
  return result;
}

template<size_t SIZE>
std::array<int32_t, SIZE> algorithms::graph::graph_t<SIZE>::dijkstra_distance(size_t source) const {
  std::array<int32_t, SIZE> distances;
  // TODO: implement dijkstra
  return distances;
}