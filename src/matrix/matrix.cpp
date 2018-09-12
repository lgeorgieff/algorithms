#pragma once

#include "matrix.hpp"

template<typename T, size_t SIZE>
void matrix::rotate_90(matrix_t<T, SIZE> &matrix) {
  for(size_t row{0}; row < SIZE / 2; ++row) {
    for(size_t col{row}; col < SIZE - row - 1; ++col) {
      auto tmp{matrix[row][col]};
      matrix[row][col] = matrix[SIZE - col - 1][row];
      matrix[SIZE - col - 1][row] = matrix[SIZE - row - 1][SIZE - col - 1];
      matrix[SIZE - row - 1][SIZE - col - 1] = matrix[col][SIZE - row - 1];
      matrix[col][SIZE - row - 1] = tmp;
    }
  }
}

template<typename T, size_t SIZE, typename STRINGIFY>
std::string matrix::to_string(const matrix_t<T, SIZE> &matrix, STRINGIFY stringify) {
  std::string result;
  result.reserve(SIZE * SIZE * 2);

  for(size_t row{0}; row < SIZE; ++row) {
    for(size_t col{0}; col < SIZE; ++col) {
      result.append(stringify(matrix[row][col]));
      if(col != SIZE - 1) result += ' ';
    }
    result += '\n';
  }

  return result;
}
