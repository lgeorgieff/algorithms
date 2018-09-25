#pragma once

#include "containers.hpp"

#include <cstddef>
#include <iostream>
#include <map>
#include <algorithm>
#include <bitset>
#include <stdexcept>

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

void permute_(std::string::iterator original_begin, std::string::iterator begin,
              std::string::iterator end, containers::permutation_fn fn) {
  if (begin == end - 1) {
    fn(original_begin, end);
  } else {
    for(auto iter{begin}; iter < end; ++iter) {
      std::swap(*begin, *iter);
      permute_(original_begin, begin + 1, end, fn);
      std::swap(*begin, *iter);
    }
  }
}

template<typename T>
void combine_inc_(T *begin_a, T *end_a, T *begin_b, T *end_b, std::vector<std::vector<T>> &result,
                  std::vector<T> &accumulator) {
  if (!(accumulator.size() % 2)) {
    for(; begin_a < end_a; ++begin_a) {
      if (!accumulator.size() || *begin_a > accumulator.back()) {
        accumulator.push_back(*begin_a);
        combine_inc_(begin_a + 1, end_a, begin_b, end_b, result, accumulator);
        accumulator.pop_back();
      }
    }
  } else {
    for(; begin_b < end_b; ++begin_b) {
      if (*begin_b > accumulator.back()) {
        accumulator.push_back(*begin_b);
        result.push_back(accumulator);
        combine_inc_(begin_a, end_a, begin_b + 1, end_b, result, accumulator);
        accumulator.pop_back();
      }
    }
  }
}

void all_substrings_(const std::string &str, size_t pos, std::string &container) {
  if(pos >= str.size()) return;

  for(size_t idx{pos}; idx < str.size(); ++idx) {
    container.push_back(str[idx]);
    std::cout << "_" << container << "_" << std::endl;
    all_substrings_(str, idx + 1, container);
    container.pop_back();
  }
}

const unsigned char ALPHA_LOWER_BEGIN{65};
const unsigned char ALPHA_LOWER_END{91};
const unsigned char ALPHA_UPPER_BEGIN{97};
const unsigned char ALPHA_UPPER_END{123};
constexpr unsigned char ALPHA_SPACE{ALPHA_LOWER_END - ALPHA_LOWER_BEGIN + ALPHA_UPPER_END - ALPHA_UPPER_BEGIN - 2};

unsigned char to_alpha_space(unsigned char c) {
  if(c >= ALPHA_LOWER_BEGIN && c < ALPHA_LOWER_END) {
    return c - ALPHA_LOWER_BEGIN;
  } else if (c >= ALPHA_UPPER_BEGIN && c < ALPHA_UPPER_END) {
    return c - ALPHA_UPPER_BEGIN + (ALPHA_LOWER_END - ALPHA_LOWER_BEGIN - 1);
  } else {
    throw std::invalid_argument{"c is out of bound from ALPHA"};
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
  permute_(first, first, end, fn);
}

template<typename T>
std::vector<std::vector<T>> combine_inc(T *begin_a, T *end_a, T *begin_b, T *end_b) {
  std::vector<std::vector<T>> result;
  std::vector<T> accumulator;
  combine_inc_(begin_a, end_a, begin_b, end_b, result, accumulator);
  return result;
}

void all_substrings(const std::string &str) {
  std::string container;
  container.reserve(str.size());
  std::cout << "__" << std::endl;
  all_substrings_(str, 0, container);
}

bool is_permutation(const std::string &lhs, const std::string &rhs) {
  if(lhs.size() != rhs.size()) return false;

  std::map<char, ssize_t> chars;
  for(const char c : lhs) ++chars[c];
  for(const char c : rhs) if(--chars[c] == -1) return false;
  return std::all_of(chars.begin(), chars.end(), [](const auto &pair){ return pair.second == 0; });
}

bool is_palindrome_permutation(const std::string &str) {
  std::bitset<ALPHA_SPACE> storage;
  for(unsigned char c : str) storage.flip(to_alpha_space(c));
  return storage.count() <= 1;
}
}  // namespace containers