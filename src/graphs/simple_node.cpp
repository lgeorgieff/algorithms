#pragma once

#include "simple_node.hpp"

#include <algorithm>
#include <stdexcept>
#include <iostream>

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
    const algorithms::simple_graph::node<T> *other) {
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
void algorithms::simple_graph::print_pre_order_rec(const node<T> *root, const std::string &separator) {
  if(!root) return;
  std::cout << root->value() << separator;
  const std::vector<node<T> *> links{root->links()};
  print_pre_order_rec(links.size() >= 1 ? links[0] : nullptr, separator);
  print_pre_order_rec(links.size() >= 2 ? links[1] : nullptr, separator);
}

template<typename T>
void algorithms::simple_graph::print_in_order_rec(const node<T> *root, const std::string &separator) {
  if(!root) return;
  const std::vector<node<T> *> links{root->links()};
  print_in_order_rec(links.size() >= 1 ? links[0] : nullptr, separator);
  std::cout << root->value() << separator;
  print_in_order_rec(links.size() >= 2 ? links[1] : nullptr, separator);
}