#include "expr/parser.hpp"

#include <cctype>
#include <cmath>
#include <memory>
#include <string>

using namespace expr::dynamic;

namespace {

ExprPtr parse_add(std::string_view &s);

UnaryOpType get_unary_op(std::string_view id) {
  static const std::unordered_map<std::string_view, UnaryOpType> kUnaryMap = {
      {"sin", UnaryOpType::kSin},   {"cos", UnaryOpType::kCos}, {"sqrt", UnaryOpType::kSqrt},
      {"cbrt", UnaryOpType::kCbrt}, {"exp", UnaryOpType::kExp}, {"ln", UnaryOpType::kLog}};
  auto it = kUnaryMap.find(id);
  if (it == kUnaryMap.end()) { throw ParserException("unknown function: " + std::string(id)); }
  return it->second;
}

void skip_whitespace(std::string_view &s) {
  while (!s.empty() && std::isspace(s.front())) { s.remove_prefix(1); }
}

bool consume(std::string_view &s, char c) {
  if (!s.empty() && s.front() == c) {
    s.remove_prefix(1);
    return true;
  }
  return false;
}

bool consume_word(std::string_view &s, std::string_view w) {
  skip_whitespace(s);
  if (s.substr(0, w.size()) == w) {
    s.remove_prefix(w.size());
    return true;
  }
  return false;
}

std::string parse_identifier(std::string_view &s) {
  skip_whitespace(s);
  size_t i = 0;
  while (i < s.size() && (std::isalpha(s[i]) || std::isdigit(s[i]) || s[i] == '_')) { ++i; }
  if (i == 0) { throw ParserException("expected identifier"); }
  std::string result{s.substr(0, i)};
  s.remove_prefix(i);
  return result;
}

ExprPtr parse_number(std::string_view &s) {
  skip_whitespace(s);
  size_t i = 0;
  bool dot = false;
  while (i < s.size() && (std::isdigit(s[i]) || (s[i] == '.' && !dot))) {
    if (s[i] == '.') dot = true;
    ++i;
  }
  if (i == 0) throw ParserException("expected number");
  double value = std::stod(std::string(s.substr(0, i)));
  s.remove_prefix(i);
  return std::make_shared<Const>(value);
}

ExprPtr parse_atom(std::string_view &s) {
  skip_whitespace(s);
  if (consume(s, '(')) {
    ExprPtr e = parse_add(s);
    if (!consume(s, ')')) { throw ParserException("expected ')'"); }
    return e;
  }
  if (std::isdigit(s.front()) || s.front() == '.') return parse_number(s);
  std::string id = parse_identifier(s);
  if (consume(s, '(')) {
    ExprPtr arg = parse_add(s);
    if (!consume(s, ')')) { throw ParserException("expected ')' after function call"); }
    return std::make_shared<UnaryOp>(get_unary_op(id), arg);
  }
  return std::make_shared<Var>(id);
}

ExprPtr parse_pow(std::string_view &s) {
  ExprPtr base = parse_atom(s);
  skip_whitespace(s);
  if (!consume(s, '^')) return base;
  ExprPtr exp = parse_pow(s);
  if (auto unary = dynamic_cast<UnaryOp *>(exp.get());
      unary && unary->m_operator == UnaryOpType::kNeg) {
    if (auto c = dynamic_cast<Const *>(unary->m_operand.get())) {
      double val = -c->m_value;
      if (std::abs(val - std::round(val)) < kEps)
        return std::make_shared<IntPow>(base, static_cast<int>(std::round(val)));
    }
  }
  if (auto c = dynamic_cast<Const *>(exp.get())) {
    if (std::abs(c->m_value - std::round(c->m_value)) < kEps)
      return std::make_shared<IntPow>(base, static_cast<int>(std::round(c->m_value)));
  }
  throw ParserException("only integer exponents supported");
}

ExprPtr parse_unary(std::string_view &s) {
  skip_whitespace(s);
  if (consume(s, '-')) { return std::make_shared<UnaryOp>(UnaryOpType::kNeg, parse_unary(s)); }
  return parse_pow(s);
}

ExprPtr parse_mul(std::string_view &s) {
  ExprPtr lhs = parse_unary(s);
  while (true) {
    skip_whitespace(s);
    char op = s.empty() ? '\0' : s.front();
    BinaryOpType type;

    switch (op) {
    case '*': type = BinaryOpType::kMul; break;
    case '/': type = BinaryOpType::kDiv; break;
    default: return lhs;
    }
    s.remove_prefix(1);
    auto rhs = parse_unary(s);
    lhs = std::make_shared<BinaryOp>(type, lhs, rhs);
  }
}

ExprPtr parse_add(std::string_view &s) {
  ExprPtr lhs = parse_mul(s);
  while (true) {
    skip_whitespace(s);
    char op = s.empty() ? '\0' : s.front();
    BinaryOpType type;

    switch (op) {
    case '+': type = BinaryOpType::kAdd; break;
    case '-': type = BinaryOpType::kSub; break;
    default: return lhs;
    }
    s.remove_prefix(1);
    auto rhs = parse_mul(s);
    lhs = std::make_shared<BinaryOp>(type, lhs, rhs);
  }
}

} // namespace

namespace expr::dynamic {

ExprPtr parseExpr(std::string_view s) {
  ExprPtr expr = parse_add(s);
  skip_whitespace(s);
  if (!s.empty()) { throw ParserException("unexpected input at end: '" + std::string(s) + "'"); }
  return expr;
}

} // namespace expr::dynamic