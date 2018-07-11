#pragma once

#include <string>
#include <vector>
#include <deque>

typedef std::vector<std::string> strings;

namespace containers {

std::vector<strings> partition_string(const std::string &str);


std::deque<int> shortest_subsequence(std::vector<int>::const_iterator begin,
                                     std::vector<int>::const_iterator end, int threshold);

} // namespace containers