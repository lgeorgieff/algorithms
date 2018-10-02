#include "bellman_ford.hpp"

#include <stdexcept>
#include <string>
#include <unordered_set>
#include <iostream>

namespace {
bool is_int32_t_overflow(int32_t val1, int32_t val2) {
  return (val1 > 0 && val2 > 0 && val1 + val2 < 0) || (val1 < 0 && val2 < 0 && val1 + val2 > 0);
}

template<size_t SIZE>
std::vector<size_t> get_all_successors(const algorithms::graph::matrix_t<SIZE> &matrix, size_t node) {
  std::unordered_set<size_t> visited;
  std::vector<size_t> successors;
  successors.push_back(node);
  visited.insert(node);
  size_t counter{0};
  while(counter < successors.size()) {
    for(size_t link{0}; link < SIZE; ++link) {
      if(matrix[successors[counter]][link] != algorithms::graph::INFINITE && visited.find(link) == visited.end()) {
        visited.insert(link);
        successors.push_back(link);
      }
    }
    ++counter;
  }

  return successors;
}
} // anonymous namespace

template<size_t SIZE>
std::array<int32_t, SIZE> algorithms::graph::bellman_ford_distance(const matrix_t<SIZE> &matrix,  size_t source, bool throw_if_cycle) {
  std::array<int32_t, SIZE> distances;
  if(source >= SIZE) throw std::out_of_range{"source index is out of graph's range"};

  for(auto &distance : distances) distance = INFINITE;
  distances[source] = 0;
  for(size_t iteration{0}; SIZE > 0 && iteration < SIZE - 1; ++iteration) {
    for(size_t node{0}; node < SIZE; ++node) {
      for(size_t link{0}; link < SIZE; ++link) {
        if (!is_int32_t_overflow(distances[node], matrix[node][link]) && distances[link] > distances[node] + matrix[node][link]) {
          distances[link] = distances[node] + matrix[node][link];
        }
      }
    }
  }

  ssize_t start_of_negative_cycle{-1};
  for(size_t node{0}; node < SIZE; ++node) {
    for(size_t link{0}; link < SIZE; ++link) {
      if (!is_int32_t_overflow(distances[node], matrix[node][link]) && distances[link] > distances[node] + matrix[node][link]) {
        distances[link] = distances[node] + matrix[node][link];
        start_of_negative_cycle = node;
        break;
      }
    }
    if(start_of_negative_cycle != -1) {
      std::string message{"bellman_ford_distance: Negative cycle detected: "};
      auto negative_cycle{get_all_successors(matrix, start_of_negative_cycle)};
      for(size_t iter{0}; iter < negative_cycle.size(); ++iter) {
        message += std::to_string(negative_cycle[iter]);
        if(iter != negative_cycle.size() - 1) message += " ";
      }

      if(throw_if_cycle) {
        throw std::runtime_error{message};
      } else {
        std::cerr << message << std::endl;
        for(auto link : negative_cycle) distances[link] = INFINITE;
        return distances;
      }
    }
  }

  return distances;
}