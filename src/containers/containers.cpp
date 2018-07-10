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

} // namespace containers