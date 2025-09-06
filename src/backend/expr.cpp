#include "backend/expr.hpp"

#include <cmath>
#include <cstdlib>
#include <stdexcept>
#include <utility>
#include <vector>

#include "backend/utility.hpp"

namespace expr {

float IntPow::eval(const std::vector<float> &vars) const {
  return intPow(m_base->eval(vars), m_exponent);
}

float UnaryOp::eval(const std::vector<float> &vars) const {
  float val = m_operand->eval(vars);
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

float BinaryOp::eval(const std::vector<float> &vars) const {
  float l_val = m_left->eval(vars);
  float r_val = m_right->eval(vars);
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

}  // namespace expr