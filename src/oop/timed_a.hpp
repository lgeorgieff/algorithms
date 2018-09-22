#pragma once

#include "timed_base.hpp"

namespace oop {
 class timed_a : public timed_base {
  public:
   std::string to_string() const noexcept override;
};
} // namespace oop