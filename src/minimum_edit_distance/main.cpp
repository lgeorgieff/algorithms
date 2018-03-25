#include "./minimum_edit_distance.hpp"

#include <iostream>
#include <string>

using med = low::minimum_edit_distance;
using std::cout;
using std::endl;

int main(const int argc, const char **argv) {
  med distance("execution", "intention", false);
  cout << "distance str1: " << distance.str1() << ", str2: " << distance.str2()
       << ": " << distance.distance() << endl
       << endl
       << distance.to_string() << endl;

  med levenshtein_distance("execution", "intention", true);
  cout << "levenshtein distance str1: " << levenshtein_distance.str1()
       << ", str2: " << levenshtein_distance.str2() << ": "
       << levenshtein_distance.distance() << endl
       << endl
       << levenshtein_distance.to_string() << endl;

  return 0;
}
