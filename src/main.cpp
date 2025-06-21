#include <print>

#include "expr/tree.hpp"

using namespace expr;

int main() {
  ExprPtr x = std::make_shared<Var>("x");
  ExprPtr one = std::make_shared<Const>(1.0);
  ExprPtr two = std::make_shared<Const>(2.0);

  ExprPtr x_plus_1 = std::make_shared<BinaryOp>(BinaryOpType::kAdd, x, one);
  ExprPtr two_x = std::make_shared<BinaryOp>(BinaryOpType::kMul, two, x);
  ExprPtr sin_2x = std::make_shared<UnaryOp>(UnaryOpType::kSin, two_x);
  ExprPtr expr = std::make_shared<BinaryOp>(BinaryOpType::kMul, x_plus_1, sin_2x);

  std::unordered_map<std::string, double> vars = {{"x", 0.5}};

  std::println("{}", expr->eval(vars));
  return 0;
}
