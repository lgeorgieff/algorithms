#pragma once

#include "file_reader.hpp"

algorithms::fs::file_reader::file_reader(const std::string path) :path_{path}, file_{path} { }

algorithms::fs::file_reader::~file_reader() noexcept {
  file_.close();
}

template<typename T>
std::list<T> algorithms::fs::file_reader::all_lines(std::function<T(const std::string &)> fn) {
  std::list<T> result;
  while(file_) {
    std::string line;
    std::getline(file_, line);
    result.push_back(fn(line));
  }
  return result;
}

std::list<std::string> algorithms::fs::file_reader::last_lines(size_t n) {
  std::list<std::string> result;
  while(file_) {
    std::string line;
    std::getline(file_, line);
    result.push_back(line);
    if(result.size() > n) result.pop_front();
  }
  return result;
}

void algorithms::fs::file_reader::reset() {
  file_.clear();
  file_.seekg(0, file_.beg);
}