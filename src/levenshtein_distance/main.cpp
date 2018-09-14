#include "./levenshtein_distance.hpp"

#include <iostream>
#include <string>

using low::levenshtein_distance;
using std::cout;
using std::endl;

int main() {
  levenshtein_distance distance1("execution", "intention");
  cout << "distance(1, 1, 1) str1: " << distance1.str1()
       << ", str2: " << distance1.str2() << ": " << distance1.distance() << endl
       << endl
       << distance1.to_string() << endl;

  struct levenshtein_distance::config config2({1, 1, 2});
  levenshtein_distance distance2("execution", "intention", config2);
  cout << "distance(1, 1, 2) str1: " << distance2.str1()
       << ", str2: " << distance2.str2() << ": " << distance2.distance() << endl
       << endl
       << distance2.to_string() << endl;

  struct levenshtein_distance::config config3({1, 2, 1});
  levenshtein_distance distance3("execution", "intention", config3);
  cout << "distance(1, 2, 1) str1: " << distance3.str1()
       << ", str2: " << distance3.str2() << ": " << distance3.distance() << endl
       << endl
       << distance3.to_string() << endl;

  struct levenshtein_distance::config config4({2, 1, 1});
  levenshtein_distance distance4("execution", "intention", config4);
  cout << "distance(2, 1, 1) str1: " << distance4.str1()
       << ", str2: " << distance4.str2() << ": " << distance4.distance() << endl
       << endl
       << distance4.to_string() << endl;

  struct levenshtein_distance::config config5({2, 2, 2});
  levenshtein_distance distance5("execution", "intention", config5);
  cout << "distance(2, 2, 2) str1: " << distance5.str1()
       << ", str2: " << distance5.str2() << ": " << distance5.distance() << endl
       << endl
       << distance5.to_string() << endl;

  struct levenshtein_distance::config config6({2, 2, 1});
  levenshtein_distance distance6("execution", "intention", config6);
  cout << "distance(2, 2, 2) str1: " << distance6.str1()
       << ", str2: " << distance6.str2() << ": " << distance6.distance() << endl
       << endl
       << distance6.to_string() << endl;


  return 0;
}
