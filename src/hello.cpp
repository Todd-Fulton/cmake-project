
#include <header.hpp>

using namespace std;
using namespace std::literals;

string prepend_hello(string_view s) {
  return "Hello, "s + string(s) + '!';
}

