#pragma once

#include <cstddef>
#include <functional>
#include <vector>

namespace algorithms {

template<typename T>
class heap_comp {
 public:
  int operator()(const T &left, const T &right) const;
};

template<typename T, typename COMP = heap_comp<T>>
class heap {
 public:
  heap();
  heap(const T *begin, const T *end);
  heap(const heap &other);
  heap(heap &&other);
  ~heap();
  heap &operator=(const heap &other);
  heap &operator=(heap &&);

  T pop();
  void push(const T &t);
  const T &top() const;
  size_t size() const noexcept;
  size_t capacity() const noexcept;
  bool empty() const noexcept;
  std::vector<T> data() const noexcept;

  static const size_t DEFAULT_HEAP_CAPACITY;
 private:
  void heapify();
  void heapify_down(size_t index);
  void heapify_up(size_t index);

  size_t size_;
  size_t capacity_;
  T* data_;
};
} // namespace algorithms

#include "heap.cpp"