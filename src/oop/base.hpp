#pragma once

#include <chrono>
#include <string>

namespace oop {
class base {
 public:
  base() noexcept;
  base(const base &) = default;
  base(base &&) = default;
  base &operator=(const base &) = default;
  base &operator=(base &&) = default;
  ~base() = default;

  long timestamp() const noexcept;
  virtual std::string to_string() const noexcept;
 private:
  std::chrono::milliseconds timestamp_;
};
} // namespace oop