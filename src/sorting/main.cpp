#include "sorting.hpp"

#include <iostream>
#include <cstddef>

using std::cout;
using std::endl;
using sorting::randomize;
using sorting::bubble_sort;
using sorting::merge_sort;
using sorting::insertion_sort;
using sorting::quick_sort;

template <typename T>
void print_container(T begin, T end);

int main() {
  const size_t SIZE{15};
  const size_t MAX_VALUE{10};
  int ints[SIZE];
  for(size_t idx{0}; idx < SIZE; ++idx) ints[idx] = idx % (MAX_VALUE + 1);
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

  cout << endl;
  randomize(ints, ints + SIZE);
  cout << "ints (randomize()): ";
  print_container(ints, ints + SIZE);
  quick_sort<int>(ints, ints + SIZE);
  cout << "ints (quick_sort()): ";
  print_container(ints, ints + SIZE);
  const size_t SIZE_2{12};
  int ints2[SIZE_2]{0, 2, 4, 1, 3, 7, 4, 5, 9, 8, 7, 6};
  cout << "ints2 (randomize()): ";
  print_container(ints2, ints2 + SIZE_2);
  quick_sort<int>(ints2, ints2 + SIZE_2);
  cout << "ints2 (quick_sort()): ";
  print_container(ints2, ints2 + SIZE_2);

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
