#pragma once
#include <memory>
#include <string>
#include <unordered_map>
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
  virtual double eval(const std::unordered_map<std::string, double> &vars) const = 0;
  virtual ~Expr() = default;
};

using ExprPtr = std::shared_ptr<Expr>;
/// Supported unary operations
enum class UnaryOpType { kNeg, kSqrt, kCbrt, kSin, kCos, kExp, kLog };
/// Supported binary operations
enum class BinaryOpType { kAdd, kSub, kMul, kDiv };
/// Global epsilon used for numerical comparisons
static constexpr double kEps = 1e-12;

/**
 * Constant node.
 */
struct Const : Expr {
  explicit Const(double value) : m_value(value) {}
  inline double eval(const std::unordered_map<std::string, double> &vars) const override {
    return m_value;
  }
  const double m_value; ///< constant value
};

/**
 * Variable node.
 */
struct Var : Expr {
  explicit Var(std::string identifier) : m_identifier(std::move(identifier)) {}
  inline double eval(const std::unordered_map<std::string, double> &vars) const override {
    return vars.at(m_identifier);
  }
  std::string m_identifier; ///< variable identifier
};

/**
 * Integer power node.
 */
struct IntPow : Expr {
  IntPow(ExprPtr base, int exponent) : m_base(std::move(base)), m_exponent(exponent) {}
  double eval(const std::unordered_map<std::string, double> &vars) const override;

  ExprPtr m_base; ///< base expression
  int m_exponent; ///< integer exponent
};

/**
 * Unary operator node.
 */
struct UnaryOp : Expr {
  explicit UnaryOp(UnaryOpType op, ExprPtr expr) : m_operator(op), m_operand(std::move(expr)) {}
  double eval(const std::unordered_map<std::string, double> &vars) const override;

  UnaryOpType m_operator; ///< operator type
  ExprPtr m_operand;      ///< operand
};

/**
 * Binary operator node.
 */
struct BinaryOp : Expr {
  explicit BinaryOp(BinaryOpType op, ExprPtr left, ExprPtr right)
      : m_operator(op), m_left(std::move(left)), m_right(std::move(right)) {}
  double eval(const std::unordered_map<std::string, double> &vars) const override;

  BinaryOpType m_operator; ///< operator type
  ExprPtr m_left;          ///< left operand
  ExprPtr m_right;         ///< right operand
};
} // namespace expr::dynamic
