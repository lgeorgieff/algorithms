#pragma once

#include "sorting.hpp"

#include <algorithm>
#include <random>
#include <list>

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
  for(T *outer_iter{begin}; outer_iter < end; ++outer_iter) {
    for (T *inner_iter{outer_iter}; inner_iter < end; ++inner_iter) {
      if (comp(*outer_iter, *inner_iter) == 1) std::swap(*outer_iter, *inner_iter);
    }
  }
}

template <typename T>
void merge_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp) {
  if (begin >= end - 1) return;

  auto begin_left{begin}, end_left{begin + ((end - begin) / 2)}, begin_right{end_left},
      end_right{end};

  merge_sort(begin_left, end_left, comp);
  merge_sort(begin_right, end_right, comp);

  std::list<T> tmp;
  while(begin_left < end_left && begin_right < end_right) {
    if (comp(*begin_left, *begin_right) <= 0) tmp.push_back(*begin_left++);
    else tmp.push_back(*begin_right++);
  }
  while(begin_left < end_left) tmp.push_back(*begin_left++);
  while(begin_right < end_right) tmp.push_back(*begin_right++);

  for(auto iter_tmp{tmp.begin()}; iter_tmp != tmp.end(); ++iter_tmp) std::swap(*iter_tmp, *begin++);
}
} // namespace sorting