#pragma once

#include "node.hpp"
#include <functional>

namespace algorithms {
namespace graph {

template<typename T>
void bfs_iterative(std::shared_ptr<node<T>> current_node, std::function<void(const T &, bool)>);

template<typename T>
void bfs_recursive(std::shared_ptr<node<T>> current_node, std::function<void(const T &, bool)>);

} // namespace graph
} // namespace algorithms

#include "bfs.cpp"