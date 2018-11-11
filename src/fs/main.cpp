#include <iostream>
#include <string>
#include <algorithm>

#include "file_reader.hpp"

using algorithms::fs::file_reader;
using std::string, std::to_string;
using std::for_each;
using std::cout, std::endl;

template<typename T>
void print_lines(const T &lines) {
  for_each(lines.begin(), lines.end(), [](const auto &line){
    cout << line << endl;
  });

}

int main() {
  file_reader fr{"test.txt"};
  size_t line_counter{0};
  std::function<string(const string &)> fn{[&line_counter](const string &line){
    return to_string(line_counter++) + ") " + line;
  }};
  cout << "all_lines()" << endl;
  print_lines(fr.all_lines(fn));

  cout << "last_lines()" << endl;
  fr.reset();
  print_lines(fr.last_lines());

  cout << "last_lines(5)" << endl;
  fr.reset();
  print_lines(fr.last_lines(5));
  return 0;
}