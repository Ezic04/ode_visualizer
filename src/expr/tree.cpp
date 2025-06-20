#include "expr/tree.hpp"

#include <cassert>
#include <cmath>
#include <cstdlib>
#include <stdexcept>

#define assertm(exp, msg) assert((void(msg), exp))

using namespace expr;

// double IntPow::int_pow(double x, int n) {
//   if (n == 0) return 1.0;
//   if (n < 0) return 1.0 / int_pow(x, -n);
//   if (n & 1) return x * int_pow(x * x, n >> 1);
//   return int_pow(x * x, n / 2);
// }

double IntPow::int_pow(double x, int n) {
  if (n == 0) return 1.0;
  if (n < 0) return 1.0 / int_pow(x, -n);
  double result = 1.0;
  while (n > 0) {
    if (n & 1) result *= x;
    x *= x;
    n >>= 1;
  }
  return result;
}

double UnaryOp::eval(const std::unordered_map<std::string, double> &vars) const {
  double val = m_operand->eval(vars);
  switch (m_operator) {
    case UnaryOpType::kNeg:
      return -val;
    case UnaryOpType::kSqrt:
      if (val < 0.0) {
        throw std::invalid_argument("Square root of negative number");
      }
      return std::sqrt(val);
    case UnaryOpType::kCbrt:
      return std::cbrt(val);
    case UnaryOpType::kSin:
      return std::sin(val);
    case UnaryOpType::kCos:
      return std::cos(val);
    case UnaryOpType::kExp:
      return std::exp(val);
    case UnaryOpType::kLog:
      return std::log(val);
  }
  assertm(false, "Unknown UnaryOpType");
}

double BinaryOp::eval(const std::unordered_map<std::string, double> &vars) const {
  double l_val = m_left->eval(vars);
  double r_val = m_right->eval(vars);
  switch (m_operator) {
    case BinaryOpType::kAdd:
      return l_val + r_val;
    case BinaryOpType::kSub:
      return l_val - r_val;
    case BinaryOpType::kMul:
      return l_val * r_val;
    case BinaryOpType::kDiv:
      if (std::abs(r_val) < kEps) {
        throw std::invalid_argument("Division by near-zero");
      }
      return l_val / r_val;
  }
  assertm(false, "Unknown BinaryOpType");
}