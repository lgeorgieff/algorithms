#include "./minimum_edit_distance.hpp"

#include <algorithm>
#include <cstddef>
#include <string>

using std::min;
using std::max;
using std::string;

namespace {
size_t rows(const string &str1, const string &str2) { return str1.size() + 1; }
size_t lines(const string &str1, const string &str2) { return str2.size() + 1; }

template <typename T>
T **allocate_2_dim_array(size_t lines, size_t rows) {
  T **line_array = new T *[lines];
  for(size_t line(0); line < lines; ++line)
    line_array[line] = new T[rows];
  return line_array;
}

size_t get_min_distance(size_t **distance_matrix, size_t current_line,
                        size_t current_row, char c1, char c2,
                        bool levenshtein) {
  size_t diff(c1 == c2 ? 0 : 1);
  if(!current_line) {
    return distance_matrix[0][current_row - 1] + diff;
  } else if (!current_row) {
    return distance_matrix[current_line - 1][0] + diff;
  } else {
    size_t line1_row1(distance_matrix[current_line - 1][current_row - 1] +
                      (diff * (levenshtein ? 2 : 1))),
        line1_row(distance_matrix[current_line - 1][current_row] +
                  (levenshtein ? 1 : diff)),
        line_row1(distance_matrix[current_line][current_row - 1] +
                  (levenshtein ? 1 : diff));
    return min(min(line1_row, line1_row1), line_row1);
  }
}

size_t **create_distance_matrix(const string &str1, const string str2,
                                bool levenshtein) {
  size_t max_lines(lines(str1, str2)), max_rows(rows(str1, str2));
  size_t **matrix(allocate_2_dim_array<size_t>(max_lines, max_rows));

  // Set default distances for first line and first row
  for (size_t row(0); row < max_rows; ++row)
    matrix[0][row] = row;
  for (size_t line(0); line < max_lines; ++line)
    matrix[line][0] = line;

  // Set distance based on prior or default distances
  for(size_t line(1); line < max_lines; ++line) {
    for(size_t row(1); row < max_rows; ++row) {
      size_t min_distance(get_min_distance(matrix, line, row, str1[row - 1],
                                           str2[line - 1], levenshtein));
      matrix[line][row] = min_distance;
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

size_t get_width(size_t **matrix, size_t lines, size_t rows) {
  size_t max;
  for(size_t line(0); line < lines; ++line)
    for(size_t row(0); row < rows; ++row)
      if(max < matrix[line][row]) max = matrix[line][row];
  return (max / 10) + 2;
}
} // anonymous namespace

namespace low {
minimum_edit_distance::minimum_edit_distance(const string &str1,
                                             const string &str2,
                                             bool levenshtein) noexcept
    : _distance_matrix(create_distance_matrix(str1, str2, levenshtein)),
      _str1(str1), _str2(str2), _levenshtein(levenshtein) {}

string minimum_edit_distance::to_string() const noexcept {
  size_t width(get_width(this->_distance_matrix, this->lines(), this->rows()));
  string result;

  for(size_t line(0); line < this->lines() + 1; ++line) {
    for(size_t row(0); row < this->rows() + 1; ++row) {
      if(line == 0 && row == 0) {
        result += to_field(" ", width);
      } else if((line == 0 && row == 1) || (line == 1 && row == 0)) {
        result += to_field("#", width);
      } else if (line == 0 && row > 1) {
        result += to_field(string(1, this->_str1[row - 2]), width);
      } else if (row == 0 && line > 1) {
        result += to_field(string(1, this->_str2[line - 2]), width);
      } else {
        result += to_field(
            std::to_string(this->_distance_matrix[line - 1][row - 1]), width);
      }
    }
    result += '\n';
  }

  return result;
}

minimum_edit_distance::~minimum_edit_distance() noexcept {
  for(size_t line(0); line < this->lines(); ++line)
    delete[] this->_distance_matrix[line];
  delete[] this->_distance_matrix;
  this->_distance_matrix = nullptr;
}

const string &minimum_edit_distance::str1() const noexcept {
  return this->_str1;
}

const string &minimum_edit_distance::str2() const noexcept {
  return this->_str2;
}

size_t minimum_edit_distance::lines() const noexcept {
  return ::lines(this->_str1, this->_str2);
}

size_t minimum_edit_distance::rows() const noexcept {
  return ::rows(this->_str1, this->_str2);
}

size_t minimum_edit_distance::distance() const noexcept {
  return this->_distance_matrix[this->lines() - 1][this->rows() - 1];
}

bool minimum_edit_distance::levenshtein() const noexcept {
  return this->_levenshtein;
}
} // namespace low
