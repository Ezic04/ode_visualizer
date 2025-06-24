#include "expr/expr.hpp"
#include "tests/eval_test.hpp"
#include <iostream>

int main() {
  expr::ExprPtr expr = std::make_shared<expr::Var>("x");
  std::cout << expr->eval({{"x", 2.0}}) << '\n';
  try {
    benchmark_exprs();
  } catch (std::exception &e) { std::cout << e.what() << '\n'; }
  return 0;
}
