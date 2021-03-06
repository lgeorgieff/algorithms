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
using containers::is_permutation;
using containers::is_palindrome_permutation;

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

  cout << endl << "=== is_permutation ===" << endl;
  {
    string str1{"abcdefghABCI"}, str2{"ABabCcIdhegf"}, str3{"cdeABabfCghI"}, str4{"abcdefghBBCI"}, str5{"abcdefghBCI"};
    cout << str1 << " <> " << str1 << " -> " << (is_permutation(str1, str1) ? "true" : "false") << endl;
    cout << str1 << " <> " << str2 << " -> " << (is_permutation(str1, str2) ? "true" : "false") << endl;
    cout << str1 << " <> " << str3 << " -> " << (is_permutation(str1, str3) ? "true" : "false") << endl;
    cout << str1 << " <> " << str4 << " -> " << (is_permutation(str1, str4) ? "true" : "false") << endl;
    cout << str1 << " <> " << str5 << " -> " << (is_permutation(str1, str5) ? "true" : "false") << endl;
  }
  cout << endl << "=== is_palindrome_permutation ===" << endl;
  {
    string str1{"abCab"}, str2{"dadaBBBccdd"}, str3{"a"}, str4{"xx"}, str5{""}, str6{"abbc"}, str7{"aabbccayyb"},
    str8{"abc"};
    cout << "_" << str1 << "_ -> " << (is_palindrome_permutation(str1) ? "true" : "false") << endl;
    cout << "_" << str2 << "_ -> " << (is_palindrome_permutation(str2) ? "true" : "false") << endl;
    cout << "_" << str3 << "_ -> " << (is_palindrome_permutation(str3) ? "true" : "false") << endl;
    cout << "_" << str4 << "_ -> " << (is_palindrome_permutation(str4) ? "true" : "false") << endl;
    cout << "_" << str5 << "_ -> " << (is_palindrome_permutation(str5) ? "true" : "false") << endl;
    cout << "_" << str6 << "_ -> " << (is_palindrome_permutation(str6) ? "true" : "false") << endl;
    cout << "_" << str7 << "_ -> " << (is_palindrome_permutation(str7) ? "true" : "false") << endl;
    cout << "_" << str8 << "_ -> " << (is_palindrome_permutation(str8) ? "true" : "false") << endl;
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
