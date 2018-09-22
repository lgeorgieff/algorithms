#include <iostream>
#include <thread>
#include <chrono>

#include "timed_base.hpp"
#include "timed_a.hpp"
#include "timed_b.hpp"
#include "timed_queue.hpp"

using std::cout, std::endl;
using std::chrono::milliseconds;

int main() {
  oop::timed_queue mixed_queue;
  for(unsigned short i{0}; i < 11; ++i) {
    mixed_queue.push(oop::timed_a{});
    std::this_thread::sleep_for(milliseconds{123});
    mixed_queue.push(oop::timed_b{});
    std::this_thread::sleep_for(milliseconds{123});
  }

  cout << mixed_queue.to_string() << endl << endl;

  cout << "pop()" << endl;
  while(mixed_queue.size() > 10) {
    auto tmp{mixed_queue.pop()};
    cout << "\t[" << mixed_queue.size() + 1 << "]: " << tmp->to_string() << endl;
  }

  cout << endl << "pop_a()" << endl;
  while(!mixed_queue.has_a()) {
    auto tmp{mixed_queue.pop_a()};
    cout << "\t[" << mixed_queue.size() + 1 << "]: " << tmp->to_string() << endl;
  }

  cout << endl << "pop_b()" << endl;
  while(!mixed_queue.has_b()) {
    auto tmp{mixed_queue.pop_b()};
    cout << "\t[" << mixed_queue.size() + 1 << "]: " << tmp->to_string() << endl;
  }

  return 0;
}