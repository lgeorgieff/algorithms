#pragma once

#include "base.hpp"

namespace oop {
 class derived_a : public base {
  public:
   std::string to_string() const noexcept override;
};
} // namespace oop