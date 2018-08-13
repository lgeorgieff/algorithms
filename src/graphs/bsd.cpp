#pragma once

#include "bsd.hpp"
#include <deque>
#include <unordered_set>
#include <iterator>
#include <algorithm>
#include <memory>

template<typename T>
void algorithms::graph::bsd_iterative(std::shared_ptr<node<T>> current_node, std::function<void(const T &, bool)> fn) {
  using container_t = std::vector<std::shared_ptr<node<T>>>;
  container_t current_level{current_node};
  container_t next_level;
  std::unordered_set<std::shared_ptr<node<T>>> visited;

  bool new_level{false};
  while(!current_level.empty()) {
    auto elem{current_level.back()};
    current_level.pop_back();

    if(visited.cend() == visited.find(elem)) {
      visited.insert(elem);
      fn(elem->value, new_level);
      auto new_elems{elem->connections()};
      for(auto wp : new_elems) {
        auto sp{wp.lock()};
        if(sp != nullptr) next_level.push_back(sp);
      }
    }
    new_level = current_level.empty();
    if(current_level.empty()) current_level.swap(next_level);
  }
}
