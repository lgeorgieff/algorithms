#pragma once

#include <string>
#include <cstddef>

namespace low {
  class minimum_edit_distance {
  public:
    minimum_edit_distance(const std::string &str1, const std::string &str2,
                          bool levenshtein) noexcept;
    size_t distance() const noexcept;
    ~minimum_edit_distance() noexcept;
    std::string to_string() const noexcept;
    const std::string &str1() const noexcept;
    const std::string &str2() const noexcept;
    size_t lines() const noexcept;
    size_t rows() const noexcept;
    bool levenshtein() const noexcept;

  private:
    size_t** _distance_matrix;
    std::string _str1;
    std::string _str2;
    bool _levenshtein;
  }; // class minimum_edit_distance
} // namesapce low
