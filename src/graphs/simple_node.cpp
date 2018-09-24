#pragma once

#include "simple_node.hpp"

#include <algorithm>
#include <stdexcept>

template<typename T>
algorithms::simple_graph::node<T>::node(const T &value) :value_{value}, links_{} {}

template<typename T>
const T &algorithms::simple_graph::node<T>::value() const noexcept { return value_; }

template<typename T>
T &algorithms::simple_graph::node<T>::value() noexcept { return value_; }

template<typename T>
const std::vector<algorithms::simple_graph::node<T>> &algorithms::simple_graph::node<T>::links() const noexcept {
  return links;
}

template<typename T>
std::vector<algorithms::simple_graph::node<T>> &algorithms::simple_graph::node<T>::links() noexcept { return links; }

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
