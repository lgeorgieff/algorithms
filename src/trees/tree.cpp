#pragma once

#include "tree.hpp"

#include <algorithm>
#include <cmath>
#include <list>
#include <stack>
#include <stdexcept>
#include <utility>

namespace {
template<typename tkey, typename tvalue>
typename trees::tree<tkey, tvalue>::node *find_node(
    const tkey &key, typename trees::tree<tkey, tvalue>::node *current) {
  if (!current) {
    return nullptr;
  } else if (key == current->key) {
    return current;
  } else if (key < current->key && current->lnode) {
    return find_node<tkey, tvalue>(key, current->lnode);
  } else if (key > current->key && current->rnode) {
    return find_node<tkey, tvalue>(key, current->rnode);
  } else {
    return nullptr;
  }
}

template<typename tkey, typename tvalue>
void insert_value(const tkey &key, const tvalue &value,
                  typename trees::tree<tkey, tvalue>::node *current) {
  if (!current) {
    return;
  } else if (key == current->key) {
    current->value = value;
  } else if (key < current->key) {
    if (current->lnode) {
      return insert_value<tkey, tvalue>(key, value, current->lnode);
    } else {
      current->lnode = new typename trees::tree<tkey, tvalue>::node(key, value, 0, 0);
      current->lnode->parent = current;
    }
  } else if (key > current->key) {
    if (current->rnode) {
      return insert_value<tkey, tvalue>(key, value, current->rnode);
    } else {
      current->rnode = new typename trees::tree<tkey, tvalue>::node(key, value, 0, 0);
      current->rnode->parent = current;
    }
  }
}

template<typename tkey, typename tvalue>
typename trees::tree<tkey, tvalue>::node *find_left(
    typename trees::tree<tkey, tvalue>::node *node) {
  if (!node) return nullptr;
  if (node->lnode) {
    return find_left<tkey, tvalue>(node->lnode);
  } else {
    return node;
  }
}

std::string adapt_str_width(const std::string &str, size_t str_width) {
  size_t missing_count{std::max<size_t>(0, str_width - str.size())};
  std::string result{std::string(missing_count / 2, ' ') + str +
      std::string(missing_count / 2, ' ')};
  return missing_count % 2 ? result + " " : result;
}

template<typename T>
bool only_nulls(const std::list<T *> &lst) {
  if (lst.empty()) return false;
  for (auto t : lst)
    if (t) return false;
  return true;
}

template<typename tkey, typename tvalue>
void in_order_values(const typename trees::tree<tkey, tvalue>::node *node,
                     std::vector<tvalue> &accumulator) {
  if (!node) return;
  in_order_values<tkey, tvalue>(node->lnode, accumulator);
  accumulator.push_back(node->value);
  in_order_values<tkey, tvalue>(node->rnode, accumulator);
}

template<typename tkey, typename tvalue>
void pre_order_values(const typename trees::tree<tkey, tvalue>::node *node,
                      std::vector<tvalue> &accumulator) {
  if (!node) return;
  accumulator.push_back(node->value);
  pre_order_values<tkey, tvalue>(node->lnode, accumulator);
  pre_order_values<tkey, tvalue>(node->rnode, accumulator);
}

template<typename tkey, typename tvalue>
void post_order_values(const typename trees::tree<tkey, tvalue>::node *node,
                       std::vector<tvalue> &accumulator) {
  if (!node) return;
  post_order_values<tkey, tvalue>(node->lnode, accumulator);
  post_order_values<tkey, tvalue>(node->rnode, accumulator);
  accumulator.push_back(node->value);
}

template<typename tkey, typename tvalue>
void in_order_keys(const typename trees::tree<tkey, tvalue>::node *node,
                   std::vector<tkey> &accumulator) {
  if (!node) return;

  std::stack<const typename trees::tree<tkey, tvalue>::node *> storage;
  const typename trees::tree<tkey, tvalue>::node *current{node};
  bool done{false};
  while (!done) {
    if (current) {
      storage.push(current);
      current = current->lnode;
    } else {
      if (storage.empty()) {
        done = true;
      } else {
        accumulator.push_back(storage.top()->key);
        current = storage.top()->rnode;
        storage.pop();
      }
    }
  }
}

template<typename tkey, typename tvalue>
void pre_order_keys(const typename trees::tree<tkey, tvalue>::node *node,
                    std::vector<tkey> &accumulator) {
  if (!node) return;

  std::stack<const typename trees::tree<tkey, tvalue>::node *> storage;
  const typename trees::tree<tkey, tvalue>::node *current{node};
  bool done{false};
  while (!done) {
    if (current) {
      accumulator.push_back(current->key);
      storage.push(current);
      current = current->lnode;
    } else {
      if (storage.empty()) {
        done = true;
      } else {
        current = storage.top()->rnode;
        storage.pop();
      }
    }
  }
}

template<typename tkey, typename tvalue>
void post_order_keys(const typename trees::tree<tkey, tvalue>::node *node,
                     std::vector<tkey> &accumulator) {
  if (!node) return;

  std::stack<const typename trees::tree<tkey, tvalue>::node *> storage;
  storage.push(node);
  const typename trees::tree<tkey, tvalue>::node *prev{nullptr};
  while (!storage.empty()) {
    auto current{storage.top()};
    if (!prev || prev->lnode == current || prev->rnode == current) {
      if (current->lnode) {
        storage.push(current->lnode);
      } else if (current->rnode) {
        storage.push(current->rnode);
      }
    } else if (current->lnode == prev) {
      if (current->rnode) storage.push(current->rnode);
    } else {
      accumulator.push_back(storage.top()->key);
      storage.pop();
    }
    prev = current;
  }
}

template<typename tkey, typename tvalue>
void delete_nodes(typename trees::tree<tkey, tvalue>::node *root) {
  std::list<typename trees::tree<tkey, tvalue>::node *> container;
  if (root) container.push_back(root);
  while (!container.empty()) {
    if (container.front()->lnode) container.push_back(container.front()->lnode);
    if (container.front()->rnode) container.push_back(container.front()->rnode);
    typename trees::tree<tkey, tvalue>::node *tmp{container.front()};
    container.pop_front();
    delete tmp;
  }
}

template<typename tkey, typename tvalue>
typename trees::tree<tkey, tvalue>::node *copy_nodes(const typename trees::tree<tkey, tvalue>::node *root) {
  if (!root) return nullptr;
  using nnode = typename trees::tree<tkey, tvalue>::node;

  std::stack<std::pair<const nnode *, nnode *>> storage;
  const nnode *current_src{root};
  nnode *current_this{new nnode{*root}};
  nnode *this_root{current_this};
  bool done{false};
  while (!done) {
    if (current_src) {
      storage.push(std::pair<const nnode *, nnode *>(current_src, current_this));
      current_src = current_src->lnode;
      if (current_src) {
        current_this = new nnode{*current_src};
        current_this->parent = storage.top().second;
        storage.top().second->lnode = current_this;
      } else {
        current_this = nullptr;
      }
    } else {
      if (storage.empty()) {
        done = true;
      } else {
        auto top{storage.top()};
        current_src = top.first->rnode;
        if (current_src) {
          current_this = new nnode{*top.first->rnode};
          current_this->parent = top.second;
          top.second->rnode = current_this;
        } else {
          current_this = nullptr;
        }
        storage.pop();
      }
    }
  }
  return this_root;
}
}  // namespace

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue>::tree() : root_{nullptr}, size_{0} {}

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue>::tree(const tree &src) {
  if (this == &src) return;
  this->size_ = src.size();
  if (!this->size()) return;
  this->root_ = copy_nodes<tkey, tvalue>(src.root_);
}

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue>::tree(tree &&src)
    : root_{std::move(src.root_)}, size_{std::move(src.size_)} {}

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue> &trees::tree<tkey, tvalue>::operator=(const tree<tkey, tvalue> &other) {
  delete_nodes(this->root_);
  this->size_ = other.size_;
  this->root_ = copy_nodes(other.root_);
}

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue> &trees::tree<tkey, tvalue>::operator=(tree<tkey, tvalue> &&other) {
  delete_nodes(this->root_);
  this->size_ = std::move(other.size_);
  this->root_ = std::move(other.root_);
}

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue>::~tree() {
  delete_nodes<tkey, tvalue>(this->root_);
  this->size_ = 0;
  this->root_ = nullptr;
}

