#include "derived_a.hpp"

std::string oop::derived_a::to_string() const noexcept { return "derived_a: " + std::to_string(timestamp()); }