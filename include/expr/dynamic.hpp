#pragma once
#include <memory>
#include <vector>

#include "utility/utility.hpp"

namespace expr::dynamic {

/**
 * Abstract base class for all expression nodes.
 */
struct Expr {
  /**
   * Evaluates the expression given variable values.
   * @param vars map of variable names to values
   * @return evaluated result
   */
  virtual FloatType eval(const std::vector<FloatType> &vars) const = 0;
  virtual ~Expr() = default;
};

using ExprPtr = std::shared_ptr<Expr>;
/// Supported unary operations
enum class UnaryOpType { kNeg, kSqrt, kCbrt, kSin, kCos, kTan, kExp, kLog };
/// Supported binary operations
enum class BinaryOpType { kAdd, kSub, kMul, kDiv };
/// Global epsilon used for numerical comparisons
static constexpr FloatType kEps = 1e-12;

/**
 * Constant node.
 */
struct Const : Expr {
  explicit Const(FloatType value) : m_value(value) {}
  inline FloatType eval(const std::vector<FloatType> &vars) const override { return m_value; }
  const FloatType m_value; ///< constant value
};

/**
 * Variable node.
 */
struct Var : Expr {
  explicit Var(size_t idx) : m_idx(idx) {}
  inline FloatType eval(const std::vector<FloatType> &vars) const override { return vars.at(m_idx); }
  size_t m_idx; ///< variable index
};

/**
 * Integer power node.
 */
struct IntPow : Expr {
  IntPow(ExprPtr base, int exponent) : m_base(std::move(base)), m_exponent(exponent) {}
  FloatType eval(const std::vector<FloatType> &vars) const override;

  ExprPtr m_base; ///< base expression
  int m_exponent; ///< integer exponent
};

/**
 * Unary operator node.
 */
struct UnaryOp : Expr {
  explicit UnaryOp(UnaryOpType op, ExprPtr expr) : m_operator(op), m_operand(std::move(expr)) {}
  FloatType eval(const std::vector<FloatType> &vars) const override;

  UnaryOpType m_operator; ///< operator type
  ExprPtr m_operand;      ///< operand
};

/**
 * Binary operator node.
 */
struct BinaryOp : Expr {
  explicit BinaryOp(BinaryOpType op, ExprPtr left, ExprPtr right)
      : m_operator(op), m_left(std::move(left)), m_right(std::move(right)) {}
  FloatType eval(const std::vector<FloatType> &vars) const override;

  BinaryOpType m_operator; ///< operator type
  ExprPtr m_left;          ///< left operand
  ExprPtr m_right;         ///< right operand
};

} // namespace expr::dynamic
