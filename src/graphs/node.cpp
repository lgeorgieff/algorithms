#pragma once

#include "node.hpp"
#include <functional>
#include <algorithm>

namespace {
template<typename T>
using node_t = algorithms::graph::node<T>;
template<typename T>
using weak_ptr_hash = algorithms::graph::weak_ptr_hash<T>;
template<typename T>
using weak_ptr_equal = algorithms::graph::weak_ptr_equal<T>;

template<typename T>
void erase_dangling_pointers(std::unordered_set<std::weak_ptr<node_t<T>>,
    weak_ptr_hash<node_t<T>>, weak_ptr_equal<node_t<T>>> &container) {
  auto iter{container.begin()};
  while(iter != container.end()) {
    if(iter->expired()) iter = container.erase(iter);
    else ++iter;
  }
}

template<typename T>
size_t count_valid_pointers(const std::unordered_set<std::weak_ptr<node_t<T>>,
    weak_ptr_hash<node_t<T>>, weak_ptr_equal<node_t<T>>> &container) {
  size_t counter{0};
  for(auto iter{container.begin()}; iter != container.end(); ++iter)
    if (!iter->expired()) ++counter;
  return counter;
}
} // anonymous namespace

template<typename T>
algorithms::graph::node<T>::node(T const &_value) :value{_value}, _links{} {}

template<typename T>
std::unique_ptr<algorithms::graph::node<T>> algorithms::graph::node<T>::create(T &&value) {
  return std::make_unique<node>(std::forward<T>(value));
}

template<typename T>
algorithms::graph::node<T>::~node() {
  _links.clear();
}

template<typename T>
bool algorithms::graph::node<T>::empty() const noexcept {
  return count_valid_pointers(_links) == 0;
}

template<typename T>
size_t algorithms::graph::node<T>::size() const noexcept {
  return count_valid_pointers(_links);
}

template<typename T>
bool algorithms::graph::node<T>::is_connected(std::shared_ptr<algorithms::graph::node<T>> other) const noexcept {
  for(auto iter{_links.begin()}; iter != _links.end(); ++iter) {
    if(!iter->expired()) {
      auto ptr{iter->lock()};
      if(ptr != nullptr && ptr == other) return true;
    }
  }
  return false;
}

template<typename T>
void algorithms::graph::node<T>::connect(std::shared_ptr<algorithms::graph::node<T>> other) {
  erase_dangling_pointers(_links);
  _links.insert(std::weak_ptr{other});
}

template<typename T>
void algorithms::graph::node<T>::disconnect(std::shared_ptr<algorithms::graph::node<T>> other) {
  erase_dangling_pointers(_links);
  _links.erase(std::weak_ptr{other});
}

template<typename T>
decltype(auto) algorithms::graph::node<T>::connections() const noexcept {
  decltype(_links) result;
  std::copy_if(_links.begin(), _links.end(), std::inserter(result, result.begin()),
      [](std::weak_ptr<node> ptr){ return !ptr.expired(); });

  return result;
}

template<typename T>
void algorithms::graph::node<T>::connect_sym(std::shared_ptr<node> node1, std::shared_ptr<node> node2) {
  node1->connect(node2);
  node2->connect(node1);
}

template<typename T>
void algorithms::graph::node<T>::disconnect_sym(std::shared_ptr<node> node1, std::shared_ptr<node> node2) {
  node1->disconnect(node2);
  node2->disconnect(node1);
}