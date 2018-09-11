#pragma once

#include <cstddef>
#include <array>
#include <string>
#include <functional>

namespace matrix {
template<typename T, size_t SIZE>
using matrix_t = std::array<std::array<T, SIZE>, SIZE>;

template<typename T, size_t SIZE>
void rotate_90(matrix_t<T, SIZE> &matrix);

template<typename T, size_t SIZE, typename STRINGIFY>
std::string to_string(const matrix_t<T, SIZE> &matrix, STRINGIFY);
} // namespace matrix

#include "matrix.cpp"