#pragma once

#include "timed_base.hpp"

namespace oop {
class timed_b : public timed_base {
 public:
  std::string to_string() const noexcept override;
};
} // namespace oop