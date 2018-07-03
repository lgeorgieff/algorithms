#include "tree.hpp"

#include <functional>
#include <iostream>
#include <string>
#include <vector>

using std::cout;
using std::endl;
using std::function;
using std::string;
using std::vector;

using trees::tree;
using is_order = trees::tree<int, string>::order;

template <typename T>
string x_to_str(T t, bool last_element = false) {
  return last_element ? std::to_string(t) : std::to_string(t) + ", ";
}

template <>
string x_to_str<string>(string t, bool last_element) {
  return last_element ? t : t + ", ";
}

template <typename C, typename T>
string container_to_str(const C &container, function<string(T, bool)> str_fn) {
  string result;
  if (container.empty()) return result;

  const auto last{--container.cend()};
  for (auto iter{container.cbegin()}; iter != container.cend(); ++iter)
    result += str_fn(*iter, iter == last);
  return result;
}

int main(const int argc, const char **argv) {
  cout << "Entered main" << endl;

  tree<int, string> t;
  t.set(8, "8");
  t.set(4, "4");
  t.set(11, "11");
  t.set(2, "2");
  t.set(6, "6");
  t.set(9, "9");
  t.set(15, "15");
  t.set(1, "1");
  t.set(3, "3");
  t.set(5, "5");
  t.set(7, "7");
  t.set(10, "10");
  t.set(13, "13");
  t.set(17, "17");

  cout << endl << t.to_string(x_to_str<string>) << endl << endl;

  cout << "in-order values: "
       << container_to_str<std::vector<string>, string>(t.values(is_order::in_order),
                                                        x_to_str<string>)
       << endl;
  cout << "pre-order values: "
       << container_to_str<std::vector<string>, string>(t.values(is_order::pre_order),
                                                        x_to_str<string>)
       << endl;
  cout << "post-order values: "
       << container_to_str<std::vector<string>, string>(t.values(is_order::post_order),
                                                        x_to_str<string>)
       << endl;

  cout << "in-order keys: "
       << container_to_str<std::vector<int>, int>(t.keys(is_order::in_order), x_to_str<int>)
       << endl;
  cout << "pre-order keys: "
       << container_to_str<std::vector<int>, int>(t.keys(is_order::pre_order), x_to_str<int>)
       << endl;
  cout << "post-order keys: "
       << container_to_str<std::vector<int>, int>(t.keys(is_order::post_order), x_to_str<int>)
       << endl;

  tree<int, string> u{t};
  cout << endl << u.to_string(x_to_str<string>) << endl << endl;

  cout << "unset 8: " << u.unset(8) << " (" << u.size() << ")" << endl;
  cout << "unset 13: " << u.unset(13) << " (" << u.size() << ")" << endl;
  cout << "unset 17: " << u.unset(17) << " (" << u.size() << ")" << endl;
  cout << "unset 4: " << u.unset(4) << " (" << u.size() << ")" << endl;
  cout << "unset 1: " << u.unset(1) << " (" << u.size() << ")" << endl;
  cout << endl << u.to_string(x_to_str<string>) << endl << endl;

  u[7] = "007";
  cout << "u[7]: " << u[7] << endl;
  cout << "u[3]: " << u[3] << endl;
  const string u15{u[15]};
  cout << "u[15]: " << u15 << endl << endl;

  cout << "Exiting main" << endl;
  return 0;
}
