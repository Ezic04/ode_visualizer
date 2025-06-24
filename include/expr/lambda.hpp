#pragma once
#include <cmath>
#include <functional>
#include <memory>
#include <utility>
#include <vector>

#include "expr/uility.hpp"

namespace expr::lambda {

/// Expression represented as a function object
using EvalFunc = std::function<double(const std::vector<double> &)>;

struct Expr {
  EvalFunc eval; ///< compiled expression
};

using ExprPtr = std::shared_ptr<Expr>;

/// Helper: create a constant expression
inline ExprPtr makeConst(double val) {
  return std::make_shared<Expr>(Expr{[val](const std::vector<double> &) { return val; }});
}

/// Helper: create a variable (by index)
inline ExprPtr make_var(size_t index) {
  return std::make_shared<Expr>(
      Expr{[index](const std::vector<double> &vars) { return vars[index]; }});
}

inline ExprPtr makeIntPow(ExprPtr base, int exponent) {
  return std::make_shared<Expr>(
      Expr{[base = std::move(base), exponent](const std::vector<double> &vars) {
        return intPow(base->eval(vars), exponent);
      }});
}

/// Unary op
enum class UnaryOpType { Neg, Sqrt, Sin, Cos, Exp, Log };

inline ExprPtr makeUnary(UnaryOpType op, ExprPtr arg) {
  return std::make_shared<Expr>(Expr{[op, arg = std::move(arg)](const std::vector<double> &vars) {
    double x = arg->eval(vars);
    switch (op) {
    case UnaryOpType::Neg: return -x;
    case UnaryOpType::Sqrt: return std::sqrt(x);
    case UnaryOpType::Sin: return std::sin(x);
    case UnaryOpType::Cos: return std::cos(x);
    case UnaryOpType::Exp: return std::exp(x);
    case UnaryOpType::Log: return std::log(x);
    }
    std::unreachable();
  }});
}

/// Binary op
enum class BinaryOpType { Add, Sub, Mul, Div };

inline ExprPtr make_binary(BinaryOpType op, ExprPtr lhs, ExprPtr rhs) {
  return std::make_shared<Expr>(
      Expr{[op, lhs = std::move(lhs), rhs = std::move(rhs)](const std::vector<double> &vars) {
        double a = lhs->eval(vars);
        double b = rhs->eval(vars);
        switch (op) {
        case BinaryOpType::Add: return a + b;
        case BinaryOpType::Sub: return a - b;
        case BinaryOpType::Mul: return a * b;
        case BinaryOpType::Div: return a / b;
        }
        std::unreachable();
      }});
}

} // namespace expr::lambda
