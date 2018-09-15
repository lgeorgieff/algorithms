#pragma once

#include <string>
#include <cstddef>

namespace low {
  class levenshtein_distance {
  public:
    struct config {
      uint8_t deletion;
      uint8_t insertion;
      uint8_t substitution;
    }; // struct config

    const static struct config DEFAULT_CONFIG;

  public:
    levenshtein_distance(const std::string &str1,
                          const std::string &str2) noexcept;
    levenshtein_distance(const std::string &str1, const std::string &str2,
                          const config &config) noexcept;
    size_t distance() const noexcept;
    ~levenshtein_distance() noexcept;
    std::string to_string() const noexcept;
    const std::string &str1() const noexcept;
    const std::string &str2() const noexcept;
    size_t rows() const noexcept;
    size_t cols() const noexcept;
    const config & config() const noexcept;

  private:
    size_t **_distance_matrix;
    std::string _str1;
    std::string _str2;
    struct config _config;
  }; // class levenshtein_distance
} // namesapce low
