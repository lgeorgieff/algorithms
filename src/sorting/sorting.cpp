#pragma once

#include "sorting.hpp"

#include <algorithm>
#include <random>

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
} // namespace sorting