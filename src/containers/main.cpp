#include "containers.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;
using ints = std::vector<int>;

using containers::partition_string;
using containers::shortest_subsequence;

template<typename T>
void print_container (const T &container, bool print_endl = true);

int main() {
  cout << "=== palindromic partitions ===" << endl;
  string str{"nitingeeks"};

  for (const auto &partition : partition_string(str)) print_container(partition);

  cout << endl << "=== shortest subsequence ===" << endl;

  std::vector<ints> numbers {
      {1, 4, 45, 6, 0, 19},
      {1, 10, 5, 2, 7},
      {1, 11, 100, 1, 0, 200, 3, 2, 1, 250},
      {1, 2, 4}
  };
  ints thresholds{51, 9, 280, 8};
  auto threshold_iter{thresholds.cbegin()};
  for(auto ints_iter{numbers.cbegin()};
      ints_iter < numbers.cend() && threshold_iter < thresholds.cend();
      ++ints_iter, ++threshold_iter) {
    print_container(*ints_iter, false);
    cout << " [" << *threshold_iter << "] --> ";
    print_container(shortest_subsequence(ints_iter->cbegin(), ints_iter->cend(), *threshold_iter));
  }

  return 0;
}

template<typename T>
void print_container (const T &container, bool print_endl) {
  if (container.empty()) {
    if (print_endl) cout << endl;
    return;
  }
  auto last{--container.cend()};
  for(auto iter{container.cbegin()}; iter < container.cend(); ++iter) {
    cout << *iter;
    if (iter == last && print_endl) cout << endl;
    else cout << " ";
  }
}