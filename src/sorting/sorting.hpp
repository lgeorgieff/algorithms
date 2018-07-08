#pragma once

#include <functional>

namespace sorting {

template <typename T>
void randomize(T begin, T end);

template <typename T>
int comparator_fn(const T &a, const T &b);

template<typename T>
void bubble_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp = comparator_fn<T>);

template<typename T>
void merge_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp = comparator_fn<T>);

template<typename T>
void quick_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp = comparator_fn<T>);

template<typename T>
void insertion_sort(T *begin, T *end, std::function<int(const T&, const T&)> comp = comparator_fn<T>);

template<typename T>
void heap_sort(T &t);
} // namespace sorting

#include "sorting.cpp"