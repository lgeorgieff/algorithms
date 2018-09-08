#pragma once

#include "heap.hpp"

#include <algorithm>
#include <utility>
#include <stdexcept>
#include <iterator>

namespace {
template<typename T, typename COMP>
size_t get_capacity(size_t size) {
  size_t capacity{algorithms::heap<T, COMP>::DEFAULT_HEAP_CAPACITY};
  while(capacity < size) size *= 2;
  return capacity;
}

size_t get_parent(size_t index) {
  size_t result{(index - 1) / 2};
  return result < 0 ? 0 : result;
}

size_t get_left_child(size_t index) {
  return index * 2 + 1;
}

size_t get_right_child(size_t index) {
  return index * 2 + 2;
}

bool has_children(size_t index, size_t heap_size) {
  size_t expected_left_child{index * 2 + 1};
  return expected_left_child < heap_size;
}
} // anonymous namespace

template <typename T>
int algorithms::heap_comp<T>::operator()(const T &left, const T &right) const {
    if(left < right) return -1;
    else if(left == right) return 0;
    else return 1;
}

template<typename T, typename COMP>
algorithms::heap<T, COMP>::heap(const T *begin, const T *end) :size_{0}, capacity_{0}, data_{nullptr} {
  capacity_ = get_capacity<T, COMP>(end - begin);
  data_ = new T[capacity_];
  size_ = end - begin;
  std::copy(begin, end, data_);
  heapify();
}

template<typename T, typename COMP>
const size_t algorithms::heap<T, COMP>::DEFAULT_HEAP_CAPACITY = 16;

template<typename T, typename COMP>
algorithms::heap<T, COMP>::~heap() {
  if(data_) delete[] data_;
  data_ = nullptr;
}

template<typename T, typename COMP>
algorithms::heap<T, COMP>::heap() :size_{0}, capacity_{DEFAULT_HEAP_CAPACITY}, data_{new T[DEFAULT_HEAP_CAPACITY]} {}

template<typename T, typename COMP>
algorithms::heap<T, COMP>::heap(const heap &other) :size_{other.size()}, capacity_{other.capacity_},
data_{new T[other.capacity_]} {
  std::copy(other.data_, other.data_ + other.size_, data_);
}

template<typename T, typename COMP>
algorithms::heap<T, COMP>::heap(heap &&other) :size_{std::move(other.size_)}, capacity_{std::move(other.capacity_)},
  data_{other.data_} {
  other.data_ = nullptr;
}

template <typename T, typename COMP>
algorithms::heap<T, COMP> &algorithms::heap<T, COMP>::operator=(algorithms::heap<T, COMP> &&other) {
  if(this == &other) return;
  size_ = std::move(other.size_);
  capacity_ = std::move(other.capacity_);
  if(data_) delete[] data_;
  data_ = other.data_;
  other.data_ = 0;
}

template<typename T, typename COMP>
algorithms::heap<T, COMP> &algorithms::heap<T, COMP>::operator=(const algorithms::heap<T, COMP> &other) {
  if(this == &other) return;
  size_ = other.size_;
  capacity_ = other.capacity_;
  if(data_) delete[] data_;
  data_ = new T[capacity_];
  std::copy(other.data_, other.data_ + other.size_, data_);
}

template<typename T, typename COMP>
size_t algorithms::heap<T, COMP>::size() const noexcept { return size_; }

template<typename T, typename COMP>
size_t algorithms::heap<T, COMP>::capacity() const noexcept { return capacity_; }

template<typename T, typename COMP>
bool algorithms::heap<T, COMP>::empty() const noexcept { return !size_; }

template<typename T, typename COMP>
const T &algorithms::heap<T, COMP>::top() const {
  if(empty()) throw std::runtime_error{"Cannot invoke top on empty heap"};
  return data_[0];
}

template<typename T, typename COMP>
T algorithms::heap<T, COMP>::pop() {
  if(empty()) throw std::runtime_error{"Cannot invoke pop on empty heap"};
  T result{data_[0]};
  data_[0] = data_[size_ - 1];
  --size_;
  heapify_down(0);
  return result;
}

template<typename T, typename COMP>
void algorithms::heap<T, COMP>::push(const T &t) {
  if(size_ == capacity_) {
    auto tmp{new T[capacity_ * 2]};
    std::copy(data_, data_ + size_, tmp);
    delete[] data_;
    data_ = tmp;
    capacity_ *= 2;
  }

  data_[size_] = t;
  ++size_;
  heapify_up(size_ - 1);
}

template<typename T, typename COMP>
void algorithms::heap<T, COMP>::heapify_up(size_t index) {
  auto current_index{index};
  while(index > 0 && COMP()(data_[get_parent(current_index)], data_[current_index]) > 0) {
    std::swap(data_[current_index], data_[get_parent(current_index)]);
  }
}

template<typename T, typename COMP>
void algorithms::heap<T, COMP>::heapify_down(size_t index) {
  auto current_index{index};
  while(has_children(current_index, size_)) {
    auto left_child{get_left_child(current_index)}, right_child{get_right_child(current_index)};
    size_t next_index{current_index};

    auto c{data_[current_index]};
    auto lc{data_[left_child]};
    auto rc{data_[right_child]};


    if(left_child < size_ && COMP()(data_[current_index], data_[left_child]) > 0) next_index = left_child;
    if(right_child < size_ && COMP()(data_[next_index], data_[right_child]) > 0) next_index = right_child;
    if(next_index == current_index) break;
    std::swap(data_[current_index], data_[next_index]);
    current_index = next_index;
  }
}

template<typename T, typename COMP>
void algorithms::heap<T, COMP>::heapify() {
  if(size_<= 1) return;
  size_t index{size_ / 2 + 1};
  while(index < size_) {
    heapify_down(index);
    --index;
  }
}

template<typename T, typename COMP>
std::vector<T> algorithms::heap<T, COMP>::data() const noexcept {
  std::vector<T> result;
  result.insert(result.begin(), data_, data_ + size());
  return result;
}