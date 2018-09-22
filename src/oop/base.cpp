#include "base.hpp"

oop::base::base() noexcept
  :timestamp_{std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
  .time_since_epoch())} {}

long oop::base::timestamp() const noexcept { return timestamp_.count(); }

std::string oop::base::to_string() const noexcept { return "base:      " + std::to_string(timestamp()); }