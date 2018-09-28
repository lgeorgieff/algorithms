#pragma once

#include <vector>
#include <string>

namespace algorithms {
namespace simple_graph {

template<typename T>
class node {
 public:
  node() = default;
  node(const T &value);
  node(const node &) = default;
  node(node &&) = default;
  node &operator=(const node &) = default;
  node &operator=(node &&) = default;
  ~node() noexcept = default;

  const T &value() const noexcept;
  T &value() noexcept;
  const std::vector<node *> &links() const noexcept;
  std::vector<node *> &links() noexcept;
  bool empty() const noexcept;
  size_t size() const noexcept;
  bool has_link(const node *other) const noexcept;
  node *link(node *other);
  node *sym_link(node *other);
  node *link(const T &value_other);
  node *sym_link(const T &value_other);

 private:
  T value_;
  std::vector<node *> links_;
};

template<typename T>
void print_pre_order_rec(node<T> * const root, const std::string &separator = " ");

template<typename T>
void print_pre_order_iter(node<T> * const root, const std::string &separator = " ");

template<typename T>
void print_in_order_rec(node<T> * const root, const std::string &separator = " ");

template<typename T>
void print_in_order_iter(node<T> * const root, const std::string &separator = " ");

template<typename T>
void print_post_order_rec(node<T> * const root, const std::string &separator = " ");

template<typename T>
void print_post_order_iter(node<T> * const root, const std::string &separator = " ");

template<typename T>
void print_breadth_first(node<T> * const root, const std::string &separator = " ");

template<typename T>
void print_depths_first(node<T> * const root, const std::string &separator = " ");
} // namespace simple_graph
} // namespace algorithm

#include "simple_node.cpp"