#pragma once
#include <cmath>
// #include <variant>
#include <stdexcept>
#include <vector>

#include "expr/uility.hpp"

namespace expr::stack {

enum class Op { Const, Var, Add, Sub, Mul, Div, Neg, Sqrt, Sin, Cos, Exp, Log, PowInt };

struct Node {
  Op op;
  union {
    double value;
    size_t var_idx_or_exponent;
  };

  Node(Op op, double val) : op(op), value(val) {}
  Node(Op op, size_t idx_or_exp) : op(op), var_idx_or_exponent(idx_or_exp) {}
  Node(Op op) : op(op), value(0) {}
};

using Program = std::vector<Node>;

/// Evaluates the program using a stack-based interpreter
inline double eval(const Program &prog, const std::vector<double> &vars) {
  std::vector<double> stack;
  stack.reserve(prog.size());

  for (const auto &node : prog) {
    switch (node.op) {
    case Op::Const: stack.push_back(node.value); break;
    case Op::Var: stack.push_back(vars[node.var_idx_or_exponent]); break;
    case Op::Add: {
      double b = stack.back();
      stack.pop_back();
      double a = stack.back();
      stack.pop_back();
      stack.push_back(a + b);
      break;
    }
    case Op::Sub: {
      double b = stack.back();
      stack.pop_back();
      double a = stack.back();
      stack.pop_back();
      stack.push_back(a - b);
      break;
    }
    case Op::Mul: {
      double b = stack.back();
      stack.pop_back();
      double a = stack.back();
      stack.pop_back();
      stack.push_back(a * b);
      break;
    }
    case Op::Div: {
      double b = stack.back();
      stack.pop_back();
      double a = stack.back();
      stack.pop_back();
      stack.push_back(a / b);
      break;
    }
    case Op::Neg: {
      double a = stack.back();
      stack.pop_back();
      stack.push_back(-a);
      break;
    }
    case Op::Sqrt: {
      double a = stack.back();
      stack.pop_back();
      stack.push_back(std::sqrt(a));
      break;
    }
    case Op::Sin: {
      double a = stack.back();
      stack.pop_back();
      stack.push_back(std::sin(a));
      break;
    }
    case Op::Cos: {
      double a = stack.back();
      stack.pop_back();
      stack.push_back(std::cos(a));
      break;
    }
    case Op::Exp: {
      double a = stack.back();
      stack.pop_back();
      stack.push_back(std::exp(a));
      break;
    }
    case Op::Log: {
      double a = stack.back();
      stack.pop_back();
      stack.push_back(std::log(a));
      break;
    }
    case Op::PowInt: {
      double a = stack.back();
      stack.pop_back();
      stack.push_back(intPow(a, node.var_idx_or_exponent));
      break;
    }
    }
  }
  if (stack.size() != 1) {
    throw std::range_error("Stack underflow or overflow during evaluation");
  }
  return stack.back();
}
} // namespace expr::stack

// namespace f {

// enum class Op { Add, Sub, Mul, Div, Neg, Sqrt, Sin, Cos, Exp, Log, PowInt };

// struct Const {
//   double value;
// };
// struct Var {
//   size_t index;
// };
// struct PowConst {
//   int exponent;
// };
// struct RawOp {
//   Op op;
// };

// using Node = std::variant<std::monostate, Const, Var, PowConst, RawOp>;

// using Program = std::vector<Node>;

// inline double int_pow(double x, int n) {
//   if (n == 0) return 1.0;
//   if (n < 0) return 1.0 / int_pow(x, -n);
//   if (n & 1) return x * int_pow(x * x, n >> 1);
//   return int_pow(x * x, n >> 1);
// }

// inline double eval(const Program &prog, const std::vector<double> &vars) {
//   std::vector<double> stack;
//   stack.reserve(prog.size());

//   for (const auto &node : prog) {
//     std::visit(
//         [&](auto &&arg) {
//           using T = std::decay_t<decltype(arg)>;
//           if constexpr (std::is_same_v<T, Const>) {
//             stack.push_back(arg.value);
//           } else if constexpr (std::is_same_v<T, Var>) {
//             stack.push_back(vars[arg.index]);
//           } else if constexpr (std::is_same_v<T, PowConst>) {
//             double a = stack.back();
//             stack.pop_back();
//             stack.push_back(int_pow(a, arg.exponent));
//           } else if constexpr (std::is_same_v<T, RawOp>) {
//             switch (arg.op) {
//             case Op::Add: {
//               double b = stack.back();
//               stack.pop_back();
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(a + b);
//               break;
//             }
//             case Op::Sub: {
//               double b = stack.back();
//               stack.pop_back();
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(a - b);
//               break;
//             }
//             case Op::Mul: {
//               double b = stack.back();
//               stack.pop_back();
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(a * b);
//               break;
//             }
//             case Op::Div: {
//               double b = stack.back();
//               stack.pop_back();
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(a / b);
//               break;
//             }
//             case Op::Neg: {
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(-a);
//               break;
//             }
//             case Op::Sqrt: {
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(std::sqrt(a));
//               break;
//             }
//             case Op::Sin: {
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(std::sin(a));
//               break;
//             }
//             case Op::Cos: {
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(std::cos(a));
//               break;
//             }
//             case Op::Exp: {
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(std::exp(a));
//               break;
//             }
//             case Op::Log: {
//               double a = stack.back();
//               stack.pop_back();
//               stack.push_back(std::log(a));
//               break;
//             }
//             default: assert(false);
//             }
//           }
//         },
//         node);
//   }

//   assert(stack.size() == 1);
//   return stack.back();
// }

// } // namespace f