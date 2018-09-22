#include <iostream>
#include <thread>
#include <chrono>

#include "base.hpp"
#include "derived_a.hpp"
#include "derived_b.hpp"

using std::cout, std::endl;
using std::chrono::seconds;

int main() {
  oop::base base;
  std::this_thread::sleep_for(seconds{1});
  oop::derived_a derived_a;
  std::this_thread::sleep_for(seconds{1});
  oop::derived_b derived_b;

  cout << base.to_string() << endl;
  cout << derived_a.to_string() << endl;
  cout << derived_b.to_string() << endl;

  return 0;
}