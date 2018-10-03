#include "node.hpp"
#include "bfs.hpp"
#include "dfs.hpp"
#include "dijkstra.hpp"
#include "bellman_ford.hpp"
#include "kruskal.hpp"
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
using algorithms::graph::matrix_t;
using algorithms::graph::dijkstra_distance;
using algorithms::graph::bellman_ford_distance;
using algorithms::graph::kruskal_mst;
using algorithms::graph::INFINITE;
using algorithms::graph::print_matrix;
template<typename T>
using simple_node = algorithms::simple_graph::node<T>;
using algorithms::simple_graph::print_pre_order_rec;
using algorithms::simple_graph::print_in_order_rec;
using algorithms::simple_graph::print_post_order_rec;
using algorithms::simple_graph::print_pre_order_iter;
using algorithms::simple_graph::print_in_order_iter;
using algorithms::simple_graph::print_post_order_iter;
using algorithms::simple_graph::print_breadth_first;
using algorithms::simple_graph::print_depths_first;

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

  {
    cout << endl << "=== dijkstra 1 ===" << endl;
    const size_t GRAPH_SIZE{6};

    matrix_t<GRAPH_SIZE> matrix{
        array<int32_t, GRAPH_SIZE>{0, 2, 4, INFINITE, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, 0, 1, 4, 2, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, 0, INFINITE, 3, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, 0, INFINITE, 2},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, 3, 0, 2},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 0}
    };

    array<int32_t, GRAPH_SIZE> distances{dijkstra_distance<GRAPH_SIZE>(matrix, 0)};
    for (size_t node{0}; node < distances.size(); ++node)
      cout << "distance from 0 to " << node << ": " << distances[node] << endl;
  }

  {
    cout << endl << "=== dijkstra 2 ===" << endl;
    const size_t GRAPH_SIZE{9};

    matrix_t<GRAPH_SIZE> matrix{
        array<int32_t, GRAPH_SIZE>{0, 4, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 8, INFINITE},
        array<int32_t, GRAPH_SIZE>{4, 0, 8, INFINITE, INFINITE, INFINITE, INFINITE, 11, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, 8, 0, 7, INFINITE, 4, INFINITE, 7, 2},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, 7, 0, 9, 14, INFINITE, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, 9, 0, 10, INFINITE, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, 4, 14, 10, 0, 2, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 2, 0, 1, 6},
        array<int32_t, GRAPH_SIZE>{8, 11, 7, INFINITE, INFINITE, INFINITE, 1, 0, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, 2, INFINITE, INFINITE, INFINITE, 6, INFINITE, 0}
    };

    array<int32_t, GRAPH_SIZE> distances{dijkstra_distance<GRAPH_SIZE>(matrix, 0)};
    for (size_t node{0}; node < distances.size(); ++node)
      cout << "distance from 0 to " << node << ": " << distances[node] << endl;
  }

  {
    cout << endl << "=== bellman ford ===" << endl;
    const size_t GRAPH_SIZE{10};

    matrix_t<GRAPH_SIZE> matrix{
        array<int32_t, GRAPH_SIZE>{0, 5, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, 0, 20, INFINITE, INFINITE, 30, 60, INFINITE, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, 0, 10, 75, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, -15, 0, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, 0, INFINITE, INFINITE, INFINITE, INFINITE, 100},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 0, 5, INFINITE, 50, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 0, -50, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 0, -10, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 0, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, INFINITE, 0}
    };

    array<int32_t, GRAPH_SIZE> distances{bellman_ford_distance<GRAPH_SIZE>(matrix, 0, false)};
    for (size_t node{0}; node < distances.size(); ++node)
      cout << "distance from 0 to " << node << ": " << distances[node] << endl;
  }

  {
    cout << endl << "=== kruskal ===" << endl;
    const size_t GRAPH_SIZE{7};

    matrix_t<GRAPH_SIZE> matrix{
        array<int32_t, GRAPH_SIZE>{0, 7, INFINITE, 5, INFINITE, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{7, 0, 8, 9, 7, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, 8, 0, INFINITE, 5, INFINITE, INFINITE},
        array<int32_t, GRAPH_SIZE>{5, 9, INFINITE, 0, 15, 6, INFINITE},
        array<int32_t, GRAPH_SIZE>{INFINITE, 7, 5, 15, 0, 8, 9},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, 6, 8, 0, 11},
        array<int32_t, GRAPH_SIZE>{INFINITE, INFINITE, INFINITE, INFINITE, 9, 11, 0}
    };

    matrix_t<GRAPH_SIZE> spanning_tree{kruskal_mst<GRAPH_SIZE>(matrix)};
    print_matrix(std::cout, spanning_tree, 2);
    cout << endl;
  }

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
    cout << "print_pre_order_rec:  "; print_pre_order_rec(simple_tree); cout << endl;
    cout << "print_pre_order_iter: "; print_pre_order_iter(simple_tree); cout << endl;
    cout << "print_in_order_rec:  "; print_in_order_rec(simple_tree); cout << endl;
    cout << "print_in_order_iter: "; print_in_order_iter(simple_tree); cout << endl;
    cout << "print_post_order_rec:  "; print_post_order_rec(simple_tree); cout << endl;
    cout << "print_post_order_iter: "; print_post_order_iter(simple_tree); cout << endl;

    delete simple_tree, delete n1, delete n2, delete n3, delete n4, delete n5, delete n6, delete n7, delete n8,
        delete n9, delete n10;
  }

  {
    cout << endl << "=== simple graph ===" << endl;
    simple_node<int> *simple_graph{new simple_node<int>{0}};
    auto *n1{simple_graph->link(1)};
    auto *n6{n1->link(6)};
    auto *n7{n1->link(7)};
    auto *n8{n7->link(8)};
    auto *n2{simple_graph->link(2)};
    auto *n3{n2->link(3)}; n3->link(n2); n3->link(simple_graph);
    auto *n4{n3->link(4)}; n4->link(simple_graph); n4->link(n3);
    auto *n5{n4->link(5)};
    cout << "print_breadth_first: "; print_breadth_first(simple_graph); cout << endl;
    cout << "print_breadth_first: "; print_depths_first(simple_graph); cout << endl;

    delete simple_graph, delete n1, delete n2, delete n3, delete n4, delete n5, delete n6, delete n7, delete n8;
  }
  return 0;
}