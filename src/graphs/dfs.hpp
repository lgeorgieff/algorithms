#pragma once

#include "node.hpp"

namespace algorithms {
namespace graph {

template<typename T>
void dfs_iterative(std::shared_ptr<node<T>> current_node, std::function<void(const T &)>);

template<typename T>
void dfs_recursive(std::shared_ptr<node<T>> current_node, std::function<void(const T &)>);

} // namespace graph
} // namespace algorithms

#include "dfs.cpp"