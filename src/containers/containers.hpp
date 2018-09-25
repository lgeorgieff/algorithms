#pragma once

#include <string>
#include <vector>
#include <deque>
#include <functional>

namespace containers {

std::vector<std::vector<std::string>> partition_string(const std::string &str);

std::deque<int> shortest_subsequence(std::vector<int>::const_iterator begin,
                                     std::vector<int>::const_iterator end, int threshold);

void str_permute(std::string::iterator first, std::string::iterator last);

void print_permutation(std::string::iterator begin, std::string::iterator end);

using permutation_fn = std::function<void(std::string::iterator, std::string::iterator)>;

void permute (std::string::iterator begin, std::string::iterator end,
              permutation_fn fn = print_permutation);

template<typename T>
std::vector<std::vector<T>> combine_inc(T *begin_a, T *end_a, T *begin_b, T *end_b);

void all_substrigns(const std::string &str);

bool is_permutation(const std::string &lhs, const std::string &rhs);

} // namespace containers

#include "containers.cpp"