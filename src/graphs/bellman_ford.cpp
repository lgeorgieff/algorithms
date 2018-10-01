#include "bellman_ford.hpp"

#include <stdexcept>

template<size_t SIZE>
std::array<size_t, SIZE> algorithms::graph::bellman_ford_distance(const graph_matrix<SIZE> &matrix,  size_t source) {
  std::array<size_t, SIZE> distances;
  if(source >= SIZE) throw std::out_of_range{"source index is out of graph's range"};

  for(auto &distance : distances) distance = INFINITE;
  distances[source] = 0;
  for(size_t iteration{0}; SIZE > 0 && iteration < SIZE - 1; ++iteration) {
    for(size_t node{0}; node < SIZE; ++node) {

    }
  }

  return distances;
}