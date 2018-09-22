#pragma once

#include "base.hpp"
#include "derived_a.hpp"
#include "derived_b.hpp"

#include "forward_list"

namespace oop {
class mixed_queue {
 public:
  mixed_queue() noexcept;
  mixed_queue(const mixed_queue &other) noexcept;
  mixed_queue(mixed_queue &&other) noexcept;
  mixed_queue &operator=(const mixed_queue &other) noexcept;
  mixed_queue &operator=(mixed_queue &&other) noexcept;
  ~mixed_queue() noexcept;

  void push(const base &elem) noexcept;
  base *pop();
  derived_a *pop_a();
  derived_b *pop_b();
 private:
  std::forward_list<derived_a> a_;
  std::forward_list<derived_b> b_;
};
} // namespace oop