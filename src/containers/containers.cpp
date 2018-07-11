#include "containers.hpp"

#include <cstddef>

namespace {
  bool is_palindrom(size_t left, size_t right, const std::string &str) {
    while (left < right) if (str[left++] != str[right--]) return false;
    return true;
  }

  void partitionize(std::vector<strings> &result, strings &current, size_t start, size_t end,
                    const std::string &str) {
    if (start >= end) {
      result.push_back(current);
      return;
    }

    for(size_t anchor{start}; anchor < end; ++anchor) {
      if (is_palindrom(start, anchor, str)) {
        current.push_back(str.substr(start, anchor - start + 1));
        partitionize(result, current, anchor + 1, end, str);
        current.pop_back();
      }
    }
  }
} // namespace

namespace containers {

std::vector<strings> partition_string(const std::string &str) {
  std::vector<strings> result;
  strings current;
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
} // namespace containers