#include "node.hpp"
#include "bsd.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;

using algorithms::graph::node;
using algorithms::graph::bsd_iterative;

int main() {
  std::shared_ptr n0{node<int>::create(123)};
  std::shared_ptr n1{node<int>::create(456)};
  std::shared_ptr n2{node<int>::create(789)};

  cout << "n0 empty: " << (n0->empty() ? "true" : "false") << " (" << n0->size() << ")" << endl;
  cout << "n1 empty: " << (n1->empty() ? "true" : "false") << " (" << n1->size() << ")" << endl;
  cout << "n2 empty: " << (n2->empty() ? "true" : "false") << " (" << n2->size() << ")" << endl;
  cout << "=== n0->connect(n1) ===" << endl;
  n0->connect(n1);
  cout << "n0 empty: " << (n0->empty() ? "true" : "false") << " (" << n0->size() << ")" << endl;
  cout << "n1 empty: " << (n1->empty() ? "true" : "false") << " (" << n1->size() << ")" << endl;
  cout << "n2 empty: " << (n2->empty() ? "true" : "false") << " (" << n2->size() << ")" << endl;
  cout << "=== n0->connect(n2) ===" << endl;
  n0->connect(n2);
  cout << "n0 empty: " << (n0->empty() ? "true" : "false") << " (" << n0->size() << ")" << endl;
  cout << "n1 empty: " << (n1->empty() ? "true" : "false") << " (" << n1->size() << ")" << endl;
  cout << "n2 empty: " << (n2->empty() ? "true" : "false") << " (" << n2->size() << ")" << endl;
  cout << "n0 is connected with n1: " << (n0->is_connected(n1) ? "true" : "false") << endl;
  cout << "n0 is connected with n2: " << (n0->is_connected(n2) ? "true" : "false") << endl;
  cout << "n0 connections: " << n0->connections().size() << endl;
  cout << "=== n0->disconnect(n1) ===" << endl;
  n0->disconnect(n1);
  cout << "n0 empty: " << (n0->empty() ? "true" : "false") << " (" << n0->size() << ")" << endl;
  cout << "n1 empty: " << (n1->empty() ? "true" : "false") << " (" << n1->size() << ")" << endl;
  cout << "n2 empty: " << (n2->empty() ? "true" : "false") << " (" << n2->size() << ")" << endl;
  cout << "n0 is connected with n1: " << (n0->is_connected(n1) ? "true" : "false") << endl;
  cout << "n0 is connected with n2: " << (n0->is_connected(n2) ? "true" : "false") << endl;
  cout << "n0 connections: " << n0->connections().size() << endl;
  cout << "=== n0->disconnect(n2) ===" << endl;
  n0->disconnect(n2);
  cout << "n0 empty: " << (n0->empty() ? "true" : "false") << " (" << n0->size() << ")" << endl;
  cout << "n1 empty: " << (n1->empty() ? "true" : "false") << " (" << n1->size() << ")" << endl;
  cout << "n2 empty: " << (n2->empty() ? "true" : "false") << " (" << n2->size() << ")" << endl;
  cout << "n0 is connected with n2: " << (n0->is_connected(n2) ? "true" : "false") << endl;
  cout << "n0 connections: " << n0->connections().size() << endl;
  cout << "=== node<int>::connect_sym(n0, n1) ===" << endl;
  node<int>::connect_sym(n0, n1);
  cout << "n0 empty: " << (n0->empty() ? "true" : "false") << " (" << n0->size() << ")" << endl;
  cout << "n1 empty: " << (n1->empty() ? "true" : "false") << " (" << n1->size() << ")" << endl;
  cout << "n2 empty: " << (n2->empty() ? "true" : "false") << " (" << n2->size() << ")" << endl;
  cout << "n0 is connected with n1: " << (n0->is_connected(n1) ? "true" : "false") << endl;
  cout << "n1 is connected with n0: " << (n1->is_connected(n0) ? "true" : "false") << endl;
  cout << "n0 connections: " << n0->connections().size() << endl;
  cout << "n1 connections: " << n1->connections().size() << endl;
  cout << "=== node<int>::disconnect_sym(n0, n1) ===" << endl;
  node<int>::disconnect_sym(n0, n1);
  cout << "n0 empty: " << (n0->empty() ? "true" : "false") << " (" << n0->size() << ")" << endl;
  cout << "n1 empty: " << (n1->empty() ? "true" : "false") << " (" << n1->size() << ")" << endl;
  cout << "n2 empty: " << (n2->empty() ? "true" : "false") << " (" << n2->size() << ")" << endl;
  cout << "n0 is connected with n1: " << (n0->is_connected(n1) ? "true" : "false") << endl;
  cout << "n1 is connected with n0: " << (n1->is_connected(n0) ? "true" : "false") << endl;
  cout << "n0 connections: " << n0->connections().size() << endl;
  cout << "n1 connections: " << n1->connections().size() << endl;

  cout << endl << "=== bsd_iterative ===" << endl;
  n0 = node<int>::create(0);
  n1 = node<int>::create(1);
  n2 = node<int>::create(2);
  std::shared_ptr<node<int>> n3{node<int>::create(3)};
  std::shared_ptr<node<int>> n4{node<int>::create(4)};
  std::shared_ptr<node<int>> n5{node<int>::create(5)};
  std::shared_ptr<node<int>> n6{node<int>::create(6)};
  std::shared_ptr<node<int>> n7{node<int>::create(7)};
  std::shared_ptr<node<int>> n8{node<int>::create(8)};
  std::shared_ptr<node<int>> n9{node<int>::create(9)};
  n0->connect(n1); n0->connect(n2); n0->connect(n3);
  n1->connect(n0); n1->connect(n4); n2->connect(n5); n3->connect(n5); n3->connect(n1);
  n4->connect(n6); n4->connect(n7); n5->connect(n8); n5->connect(n9);
  std::function<void(const int &, bool level_end)> fn{[](auto value, auto new_level){
    cout << (new_level ? "\n" : "") << value << " ";
  }};

  algorithms::graph::bsd_iterative(n0, fn);

  return 0;
}