#include "node.hpp"
#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;

using algorithms::graph::node;

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
  return 0;
}