#pragma once

#include "sorting.hpp"

#include <algorithm>
#include <random>
#include <list>
#include <vector>

namespace {
template<typename T>
T* heap_parent(T *node, T *begin) {
  if(node == begin) return nullptr;
  return begin + (node - begin - 1) / 2;
}

template<typename T>
T *heap_left_child(T *node, T *begin, T *end) {
  auto *result{begin + (node - begin) * 2 + 1};
  return result >= end ? nullptr : result;
}

template<typename T>
T* heap_right_child(T *node, T *begin, T *end) {
  auto *result{begin + (node - begin) * 2 + 2};
  return result >= end ? nullptr : result;
}

template<typename T>
T* heap_smaller_child(T *node, T *begin, T *end, std::function<int(const T &, const T &)> comp) {
  auto *left_child{heap_left_child(node, begin, end)}, *right_child{heap_right_child(node, begin, end)};
  if(!left_child && !right_child) return nullptr;
  else if(left_child && !right_child) return left_child;
  else if(!left_child && right_child) return right_child;
  else if(comp(*left_child, *right_child) <= 0) return left_child;
  else return right_child;
}

template<typename T>
void heapify_down(T *node, T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  auto left_child{heap_left_child(node, begin, end)}, right_child{heap_right_child(node, begin, end)};
  if(!left_child && !right_child) return;

  T *to_be_swapped{heap_smaller_child(node, begin, end, comp)};
  if(to_be_swapped && comp(*to_be_swapped, *node) == -1) {
    std::swap(*node, *to_be_swapped);
    heapify_down(to_be_swapped, begin, end, comp);
  }
}

template<typename T>
void heapify_up(T *node, T *begin, T *end, std::function<int(const T&, const T&)>) {
  auto parent{heap_parent(node, begin)};
  if(!parent || comp(*parent, *node) >= 0) return;

  std::swap(*node, *parent);
  heapify_up(parent, begin, end);
}

template<typename T>
void build_heap(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  if(begin >= end) return;

  auto *current_node{begin + (end - begin) / 2};
  while(current_node >= begin) {
    heapify_down(current_node, begin, end, comp);
    --current_node;
  }
}
} // anonymous namespace

template <typename T>
void sorting::randomize(T *begin, T *end) {
  for(T *outer_iter{begin}; outer_iter < end; ++outer_iter) {
    for(T *inner_iter{outer_iter}; inner_iter < end; ++inner_iter) {
      if(rand() % 3) std::swap(*outer_iter, *inner_iter);
    }
  }
}

template <typename T>
int sorting::comparator_smaller_fn(const T &a, const T &b) {
  if (a < b) return -1;
  if (a > b) return 1;
  else return 0;
}

template <typename T>
int sorting::comparator_greater_fn(const T &a, const T &b) {
  if (a < b) return 1;
  if (a > b) return -1;
  else return 0;
}

template <typename T>
void sorting::bubble_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  if (begin >= end) return;

  for(T *outer_iter{begin}; outer_iter < end; ++outer_iter) {
    for (T *inner_iter{outer_iter}; inner_iter < end; ++inner_iter) {
      if (comp(*outer_iter, *inner_iter) == 1) std::swap(*outer_iter, *inner_iter);
    }
  }
}

template <typename T>
void sorting::merge_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  if(begin >= end - 1) return;

  auto begin_l{begin}, end_l{begin + (end - begin) / 2}, begin_r{end_l}, end_r{end};
  merge_sort(begin_l, end_l);
  merge_sort(begin_r, end_r);

  std::vector<T> storage;
  while(begin_l < end_l && begin_r < end_r) {
    if(comp(*begin_l, *begin_r) == -1) storage.push_back(*begin_l++);
    else storage.push_back(*begin_r++);
  }
  while(begin_l < end_l) storage.push_back(*begin_l++);
  while(begin_r < end_r) storage.push_back(*begin_r++);
  std::copy(storage.begin(), storage.end(), begin);
}

template<typename T>
void sorting::insertion_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  for(auto iter{begin}; iter < end; ++iter) {
    if (iter == begin || comp(*iter, *(iter - 1)) >= 0) continue;

    auto anchor{iter};
    while(anchor > begin && comp(*anchor, *(anchor - 1)) < 0) {
      std::swap(*anchor, *(anchor - 1));
      --anchor;
    }
  }
}

template<typename T>
void sorting::quick_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  if(begin >= end -1) return;
  
  auto left{begin}, right{end - 1}, pivot{left++};
  while(left < right) {
    while(left < right && comp(*left, *pivot) <= 0) ++left;
    while(right > left && comp(*right, *pivot) >= 0) --right;
    std::swap(*left, *right);
  }
  // In case left == right and *left < *right we swap this element with the pivot element otherwise we go one step back
  // and swap this element wth the pivot element. In the latter case we can be sure that the element is <= the pivot
  // element.
  if(comp(*left, *pivot) >= 0) --left;
  std::swap(*left, *pivot);

  quick_sort(begin, left, comp);
  quick_sort(right, end, comp);
}

template<typename T>
void sorting::heap_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  build_heap(begin, end, comp);
  auto heap_end{end};
  while(heap_end > begin) {
    auto top{*begin};
    std::swap(*begin, *(--heap_end));
    heapify_down(begin, begin, heap_end, comp);
    *end = top;
  }
}
