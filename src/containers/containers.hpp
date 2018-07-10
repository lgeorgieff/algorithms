#pragma once

#include <string>
#include <vector>

typedef std::vector<std::string> strings;

namespace containers {

std::vector<strings> partition_string(const std::string &str);

} // namespace containers