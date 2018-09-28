#pragma once

#include "simple_node.hpp"

#include <algorithm>
#include <stdexcept>
#include <unordered_set>
#include <iostream>
#include <queue>
#include <stack>

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
bool algorithms::simple_graph::node<T>::empty() const noexcept {
  return links_.empty();
}

template<typename T>
size_t algorithms::simple_graph::node<T>::size() const noexcept {
  return links_.size();
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

  std::unordered_set<node<T> *, pointer_hash<node<T> *>, pointer_compare<node<T> *>>  visited_nodes;
  std::queue<node<T> *> next_nodes;

  next_nodes.push(root);
  while(!next_nodes.empty()) {
    if(visited_nodes.find(next_nodes.front()) != visited_nodes.end()) {
      next_nodes.pop();
      continue;
    }

    visited_nodes.insert(next_nodes.front());
    std::cout << next_nodes.front()->value() << separator;

    for(auto iter{next_nodes.front()->links().begin()}; iter < next_nodes.front()->links().end(); ++iter)
      next_nodes.push(*iter);
    next_nodes.pop();
  }
}

template<typename T>
void algorithms::simple_graph::print_depths_first(node<T> * const root, const std::string &separator) {
  if(!root) return;

  std::unordered_set<node<T> *, pointer_hash<node<T> *>, pointer_compare<node<T> *>> marked_nodes;
  std::stack<node<T> *> next_nodes;

  next_nodes.push(root);
  marked_nodes.insert(root);
  while(!next_nodes.empty()) {
    auto *top{next_nodes.top()};
    for(auto *child : top->links()) {
      if(marked_nodes.find(child) == marked_nodes.end()) {
        marked_nodes.insert(child);
        next_nodes.push(child);
      }
    }
    if(top == next_nodes.top()) {
      std::cout << top->value() << separator;
      next_nodes.pop();
    }
  }
}

template<typename T>
void algorithms::simple_graph::print_pre_order_iter(node<T> * const root, const std::string &separator) {
  if(!root) return;

  std::stack<node<T> *> storage;
  storage.push(root);
  node<T> *current{root};

  while(!storage.empty()) {
    if(current) std::cout << current->value() << separator;
    if(current && !current->empty()) {
      current = current->links()[0];
      storage.push(current);
    } else {
      if(storage.top()->size() == 2) {
        current = storage.top()->links()[1];
        storage.pop();
        storage.push(current);
      } else {
        current = nullptr;
        storage.pop();
      }
    }
  }
}

template<typename T>
void algorithms::simple_graph::print_in_order_iter(node<T> * const root, const std::string &separator) {
  if(!root) return;

  std::stack<node<T> *> storage;
  node<T> *current{root};
  storage.push(root);

  while(!storage.empty()) {
    if(current) {
      if(!current->empty()) {
        current = current->links()[0];
        storage.push(current);
      } else {
        current = nullptr;
      }
    } else {
     std::cout << storage.top()->value() << separator;
     current = storage.top();
     storage.pop();
     if(current->size() == 2) {
       storage.push(current->links()[1]);
       current = storage.top();
     } else {
       current = nullptr;
     }
    }
  }
}