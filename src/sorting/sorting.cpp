#pragma once

#include "sorting.hpp"

#include <algorithm>
#include <random>
#include <list>
#include <vector>

namespace sorting {
template <typename T>
void randomize(T *begin, T *end) {
  for(T *outer_iter{begin}; outer_iter < end; ++outer_iter) {
    for(T *inner_iter{outer_iter}; inner_iter < end; ++inner_iter) {
      if(rand() % 3) std::swap(*outer_iter, *inner_iter);
    }
  }
}

template <typename T>
int comparator_fn(const T &a, const T &b) {
  if (a < b) return -1;
  if (a > b) return 1;
  else return 0;
}

template <typename T>
void bubble_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  if (begin >= end) return;

  for(T *outer_iter{begin}; outer_iter < end; ++outer_iter) {
    for (T *inner_iter{outer_iter}; inner_iter < end; ++inner_iter) {
      if (comp(*outer_iter, *inner_iter) == 1) std::swap(*outer_iter, *inner_iter);
    }
  }
}

template <typename T>
void merge_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  if(begin >= end - 1) return;

  auto begin_l{begin}, end_l{begin + (end - begin) / 2}, begin_r{end_l}, end_r{end};
  merge_sort(begin_l, end_l);
  merge_sort(begin_r, end_r);

  std::vector<T> storage;
  while(begin_l < end_l && begin_r < end_r) {
    if(*begin_l < *begin_r) storage.push_back(*begin_l++);
    else storage.push_back(*begin_r++);
  }
  while(begin_l < end_l) storage.push_back(*begin_l++);
  while(begin_r < end_r) storage.push_back(*begin_r++);
  std::copy(storage.begin(), storage.end(), begin);
}

template<typename T>
void insertion_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
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
void quick_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  if(begin >= end) return;

  auto *left{begin}, *right{end}, *pivot{left++};
  while(left < right) {
    if(comp(*left, *pivot) <= 0) {
      ++left;
    } else {
      while(right > left && comp(*right, *pivot) >= 0) --right;
      std::swap(*left, *right);
    }
  }
  --left;
  std::swap(*pivot, *left);

  quick_sort(begin, left, comp);
  quick_sort(right, end, comp);
}
} // namespace sorting