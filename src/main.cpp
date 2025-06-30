#include "tests/eval_test.hpp"
#include <iostream>

int main() {
  try {
    benchmark_exprs();
  } catch (std::exception &e) { std::cout << e.what() << '\n'; }
  return 0;
}
