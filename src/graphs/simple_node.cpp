#pragma once

#include "simple_node.hpp"

#include <algorithm>
#include <stdexcept>
#include <unordered_set>
#include <iostream>
#include <queue>

namespace {
  template<typename T>
  struct pointer_compare {
    bool operator()(const T lhs, const T rhs) const {
      return lhs == rhs;
    }
  };

  template<typename T>
  struct pointer_hash {
    size_t operator() (const T ptr) const {
      return reinterpret_cast<size_t>(ptr);
    }
  };
} // anonymous namespace

template<typename T>
algorithms::simple_graph::node<T>::node(const T &value) :value_{value}, links_{} {}

template<typename T>
const T &algorithms::simple_graph::node<T>::value() const noexcept { return value_; }

template<typename T>
T &algorithms::simple_graph::node<T>::value() noexcept { return value_; }

template<typename T>
const std::vector<algorithms::simple_graph::node<T> *> &algorithms::simple_graph::node<T>::links() const noexcept {
  return links_;
}

template<typename T>
std::vector<algorithms::simple_graph::node<T> *> &algorithms::simple_graph::node<T>::links() noexcept { return links_; }

template<typename T>
bool algorithms::simple_graph::node<T>::has_link(const algorithms::simple_graph::node<T> *other) const noexcept {
  return std::find(links_.begin(), links_.end(), other) != links_.end();
}

template<typename T>
algorithms::simple_graph::node<T> *algorithms::simple_graph::node<T>::link(
    algorithms::simple_graph::node<T> *other) {
  if(!other) throw std::invalid_argument{"other must not be null"};
  links_.push_back(other);
  return other;
}

template<typename T>
algorithms::simple_graph::node<T> *algorithms::simple_graph::node<T>::sym_link(
    algorithms::simple_graph::node<T> *other) {
  if(!other) throw std::invalid_argument{"other must not be null"};
  links_.push_back(other);
  other->links_.push_back(this);
  return other;
}

template<typename T>
algorithms::simple_graph::node<T> *algorithms::simple_graph::node<T>::link(const T &value_other) {
  node *other{new node{value_other}};
  links_.push_back(other);
  return other;
}

template<typename T>
algorithms::simple_graph::node<T> *algorithms::simple_graph::node<T>::sym_link(const T &value_other) {
  node *other{new node{value_other}};
  links_.push_back(other);
  other->links_.push_back(this);
  return other;
}

template<typename T>
void algorithms::simple_graph::print_pre_order_rec(node<T> * const root, const std::string &separator) {
  if(!root) return;
  std::cout << root->value() << separator;
  const std::vector<node<T> *> links{root->links()};
  print_pre_order_rec(links.size() >= 1 ? links[0] : nullptr, separator);
  print_pre_order_rec(links.size() >= 2 ? links[1] : nullptr, separator);
}

template<typename T>
void algorithms::simple_graph::print_in_order_rec(node<T> * const root, const std::string &separator) {
  if(!root) return;
  const std::vector<node<T> *> links{root->links()};
  print_in_order_rec(links.size() >= 1 ? links[0] : nullptr, separator);
  std::cout << root->value() << separator;
  print_in_order_rec(links.size() >= 2 ? links[1] : nullptr, separator);
}

template<typename T>
void algorithms::simple_graph::print_post_order_rec(node<T> * const root, const std::string &separator) {
  if(!root) return;
  const std::vector<node<T> *> links{root->links()};
  print_post_order_rec(links.size() >= 1 ? links[0] : nullptr, separator);
  print_post_order_rec(links.size() >= 2 ? links[1] : nullptr, separator);
  std::cout << root->value() << separator;
}

template<typename T>
void algorithms::simple_graph::print_breadth_first(node<T> * const root, const std::string &separator) {
  if(!root) return;

  std::unordered_set<node<T> *, pointer_hash<node<T> *>, pointer_compare<node<T> *>>  visited;
  std::queue<node<T> *> next_nodes;

  next_nodes.push(root);
  while(!next_nodes.empty()) {
    if(visited.find(next_nodes.front()) != visited.end()) {
      next_nodes.pop();
      continue;
    }

    visited.insert(next_nodes.front());
    std::cout << next_nodes.front()->value() << separator;

    for(auto iter{next_nodes.front()->links().begin()}; iter < next_nodes.front()->links().end(); ++iter)
      next_nodes.push(*iter);
    next_nodes.pop();
  }
}