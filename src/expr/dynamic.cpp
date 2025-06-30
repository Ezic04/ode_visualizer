#include "expr/dynamic.hpp"

#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <utility>

#include "expr/uility.hpp"

namespace expr::dynamic {

FloatType IntPow::eval(const std::vector<FloatType> &vars) const {
  return intPow(m_base->eval(vars), m_exponent);
}

FloatType UnaryOp::eval(const std::vector<FloatType> &vars) const {
  FloatType val = m_operand->eval(vars);
  switch (m_operator) {
  case UnaryOpType::kNeg: return -val;
  case UnaryOpType::kSqrt:
    if (val < 0.0) { throw std::domain_error("Square root of negative number"); }
    return std::sqrt(val);
  case UnaryOpType::kCbrt: return std::cbrt(val);
  case UnaryOpType::kSin: return std::sin(val);
  case UnaryOpType::kCos: return std::cos(val);
  case UnaryOpType::kTan: return std::tan(val);
  case UnaryOpType::kExp: return std::exp(val);
  case UnaryOpType::kLog: return std::log(val);
  }
  assertm(false, "Unknown UnaryOpType");
  std::unreachable();
}

FloatType BinaryOp::eval(const std::vector<FloatType> &vars) const {
  FloatType l_val = m_left->eval(vars);
  FloatType r_val = m_right->eval(vars);
  switch (m_operator) {
  case BinaryOpType::kAdd: return l_val + r_val;
  case BinaryOpType::kSub: return l_val - r_val;
  case BinaryOpType::kMul: return l_val * r_val;
  case BinaryOpType::kDiv:
    if (std::abs(r_val) < kEps) { throw std::domain_error("Division by near-zero"); }
    return l_val / r_val;
  }
  assertm(false, "Unknown BinaryOpType");
  std::unreachable();
}

} // namespace expr::dynamic