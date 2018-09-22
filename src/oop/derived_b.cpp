#include "derived_b.hpp"

std::string oop::derived_b::to_string() const noexcept { return "derived_b: " + std::to_string(timestamp()); }