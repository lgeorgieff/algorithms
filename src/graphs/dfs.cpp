#pragma once

#include "dfs.hpp"
#include <stack>
#include <unordered_set>

namespace {

template<typename T>
void dfs_recursive_p(std::stack<std::shared_ptr<algorithms::graph::node<T>>> &current_nodes,
    algorithms::graph::unordered_set_shared_node<T> visited, std::function<void(const T &)> fn) {
  if(current_nodes.empty()) return;

  if(visited.find(current_nodes.top()) != visited.cend()) {
    current_nodes.pop();
    dfs_recursive_p(current_nodes, visited, fn);
    return;
  }

  fn(current_nodes.top()->value);
  visited.insert(current_nodes.top());
  for(auto child : current_nodes.top()->connections()) {
    auto sptr{child.lock()};
    if(sptr != nullptr) current_nodes.push(sptr);
  }

  dfs_recursive_p(current_nodes, visited, fn);
}

} // anonymous namespace

template<typename T>
void algorithms::graph::dfs_iterative(std::shared_ptr<node<T>> current_node, std::function<void(const T &)> fn) {

}

template<typename T>
void algorithms::graph::dfs_recursive(std::shared_ptr<node<T>> current_node, std::function<void(const T &)> fn) {
  std::stack<std::shared_ptr<node<T>>> current_nodes;
  current_nodes.push(current_node);
  unordered_set_shared_node<T> visited;
  dfs_recursive_p(current_nodes, visited, fn);
}