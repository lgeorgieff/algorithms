#include "heap.hpp"

#include <iostream>
#include <cstddef>
#include <vector>
#include <algorithm>

using algorithms::heap;
using algorithms::heap_comp;

template<typename T>
void print_vector(std::vector<T> const &vector){
  std::for_each(vector.begin(), vector.end(), [](const auto &elem){
    std::cout << elem << " ";
  });
  std::cout << std::endl;
}

int main() {
  const size_t INTS_SIZE{17};
  int ints[INTS_SIZE]{20, 17, 11, 19, 14, 20, 13, 9, 15, 20, 10, 9, 9, 7, 3, 4, 8};
  heap<int, heap_comp<int>> h1{ints, ints + INTS_SIZE};

  std::cout << "internal data: ";
  print_vector(h1.data());

  std::cout << "popped data: ";
  while(!h1.empty()) std::cout << h1.pop() << " ";
  std::cout << std::endl;

  std::sort(ints, ints + INTS_SIZE);
  std::cout << "original data: ";
  std::for_each(ints, ints + INTS_SIZE, [](const auto &elem){ std::cout << elem << " "; });
  std::cout << std::endl;

  return 0;
}