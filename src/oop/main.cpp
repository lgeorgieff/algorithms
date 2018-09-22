#include <iostream>

#include "base.hpp"
#include "derived_a.hpp"

using std::cout, std::endl;

int main() {
  oop::base base;
  oop::derived_a derived_a;
  cout << base.to_string() << endl;
  cout << derived_a.to_string() << endl;

  return 0;
}