template<typename tkey, typename tvalue>
size_t trees::tree<tkey, tvalue>::size() const {
  return this->size_;
}

template<typename tkey, typename tvalue>
bool trees::tree<tkey, tvalue>::empty() const {
  return !this->size_;
}

template<typename tkey, typename tvalue>
std::vector<tvalue> trees::tree<tkey, tvalue>::values(enum order order) const {
  std::vector<tvalue> result;
  switch (order) {
    case order::in_order:in_order_values<tkey, tvalue>(this->root_, result);
      break;
    case order::pre_order:pre_order_values<tkey, tvalue>(this->root_, result);
      break;
    case order::post_order:post_order_values<tkey, tvalue>(this->root_, result);
      break;
    default:throw std::invalid_argument("unknown order: " + std::to_string(order));
  }

  return result;
}

template<typename tkey, typename tvalue>
std::vector<tkey> trees::tree<tkey, tvalue>::keys(enum order order) const {
  std::vector<tkey> result;
  switch (order) {
    case order::in_order:in_order_keys<tkey, tvalue>(this->root_, result);
      break;
    case order::pre_order:pre_order_keys<tkey, tvalue>(this->root_, result);
      break;
    case order::post_order:post_order_keys<tkey, tvalue>(this->root_, result);
      break;
    default:throw std::invalid_argument("unknown order: " + std::to_string(order));
  }
  return result;
}

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue> trees::tree<tkey, tvalue>::subtree(const tkey &start) const {
  // TODO: implement
  return *this;
}

