#pragma once
#include <vector>

namespace expr {

/**
 * Abstract base class for all expression nodes.
 */
struct Expr {
  /**
   * Evaluates the expression given variable values.
   * @param vars map of variable names to values
   * @return evaluated result
   */
  virtual float eval(const std::vector<float> &vars) const = 0;
  virtual ~Expr() = default;
};

using ExprPtr = Expr *;
/// Supported unary operations
enum class UnaryOpType { kNeg, kSqrt, kCbrt, kSin, kCos, kTan, kExp, kLog };
/// Supported binary operations
enum class BinaryOpType { kAdd, kSub, kMul, kDiv };
/// Global epsilon used for numerical comparisons
static constexpr float kEps = 1e-12;

/**
 * Constant node.
 */
struct Const : Expr {
  explicit Const(float value) : m_value(value) {}
  inline float eval(const std::vector<float> &vars) const override { return m_value; }
  const float m_value;  ///< constant value
};

/**
 * Variable node.
 */
struct Var : Expr {
  explicit Var(size_t idx) : m_idx(idx) {}
  inline float eval(const std::vector<float> &vars) const override { return vars[m_idx]; }
  size_t m_idx;  ///< variable index
};

/**
 * Integer power node.
 */
struct IntPow : Expr {
  IntPow(ExprPtr base, int exponent) : m_base(std::move(base)), m_exponent(exponent) {}
  ~IntPow() { delete m_base; }
  float eval(const std::vector<float> &vars) const override;

  ExprPtr m_base;  ///< base expression
  int m_exponent;  ///< integer exponent
};

/**
 * Unary operator node.
 */
struct UnaryOp : Expr {
  explicit UnaryOp(UnaryOpType op, ExprPtr expr) : m_operator(op), m_operand(std::move(expr)) {}
  ~UnaryOp() { delete m_operand; }
  float eval(const std::vector<float> &vars) const override;

  UnaryOpType m_operator;  ///< operator type
  ExprPtr m_operand;       ///< operand
};

/**
 * Binary operator node.
 */
struct BinaryOp : Expr {
  explicit BinaryOp(BinaryOpType op, ExprPtr left, ExprPtr right)
    : m_operator(op), m_left(std::move(left)), m_right(std::move(right)) {}
  ~BinaryOp() { delete m_left, delete m_right; }
  float eval(const std::vector<float> &vars) const override;

  BinaryOpType m_operator;  ///< operator type
  ExprPtr m_left;           ///< left operand
  ExprPtr m_right;          ///< right operand
};

}  // namespace expr
