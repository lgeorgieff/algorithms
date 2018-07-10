#include "containers.hpp"

#include <string>
#include <iostream>

using std::string;
using std::cout;
using std::endl;

using containers::partition_string;

int main(const int argc, const char **argv) {
  string str{"nitingeeks"};

  for(const auto &partition : partition_string(str)) {
    for(size_t index{0}; index < partition.size(); ++index) {
      cout << partition[index];
      if (index == partition.size() - 1) cout << endl;
      else cout << " ";
    }
  }


  return 0;
}
