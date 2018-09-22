#include "timed_b.hpp"

std::string oop::timed_b::to_string() const noexcept { return "timed_b: " + std::to_string(timestamp()); }