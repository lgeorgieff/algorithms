#include "./levenshtein_distance.hpp"

#include <algorithm>
#include <cstddef>
#include <string>

using std::min;
using std::max;
using std::string;

namespace {
size_t cols(const string &str1, const string &str2) { return str1.size() + 1; }
size_t rows(const string &str1, const string &str2) { return str2.size() + 1; }

template <typename T>
T **allocate_2_dim_array(size_t rows, size_t cols) {
  T **row_array = new T *[rows];
  for(size_t row(0); row < rows; ++row)
    row_array[row] = new T[cols];
  return row_array;
}

size_t
get_min_distance(size_t **distance_matrix, size_t current_row,
                 size_t current_col, char c1, char c2,
                 const struct low::levenshtein_distance::config &config) {
  size_t diff(c1 == c2 ? 0 : 1);
  if(!current_row) {
    return distance_matrix[0][current_col - 1] + diff;
  } else if (!current_col) {
    return distance_matrix[current_row - 1][0] + diff;
  } else {
    size_t row1_col1(distance_matrix[current_row - 1][current_col - 1] +
                      (diff * config.substitution)),
        row1_col(distance_matrix[current_row - 1][current_col] +
                  (diff * config.deletion)),
        row_col1(distance_matrix[current_row][current_col - 1] +
                  (diff * config.insertion));
    return std::min(std::min(row1_col, row1_col1), row_col1);
  }
}

size_t **create_distance_matrix(
    const string &str1, const string str2,
    const struct low::levenshtein_distance::config &config) {
  size_t max_rows(rows(str1, str2)), max_cols(cols(str1, str2));
  size_t **matrix(allocate_2_dim_array<size_t>(max_rows, max_cols));

  // Set default distances for first row and first col
  for (size_t col(0); col < max_cols; ++col)
    matrix[0][col] = col * config.deletion;
  for (size_t row(0); row < max_rows; ++row)
    matrix[row][0] = row * config.insertion;

  // Set distance based on prior or default distances
  for(size_t row(1); row < max_rows; ++row) {
    for(size_t col(1); col < max_cols; ++col) {
      size_t min_distance(get_min_distance(matrix, row, col, str1[col - 1],
                                           str2[row - 1], config));
      matrix[row][col] = min_distance;
    }
  }
  
  return matrix;
}

string to_field(const string &str, size_t width) {
  string result(str);

  while(result.size() < width)
    result.insert(0, " ");

  return result;
}

size_t get_width(size_t **matrix, size_t rows, size_t cols) {
  size_t max;
  for(size_t row(0); row < rows; ++row)
    for(size_t col(0); col < cols; ++col)
      if(max < matrix[row][col]) max = matrix[row][col];
  return (max / 10) + 2;
}
} // anonymous namespace

namespace low {
levenshtein_distance::levenshtein_distance(const string &str1,
                                             const string &str2) noexcept
    : levenshtein_distance(str1, str2, levenshtein_distance::DEFAULT_CONFIG) {
}

levenshtein_distance::levenshtein_distance(
    const string &str1, const string &str2,
    const struct low::levenshtein_distance::config &config) noexcept
    : _distance_matrix(create_distance_matrix(str1, str2, config)), _str1(str1),
      _str2(str2), _config(config) {}

string levenshtein_distance::to_string() const noexcept {
  size_t width(get_width(this->_distance_matrix, this->rows(), this->cols()));
  string result;

  for(size_t row(0); row < this->rows() + 1; ++row) {
    for(size_t col(0); col < this->cols() + 1; ++col) {
      if(row == 0 && col == 0) {
        result += to_field(" ", width);
      } else if((row == 0 && col == 1) || (row == 1 && col == 0)) {
        result += to_field("#", width);
      } else if (row == 0 && col > 1) {
        result += to_field(string(1, this->_str1[col - 2]), width);
      } else if (col == 0 && row > 1) {
        result += to_field(string(1, this->_str2[row - 2]), width);
      } else {
        result += to_field(
            std::to_string(this->_distance_matrix[row - 1][col - 1]), width);
      }
    }
    result += '\n';
  }

  return result;
}

levenshtein_distance::~levenshtein_distance() noexcept {
  for(size_t row(0); row < this->rows(); ++row)
    delete[] this->_distance_matrix[row];
  delete[] this->_distance_matrix;
  this->_distance_matrix = nullptr;
}

const string &levenshtein_distance::str1() const noexcept {
  return this->_str1;
}

const string &levenshtein_distance::str2() const noexcept {
  return this->_str2;
}

size_t levenshtein_distance::rows() const noexcept {
  return ::rows(this->_str1, this->_str2);
}

size_t levenshtein_distance::cols() const noexcept {
  return ::cols(this->_str1, this->_str2);
}

size_t levenshtein_distance::distance() const noexcept {
  return this->_distance_matrix[this->rows() - 1][this->cols() - 1];
}

const struct levenshtein_distance::config &
levenshtein_distance::config() const noexcept {
  return this->_config;
}

const struct levenshtein_distance::config
    levenshtein_distance::DEFAULT_CONFIG({1, 1, 1});
} // namespace low
