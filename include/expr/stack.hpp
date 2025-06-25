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
    FloatType value;
    size_t var_idx_or_exponent;
  };

  Node(Op op, FloatType val) : op(op), value(val) {}
  Node(Op op, size_t idx_or_exp) : op(op), var_idx_or_exponent(idx_or_exp) {}
  Node(Op op) : op(op), value(0) {}
};

using Program = std::vector<Node>;

/// Evaluates the program using a stack-based interpreter
inline FloatType eval(const Program &prog, const std::vector<FloatType> &vars) {
  std::vector<FloatType> stack;
  stack.reserve(prog.size());

  for (const auto &node : prog) {
    switch (node.op) {
    case Op::Const: stack.push_back(node.value); break;
    case Op::Var: stack.push_back(vars[node.var_idx_or_exponent]); break;
    case Op::Add: {
      FloatType b = stack.back();
      stack.pop_back();
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(a + b);
      break;
    }
    case Op::Sub: {
      FloatType b = stack.back();
      stack.pop_back();
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(a - b);
      break;
    }
    case Op::Mul: {
      FloatType b = stack.back();
      stack.pop_back();
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(a * b);
      break;
    }
    case Op::Div: {
      FloatType b = stack.back();
      stack.pop_back();
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(a / b);
      break;
    }
    case Op::Neg: {
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(-a);
      break;
    }
    case Op::Sqrt: {
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(std::sqrt(a));
      break;
    }
    case Op::Sin: {
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(std::sin(a));
      break;
    }
    case Op::Cos: {
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(std::cos(a));
      break;
    }
    case Op::Exp: {
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(std::exp(a));
      break;
    }
    case Op::Log: {
      FloatType a = stack.back();
      stack.pop_back();
      stack.push_back(std::log(a));
      break;
    }
    case Op::PowInt: {
      FloatType a = stack.back();
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
//   FloatType value;
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

// inline FloatType int_pow(FloatType x, int n) {
//   if (n == 0) return 1.0;
//   if (n < 0) return 1.0 / int_pow(x, -n);
//   if (n & 1) return x * int_pow(x * x, n >> 1);
//   return int_pow(x * x, n >> 1);
// }

// inline FloatType eval(const Program &prog, const std::vector<FloatType> &vars) {
//   std::vector<FloatType> stack;
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
//             FloatType a = stack.back();
//             stack.pop_back();
//             stack.push_back(int_pow(a, arg.exponent));
//           } else if constexpr (std::is_same_v<T, RawOp>) {
//             switch (arg.op) {
//             case Op::Add: {
//               FloatType b = stack.back();
//               stack.pop_back();
//               FloatType a = stack.back();
//               stack.pop_back();
//               stack.push_back(a + b);
//               break;
//             }
//             case Op::Sub: {
//               FloatType b = stack.back();
//               stack.pop_back();
//               FloatType a = stack.back();
//               stack.pop_back();
//               stack.push_back(a - b);
//               break;
//             }
//             case Op::Mul: {
//               FloatType b = stack.back();
//               stack.pop_back();
//               FloatType a = stack.back();
//               stack.pop_back();
//               stack.push_back(a * b);
//               break;
//             }
//             case Op::Div: {
//               FloatType b = stack.back();
//               stack.pop_back();
//               FloatType a = stack.back();
//               stack.pop_back();
//               stack.push_back(a / b);
//               break;
//             }
//             case Op::Neg: {
//               FloatType a = stack.back();
//               stack.pop_back();
//               stack.push_back(-a);
//               break;
//             }
//             case Op::Sqrt: {
//               FloatType a = stack.back();
//               stack.pop_back();
//               stack.push_back(std::sqrt(a));
//               break;
//             }
//             case Op::Sin: {
//               FloatType a = stack.back();
//               stack.pop_back();
//               stack.push_back(std::sin(a));
//               break;
//             }
//             case Op::Cos: {
//               FloatType a = stack.back();
//               stack.pop_back();
//               stack.push_back(std::cos(a));
//               break;
//             }
//             case Op::Exp: {
//               FloatType a = stack.back();
//               stack.pop_back();
//               stack.push_back(std::exp(a));
//               break;
//             }
//             case Op::Log: {
//               FloatType a = stack.back();
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