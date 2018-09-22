#include "timed_base.hpp"

oop::timed_base::timed_base() noexcept
  :timestamp_{std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now()
  .time_since_epoch())} {}

long oop::timed_base::timestamp() const noexcept { return timestamp_.count(); }

std::string oop::timed_base::to_string() const noexcept { return "timed_base: " + std::to_string(timestamp()); }