#include "containers.hpp"

#include <string>
#include <iostream>
#include <vector>
#include <deque>

using std::string;
using std::cout;
using std::endl;
using ints = std::vector<int>;
using std::vector;
using std::deque;

using containers::partition_string;
using containers::shortest_subsequence;
using containers::permute;
using containers::str_permute;
using containers::permutation_fn;
using containers::combine_inc;
using containers::all_substrings;

template<typename T>
void print_container (const T &container, bool print_endl = true);

int main() {
  cout << "=== palindromic partitions ===" << endl;
  string str{"nitingeeks"};

  for (const auto &partition : partition_string(str)) print_container(partition);

  cout << endl << "=== shortest subsequence ===" << endl;

  vector<ints> numbers {
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

  cout << endl << "=== permute ===" << endl;
  deque<string> string_permutations;
  permutation_fn fn{[&string_permutations](auto begin, auto end){
    string_permutations.push_back(string{begin, end});
  }};
  string pstr{"ABCD"};
  permute(pstr.begin(), pstr.end(), fn);
  cout << string_permutations.size() << ": ";
  print_container(string_permutations);

  cout << endl << "=== combine_inc ===" << endl;
  int a[]{10, 15, 25}, b[]{5, 20, 30};
  auto inc_combinations{combine_inc(a, a + (sizeof(a) / sizeof(int)), b,
                                    b + (sizeof(b) / sizeof(int)))};
  for(const auto &combination : inc_combinations) print_container(combination);

  cout << endl << "=== all_substrings ===" << endl;
  all_substrings("ABC");

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
