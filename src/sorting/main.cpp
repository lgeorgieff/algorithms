#include "sorting.hpp"

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;
using sorting::randomize;
using sorting::bubble_sort;
using sorting::merge_sort;
using sorting::insertion_sort;

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

  cout << endl;
  randomize(ints, ints + SIZE);
  cout << "ints (randomize()): ";
  print_container(ints, ints + SIZE);
  merge_sort<int>(ints + 0, ints + SIZE);
  cout << "ints (merge_sort()): ";
  print_container(ints, ints + SIZE);

  cout << endl;
  randomize(ints, ints + SIZE);
  cout << "ints (randomize()): ";
  print_container(ints, ints + SIZE);
  insertion_sort<int>(ints + 0, ints + SIZE);
  cout << "ints (insertion_sort()): ";
  print_container(ints, ints + SIZE);







  return 0;
}



template <typename T>
void print_container(T begin, T end) {
  cout << "[ ";
  while(begin < end) {
    cout << *begin++;
    if (begin != end) cout << ", ";
    else cout << " ";
  }
  cout << "]" << endl;
}
