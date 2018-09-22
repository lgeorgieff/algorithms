#include "timed_queue.hpp"

#include <algorithm>
#include <cstddef>
#include <stdexcept>

namespace {
template<typename T>
T *pop_front_from_list(std::list<T *> &lst) {
  T *elem{lst.front()};
  lst.pop_front();
  return elem;
}
} // anonymous namespace

oop::timed_queue::timed_queue(const timed_queue &source) noexcept :a_{}, b_{} {
  std::for_each(source.a_.begin(), source.a_.end(), [this](timed_a * const a){
    this->a_.push_back(new timed_a{*a});
  });
  std::for_each(source.b_.begin(), source.b_.end(), [this](timed_b * const b){
    this->b_.push_back(new timed_b{*b});
  });
}

oop::timed_queue &oop::timed_queue::operator=(const timed_queue &source) noexcept {
  std::for_each(source.a_.begin(), source.a_.end(), [this](timed_a * const a){
    this->a_.push_back(new timed_a{*a});
  });
  std::for_each(source.b_.begin(), source.b_.end(), [this](timed_b * const b){
    this->b_.push_back(new timed_b{*b});
  });
  return *this;
}

oop::timed_queue::~timed_queue() noexcept {
  while(!a_.empty()) {
    delete a_.front();
    a_.pop_front();
  }
  while(!b_.empty()) {
    delete b_.front();
    b_.pop_front();
  }
}

void oop::timed_queue::push(const oop::timed_base &elem) noexcept {
  if(typeid(elem) == typeid(timed_a)) {
    a_.push_back(new timed_a(dynamic_cast<const timed_a &>(elem)));
  } else if(typeid(elem) == typeid(timed_b)) {
    b_.push_back(new timed_b{dynamic_cast<const timed_b &>(elem)});
  }
}

std::string oop::timed_queue::to_string() const noexcept {
  std::string result{"timed_a\n"};
  if(!a_.empty()) result += '\t';
  size_t counter{0};
  for(const auto *a : a_) {
    if(counter == 3) {
      result += "\n\t";
      counter = 0;
    }
    result += a->to_string() + ", ";
    ++counter;
  }
  if(!a_.empty()) result += '\n';
  result += "timed_b\n";
  if(!b_.empty()) result += '\t';
  counter = 0;
  for(const auto *b : b_) {
    if(counter == 3) {
      result += "\n\t";
      counter = 0;
    }
    result += b->to_string() + ", ";
    ++counter;
  }
  return result;
}

std::unique_ptr<oop::timed_a> oop::timed_queue::pop_a() {
  if(a_.empty()) throw std::runtime_error{"\"a\" queue is empty"};
  return std::unique_ptr<timed_a>{pop_front_from_list(a_)};
}

std::unique_ptr<oop::timed_b> oop::timed_queue::pop_b() {
  if(b_.empty()) throw std::runtime_error{"\"b\" queue is empty"};
  return std::unique_ptr<timed_b>{pop_front_from_list(b_)};
}

std::unique_ptr<oop::timed_base> oop::timed_queue::pop() {
  std::unique_ptr<timed_base> tmp{nullptr};
  if(!a_.empty() && !b_.empty()) {
    if(a_.front()->timestamp() < b_.front()->timestamp()) tmp.reset(pop_front_from_list(a_));
    else tmp.reset(pop_front_from_list(b_));
  } else if(!a_.empty()) {
    tmp.reset(pop_front_from_list(a_));
  } else if(!b_.empty()) {
    tmp.reset(pop_front_from_list(b_));
  }
  if(!tmp) throw std::runtime_error{"\"a\" and \"b\" queues are empty"};
  return tmp;
}

size_t oop::timed_queue::size() const noexcept {
  return a_.size() + b_.size();
}

bool oop::timed_queue::empty() const noexcept {
  return a_.empty() && b_.empty();
}
bool oop::timed_queue::has_a() const noexcept {
  return a_.empty();
}

bool oop::timed_queue::has_b() const noexcept {
  return b_.empty();
}
