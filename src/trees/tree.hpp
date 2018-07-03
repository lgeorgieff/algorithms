#pragma once

#include <cstddef>
#include <vector>
#include <functional>

namespace trees {

  template <typename tkey, typename tvalue>
class tree {
 public:
  struct node;

  enum order { in_order, pre_order, post_order };

  tree();
  tree(const tree &src);
  tree(tree &&src);
  tree<tkey, tvalue> &operator=(const tree<tkey, tvalue> &other);
  tree<tkey, tvalue> &operator=(tree<tkey, tvalue> &&other);
  virtual ~tree();

  size_t size() const;
  bool empty() const;
  std::vector<tvalue> values(enum order = order::in_order) const;
  std::vector<tkey> keys(enum order = order::in_order) const;
  tree<tkey, tvalue> subtree(const tkey &start) const;
  bool has(const tkey &key) const;
  bool has(const tree<tkey, tvalue> &tree) const;
  virtual void set(const tkey &key, const tvalue &value);
  virtual tvalue unset(const tkey &key);
  tvalue &operator[](const tkey &key);
  const tvalue &operator[](const tkey &key) const;
  tree<tkey, tvalue> find_longest_subtree(const tree<tkey, tvalue> &other) const;
  std::string to_string(std::function<std::string(tvalue, bool)> to_str_fn,
                        char space = '.') const;
  size_t depth() const;

 private:
  node *root_;
  size_t size_;

 public:
  struct node {
    node(const tkey &key, const tvalue &value, size_t height = 0, size_t depth = 0,
         node *lnode = nullptr, node *rnode = nullptr, node *parent = nullptr);
    node(const node &src);
    tkey key;
    tvalue value;
    size_t height;
    size_t depth;
    node *lnode;
    node *rnode;
    node *parent;

    size_t left_height() const;
    size_t right_height() const;
  };  // struct node
};    // class tree

}  // namespace trees

#include "tree.cpp"
