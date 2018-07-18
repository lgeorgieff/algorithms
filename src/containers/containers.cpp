#pragma once

#include "containers.hpp"

#include <cstddef>
#include <iostream>

namespace {
bool is_palindrom(size_t left, size_t right, const std::string &str) {
  while (left < right)
    if (str[left++] != str[right--]) return false;
  return true;
}

void partitionize(std::vector<std::vector<std::string>> &result,
                  std::vector<std::string> &current, size_t start, size_t end,
                  const std::string &str) {
  if (start >= end) {
    result.push_back(current);
    return;
  }

  for (size_t anchor{start}; anchor < end; ++anchor) {
    if (is_palindrom(start, anchor, str)) {
      current.push_back(str.substr(start, anchor - start + 1));
      partitionize(result, current, anchor + 1, end, str);
      current.pop_back();
    }
  }
}

void _permute(std::string::iterator original_begin, std::string::iterator begin,
              std::string::iterator end, containers::permutation_fn fn) {
  if (begin == end - 1) {
    fn(original_begin, end);
  } else {
    for(auto iter{begin}; iter < end; ++iter) {
      std::swap(*begin, *iter);
      _permute(original_begin, begin + 1, end, fn);
      std::swap(*begin, *iter);
    }
  }
}

template<typename T>
void _combine_inc(T *begin_a, T *end_a, T *begin_b, T *end_b, std::vector<std::vector<T>> &result,
                  std::vector<T> &accumulator) {
  if (!(accumulator.size() % 2)) {
    for(; begin_a < end_a; ++begin_a) {
      if (!accumulator.size() || *begin_a > accumulator.back()) {
        accumulator.push_back(*begin_a);
        _combine_inc(begin_a + 1, end_a, begin_b, end_b, result, accumulator);
        accumulator.pop_back();
      }
    }
  } else {
    for(; begin_b < end_b; ++begin_b) {
      if (*begin_b > accumulator.back()) {
        accumulator.push_back(*begin_b);
        result.push_back(accumulator);
        _combine_inc(begin_a, end_a, begin_b + 1, end_b, result, accumulator);
        accumulator.pop_back();
      }
    }
  }
}
}  // namespace

namespace containers {

std::vector<std::vector<std::string>> partition_string(const std::string &str) {
  std::vector<std::vector<std::string>> result;
  std::vector<std::string> current;
  partitionize(result, current, 0, str.size(), str);

  return result;
}

std::deque<int> shortest_subsequence(std::vector<int>::const_iterator begin,
                                     std::vector<int>::const_iterator end, int threshold) {
  std::deque<int> result;

  std::deque<int> accumulator;
  int current_sum{0};
  for (auto iter{begin}; iter < end; ++iter) {
    accumulator.push_back(*iter);
    current_sum += *iter;

    while (!accumulator.empty() && current_sum - accumulator.front() >= threshold) {
      current_sum -= accumulator.front();
      accumulator.pop_front();
    }
    if (current_sum >= threshold && (result.size() > accumulator.size() || result.empty()))
      result = accumulator;
  }
  return result;
}

void print_permutation(std::string::iterator begin, std::string::iterator end) {
  if (begin >= end) return;

  std::cout << "\"";
  while (begin < end) std::cout << *begin++;
  std::cout << "\"" << std::endl;
}

void permute(std::string::iterator first, std::string::iterator end, permutation_fn fn) {
  _permute(first, first, end, fn);
}

template<typename T>
std::vector<std::vector<T>> combine_inc(T *begin_a, T *end_a, T *begin_b, T *end_b) {
  std::vector<std::vector<T>> result;
  std::vector<T> accumulator;
  _combine_inc(begin_a, end_a, begin_b, end_b, result, accumulator);
  return result;
}
}  // namespace containers