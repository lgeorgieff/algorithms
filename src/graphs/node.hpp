#pragma once

#include <cstddef>
#include <unordered_set>
#include <memory>

namespace algorithms {
namespace graph {

template<typename T>
class weak_ptr_hash : public std::unary_function<std::weak_ptr<T>, size_t> {
 public:
  size_t operator()(const std::weak_ptr<T>& wp) const {
    auto sp = wp.lock();
    return std::hash<decltype(sp)>()(sp);
  }
}; // class weak_ptr_hash

template<typename T>
class weak_ptr_equal : public std::unary_function<std::weak_ptr<T>, bool> {
 public:
  bool operator()(const std::weak_ptr<T>& left, const std::weak_ptr<T>& right) const {
    return !left.owner_before(right) && !right.owner_before(left);
  }
}; // class weak_ptr_equal

template<typename T>
class node {
 public:
  node() = delete;
  node(const node &) = delete;
  node(node &&) = default;
  ~node();

  node &operator=(const node &other) = delete;
  node &operator=(node &&other) = default;

  bool empty() const noexcept;
  size_t size() const noexcept;

  void connect(std::shared_ptr<node> other);
  void disconnect(std::shared_ptr<node> other);
  bool is_connected(std::shared_ptr<node> other) const noexcept;
  decltype(auto) connections() const noexcept;

  static void connect_sym(std::shared_ptr<node> node1, std::shared_ptr<node> node2);
  static void disconnect_sym(std::shared_ptr<node> node1, std::shared_ptr<node> node2);

  static std::unique_ptr<node> create(T &&value);

  friend std::unique_ptr<node> std::make_unique<node>(T &&value);

 public:
  T value;

 private:
  node(const T &value);

 private:
   std::unordered_set<std::weak_ptr<node>, weak_ptr_hash<node>, weak_ptr_equal<node>> _links;
};

} // namespace node
} // namespace algorithms
#include "node.cpp"