template<typename tkey, typename tvalue>
bool trees::tree<tkey, tvalue>::has(const tkey &key) const {
  if (this->empty()) return false;

  std::list<node *> current_level;
  current_level.push_back(this->root_);
  while (!current_level.empty()) {
    node *n{current_level.front()};
    current_level.pop_front();
    if (n->key == key) return true;
    if (n->lnode) current_level.push_back(n->lnode);
    if (n->rnode) current_level.push_back(n->rnode);
  }

  return false;
}

template<typename tkey, typename tvalue>
bool trees::tree<tkey, tvalue>::has(const tree<tkey, tvalue> &tree) const {
  // TODO: implement
  return false;
}

template<typename tkey, typename tvalue>
void trees::tree<tkey, tvalue>::set(const tkey &key, const tvalue &value) {
  if (this->has(key)) {
    throw std::invalid_argument{"key \"" + std::to_string(key) + "\" is already set"};
  }

  if (this->empty()) {
    node *new_node{new node{key, value}};
    new_node->height = 0;
    new_node->height = 0;
    this->root_ = new_node;
  } else {
    insert_value<tkey, tvalue>(key, value, this->root_);
  }

  ++this->size_;
}

template<typename tkey, typename tvalue>
tvalue trees::tree<tkey, tvalue>::unset(const tkey &key) {
  typename trees::tree<tkey, tvalue>::node *node{find_node<tkey, tvalue>(key, this->root_)};
  if (!node) throw std::invalid_argument{"key \"" + std::to_string(key) + "\" is missing"};

  auto parent{node->parent};
  auto value{node->value};
  if (!node->lnode && !node->rnode) {
    if (parent && parent->lnode == node) {
      parent->lnode = nullptr;
    } else if (parent) {
      parent->rnode = nullptr;
    } else {
      this->root_ = nullptr;
    }
  } else if (!node->lnode) {
    if (parent && parent->lnode == node) {
      parent->lnode = node->rnode;
    } else if (parent) {
      parent->rnode = node->rnode;
    } else {
      this->root_ = node->rnode;
    }
  } else if (!node->rnode) {
    if (parent && parent->lnode == node) {
      parent->rnode = node->lnode;
    } else if (parent) {
      parent->rnode = node->lnode;
    } else {
      this->root_ = node->lnode;
    }
  } else {
    auto replacement{find_left<tkey, tvalue>(node->rnode)};
    if (replacement != node->rnode) {
      if (replacement->rnode) {
        replacement->parent->lnode = replacement->rnode;
        replacement->rnode->parent = replacement->parent;
      } else {
        replacement->parent->lnode = nullptr;
      }
      replacement->lnode = node->lnode;
      node->lnode->parent = replacement;
      replacement->rnode = node->rnode;
      node->rnode->parent = replacement;
    } else {
      replacement->lnode = node->lnode;
      node->lnode->parent = replacement;
    }
    if (parent && parent->lnode == node) {
      parent->lnode = replacement;
    } else if (parent) {
      parent->rnode = replacement;
    } else {
      this->root_ = replacement;
    }
    replacement->parent = parent;
  }
  delete node;
  --this->size_;
  return value;
}

