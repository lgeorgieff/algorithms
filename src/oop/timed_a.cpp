#include "timed_a.hpp"

std::string oop::timed_a::to_string() const noexcept { return "timed_a: " + std::to_string(timestamp()); }