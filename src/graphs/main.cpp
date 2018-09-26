#include "node.hpp"
#include "bfs.hpp"
#include "dfs.hpp"
#include "dijsktra.hpp"
#include "simple_node.hpp"

#include <iostream>

using std::cout;
using std::endl;
using std::shared_ptr;
using std::function;
using std::array;

using algorithms::graph::node;
using algorithms::graph::bfs_iterative;
using algorithms::graph::bfs_recursive;
using algorithms::graph::dfs_iterative;
using algorithms::graph::dfs_recursive;
using algorithms::graph::graph_matrix;
using algorithms::graph::dijkstra_distance;
using algorithms::graph::INFINITE;
template<typename T>
using simple_node = algorithms::simple_graph::node<T>;
using algorithms::simple_graph::print_pre_order_rec;
using algorithms::simple_graph::print_in_order_rec;

int main() {
  shared_ptr n0{node<int>::create(123)};
  shared_ptr n1{node<int>::create(456)};
  shared_ptr n2{node<int>::create(789)};

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

  cout << endl << "=== bfs_iterative ===" << endl;
  n0 = node<int>::create(0);
  n1 = node<int>::create(1);
  n2 = node<int>::create(2);
  shared_ptr<node<int>> n3{node<int>::create(3)};
  shared_ptr<node<int>> n4{node<int>::create(4)};
  shared_ptr<node<int>> n5{node<int>::create(5)};
  shared_ptr<node<int>> n6{node<int>::create(6)};
  shared_ptr<node<int>> n7{node<int>::create(7)};
  shared_ptr<node<int>> n8{node<int>::create(8)};
  shared_ptr<node<int>> n9{node<int>::create(9)};
  n0->connect(n1); n0->connect(n2); n0->connect(n3);
  n1->connect(n0); n1->connect(n4); n2->connect(n5); n3->connect(n5); n3->connect(n1);
  n4->connect(n6); n4->connect(n7); n5->connect(n8); n5->connect(n9);
  function<void(const int &, bool level_end)> fn_bfs{[](auto value, auto new_level){
    cout << (new_level ? "\n" : "") << value << " ";
  }};

  bfs_iterative(n0, fn_bfs);
  cout << endl;

  cout << endl << "=== bfs_recursive ===" << endl;
  bfs_recursive(n0, fn_bfs);
  cout << endl;

  cout << endl << "=== dfs_iterative ===" << endl;
  std::function<void(const int &)> fn_dfs{[](auto value){
    cout << value << " ";
  }};
  dfs_iterative(n0, fn_dfs);
  cout << endl;

  cout << endl << "=== dfs_recursive ===" << endl;
  dfs_recursive(n0, fn_dfs);
  cout << endl;

  cout << endl << "=== dijkstra ===" << endl;
  const size_t GRAPH_SIZE{6};

  graph_matrix<GRAPH_SIZE> matrix{
      array<size_t, GRAPH_SIZE>{0, 2, 4, INFINITE, INFINITE, INFINITE},
      array<size_t, GRAPH_SIZE>{INFINITE, 0, 1, 4, 2, INFINITE},
      array<size_t, GRAPH_SIZE>{INFINITE, INFINITE, 0, INFINITE, 3, INFINITE},
      array<size_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, 0, INFINITE, 2},
      array<size_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, 3, 0, 2},
      array<size_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 0}
  };

  array<size_t, GRAPH_SIZE> distances{dijkstra_distance<GRAPH_SIZE>(matrix, 0)};
  for (size_t node{0}; node < distances.size(); ++node)
    cout << "distance from 0 to " << node << ": " << distances[node] << endl;

  {
    cout << endl << "=== simple tree ===" << endl;
    simple_node<int> *simple_tree{new simple_node<int>{0}};
    auto *n1{simple_tree->link(1)};
    auto *n3{n1->link(3)};
    auto *n4{n1->link(4)};
    auto *n7{n4->link(7)};
    auto *n2{simple_tree->link(2)};
    auto *n5{n2->link(5)};
    auto *n8{n5->link(8)};
    auto *n10{n8->link(10)};
    auto *n6{n2->link(6)};
    auto *n9{n6->link(9)};
    cout << "print_pre_order_rec: "; print_pre_order_rec(simple_tree); cout << endl;
    cout << "print_in_order_rec: "; print_in_order_rec(simple_tree); cout << endl;
    cout << "print_post_order_rec: "; print_post_order_rec(simple_tree); cout << endl;

    delete simple_tree, delete n1, delete n2, delete n3, delete n4, delete n5, delete n6, delete n7, delete n8,
        delete n9, delete n10;
  }
  return 0;
}