template<typename tkey, typename tvalue>
tvalue &trees::tree<tkey, tvalue>::operator[](const tkey &key) {
  auto node{find_node<tkey, tvalue>(key, this->root_)};
  if (!node) throw std::invalid_argument{"key \"" + std::to_string(key) + "\" is missing"};
  return node->value;
}

template<typename tkey, typename tvalue>
const tvalue &trees::tree<tkey, tvalue>::operator[](const tkey &key) const {
  return this[key];
}

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue> trees::tree<tkey, tvalue>::find_longest_subtree(
    const tree<tkey, tvalue> &other) const {
  // TODO: implement
  *this;
}

template<typename tkey, typename tvalue>
std::string trees::tree<tkey, tvalue>::to_string(std::function<std::string(tvalue, bool)> to_str_fn,
                                                 char space) const {
  const size_t VALUE_WIDTH{5}, MIN_SPACE_WIDTH{2};
  std::string result{};
  size_t max_str_width{static_cast<size_t>(pow(2, this->depth())) *
      (VALUE_WIDTH + MIN_SPACE_WIDTH)};

  std::list<typename tree<tkey, tvalue>::node *> current_level;
  if (this->root_) current_level.push_back(this->root_);
  while (!current_level.empty()) {
    std::list<typename tree<tkey, tvalue>::node *> tmp;
    int fill_width_((max_str_width - (current_level.size() * (VALUE_WIDTH + MIN_SPACE_WIDTH))) /
        (current_level.size() + 1));
    size_t fill_width(fill_width_ >= 0 ? fill_width_ : 0);
    while (!current_level.empty()) {
      result += std::string(fill_width, space);
      if (!current_level.front()) {
        tmp.push_back(nullptr);
        tmp.push_back(nullptr);
        result += std::string(VALUE_WIDTH + MIN_SPACE_WIDTH, ' ');
      } else {
        result += adapt_str_width(to_str_fn(current_level.front()->value, false),
                                  VALUE_WIDTH + MIN_SPACE_WIDTH);
        if (current_level.front()->lnode) {
          tmp.push_back(current_level.front()->lnode);
        } else {
          tmp.push_back(nullptr);
        }
        if (current_level.front()->rnode) {
          tmp.push_back(current_level.front()->rnode);
        } else {
          tmp.push_back(nullptr);
        }
      }
      current_level.pop_front();
    }

    result += std::string(fill_width, space);
    result += '\n';
    if (only_nulls(tmp)) {
      current_level.clear();
    } else {
      current_level.swap(tmp);
    }
  }

  return result;
}

template<typename tkey, typename tvalue>
size_t trees::tree<tkey, tvalue>::depth() const {
  size_t result{0};
  std::vector<typename trees::tree<tkey, tvalue>::node *> storage;
  storage.push_back(this->root_);
  while (!storage.empty()) {
    std::vector<typename trees::tree<tkey, tvalue>::node *> level;
    for (const auto node : storage) {
      if (node->lnode) level.push_back(node->lnode);
      if (node->rnode) level.push_back(node->rnode);
    }
    storage.swap(level);
    ++result;
  }
  return result;
}

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue>::node::node(const tkey &key, const tvalue &value, size_t height,
                                      size_t depth, node *lnode, node *rnode, node *parent)
    : key{key},
      value{value},
      height{height},
      depth{depth},
      lnode{lnode},
      rnode{rnode},
      parent{parent} {}

template<typename tkey, typename tvalue>
trees::tree<tkey, tvalue>::node::node(const typename trees::tree<tkey, tvalue>::node::node &src)
    : key{src.key},
      value{src.value},
      height{src.height},
      depth{src.depth},
      lnode{nullptr},
      rnode{nullptr},
      parent{nullptr} {}

template<typename tkey, typename tvalue>
size_t trees::tree<tkey, tvalue>::node::left_height() const {
  return this->lnode ? this->lnode->height + 1 : 0;
}

template<typename tkey, typename tvalue>
size_t trees::tree<tkey, tvalue>::node::right_height() const {
  return this->rnode ? this->rnode->height + 1 : 0;
}
