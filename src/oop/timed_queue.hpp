#pragma once

#include "timed_base.hpp"
#include "timed_a.hpp"
#include "timed_b.hpp"

#include <list>
#include <memory>
#include <cstddef>

namespace oop {
class timed_queue {
 public:
  timed_queue() noexcept = default;
  timed_queue(const timed_queue &source) noexcept;
  timed_queue(timed_queue &&) noexcept = default;
  timed_queue &operator=(const timed_queue &source) noexcept;
  timed_queue &operator=(timed_queue &&) noexcept = default;
  ~timed_queue() noexcept;

  void push(const timed_base &elem) noexcept;
  std::unique_ptr<timed_base> pop();
  std::unique_ptr<timed_a> pop_a();
  std::unique_ptr<timed_b> pop_b();
  bool empty() const noexcept;
  bool has_a() const noexcept;
  bool has_b() const noexcept;
  size_t size() const noexcept;
  std::string to_string() const noexcept;
 private:
  std::list<timed_a *> a_;
  std::list<timed_b *> b_;
};
} // namespace oop