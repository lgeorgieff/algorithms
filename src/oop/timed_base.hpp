#pragma once

#include <chrono>
#include <string>

namespace oop {
class timed_base {
 public:
  timed_base() noexcept;
  timed_base(const timed_base &) noexcept = default;
  timed_base(timed_base &&) noexcept = default;
  timed_base &operator=(const timed_base &) noexcept = default;
  timed_base &operator=(timed_base &&) noexcept = default;
  virtual ~timed_base() noexcept = default;

  long timestamp() const noexcept;
  virtual std::string to_string() const noexcept = 0;
 private:
  std::chrono::milliseconds timestamp_;
};
} // namespace oop