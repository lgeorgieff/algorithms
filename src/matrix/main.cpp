#include "matrix.hpp"

#include <iostream>
#include <array>
#include <string>

using std::cout;
using std::endl;
using std::array;
using std::string;
using matrix::rotate_90;
using matrix::to_string;

string stringify(const char &c) {
  return string(1, c);
};

int main() {
  const size_t SIZE_MATRIX_1{4};
  array<array<char, SIZE_MATRIX_1>, SIZE_MATRIX_1> matrix1 {
    array<char, SIZE_MATRIX_1> {'A', 'B', 'C', 'D'},
    array<char, SIZE_MATRIX_1> {'E', 'F', 'G', 'H'},
    array<char, SIZE_MATRIX_1> {'I', 'J', 'K', 'L'},
    array<char, SIZE_MATRIX_1> {'M', 'N', 'O', 'P'}
  };

  const size_t SIZE_MATRIX_2{7};
  array<array<char, SIZE_MATRIX_2>, SIZE_MATRIX_2> matrix2 {
      array<char, SIZE_MATRIX_2> {'A', 'B', 'C', 'D', 'E', 'F', 'G'},
      array<char, SIZE_MATRIX_2> {'H', 'I', 'J', 'K', 'L', 'M', 'N'},
      array<char, SIZE_MATRIX_2> {'O', 'P', 'Q', 'R', 'S', 'T', 'U'},
      array<char, SIZE_MATRIX_2> {'V', 'W', 'X', 'Y', 'Z', 'a', 'b'},
      array<char, SIZE_MATRIX_2> {'c', 'd', 'e', 'f', 'g', 'h', 'i'},
      array<char, SIZE_MATRIX_2> {'j', 'k', 'l', 'm', 'n', 'o', 'p'},
      array<char, SIZE_MATRIX_2> {'q', 'r', 's', 't', 'u', 'v', 'w'}
  };

  cout << "Original matrix 1:" << endl;
  cout << matrix::to_string(matrix1, stringify) << endl;

  cout << "Rotated matrix 1:" << endl;
  rotate_90(matrix1);
  cout << matrix::to_string(matrix1, stringify) << endl;

  cout << "Original matrix 2:" << endl;
  cout << matrix::to_string(matrix2, stringify) << endl;

  cout << "Rotated matrix 2:" << endl;
  rotate_90(matrix2);
  cout << matrix::to_string(matrix2, stringify) << endl;

  return 0;
}