#pragma once

#include <string>
#include <fstream>
#include <functional>
#include <list>
#include <cstddef>
#include <limits>

namespace algorithms {
namespace fs {
class file_reader {
 public:
  explicit file_reader(const std::string path);
  file_reader(const file_reader &source) = default;
  file_reader(file_reader &&source) = default;
  file_reader &operator=(const file_reader &source) = default;
  file_reader &operator=(file_reader &&source) = default;
  ~file_reader() noexcept;

  template<typename T>
  std::list<T> all_lines(std::function<T(const std::string &)> fn);
  std::list<std::string> last_lines(size_t n = MAX_LINES);
  void reset();

  constexpr static size_t MAX_LINES = std::numeric_limits<size_t>::max();
 private:
  const std::string path_;
  std::ifstream file_;
}; // class file_reader
} // namespace fs
} // namespace algorithms

#include "file_reader.cpp"