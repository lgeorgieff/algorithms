#include "sorting.hpp"

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;
using sorting::bubble_sort;
using sorting::randomize;

template <typename T>
void print_container(T begin, T end);

int main() {
  const size_t SIZE{10};
  int ints[SIZE];
  for(size_t idx{0}; idx < SIZE; ++idx) ints[idx] = idx;
  randomize(ints, ints + SIZE);
  cout << "ints (randomize()): ";
  print_container(ints, ints + SIZE);

  bubble_sort<int>(ints + 0, ints + SIZE);
  cout << "ints (bubble_sort()): ";
  print_container(ints, ints + SIZE);








  return 0;
}



template <typename T>
void print_container(T begin, T end) {
  while(begin < end) cout << *begin++ << ", ";
  cout << endl;
}
