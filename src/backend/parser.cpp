#include "backend/parser.hpp"

#include <algorithm>
#include <cctype>
#include <cmath>
#include <ranges>
#include <string>
#include <string_view>

#include "backend/expr.hpp"

#include <vector>

using namespace expr;

namespace parser {

std::pair<std::vector<expr::ExprPtr>, VariableMap> parse(const std::string &equations,
                                                         const std::string &free_variable) {
  return Parser{}.parseSystem(equations, free_variable);
}

std::pair<std::vector<expr::ExprPtr>, VariableMap> Parser::parseSystem(const std::string &equations,
                                                                       const std::string &free_variable) {
  std::vector<expr::ExprPtr> system;
  // VariableMap var_names;
  std::vector<std::string> exprs;
  for (auto line_range : equations | std::views::split('\n')) {
    std::string line(line_range.begin(), line_range.end());

    auto not_space = [](unsigned char c) { return !std::isspace(c); };
    auto begin_it = std::find_if(line.begin(), line.end(), not_space);
    auto end_it = std::find_if(line.rbegin(), line.rend(), not_space).base();

    if (begin_it >= end_it) continue;
    std::string trimmed(begin_it, end_it);

    auto eq_pos = trimmed.find('=');
    if (eq_pos == std::string::npos) { throw Parser::Exception("equation must contain '='"); }

    std::string lhs = trimmed.substr(0, eq_pos);
    std::string rhs = trimmed.substr(eq_pos + 1);

    auto strip = [&](std::string s) {
      auto b = std::find_if(s.begin(), s.end(), not_space);
      auto e = std::find_if(s.rbegin(), s.rend(), not_space).base();
      return (b >= e) ? std::string{} : std::string(b, e);
    };

    lhs = strip(lhs);
    rhs = strip(rhs);

    if (lhs.empty() || rhs.empty()) { throw Parser::Exception("equation malformed"); }
    if (lhs.back() != '\'') { throw Parser::Exception("lhs must be derivative of variable"); }
    lhs.pop_back();

    m_vars.addVariable(lhs);
    exprs.emplace_back(rhs);
  }
  m_vars.addVariable(free_variable);

  for (const auto &expr : exprs) { system.emplace_back(parseExpr(expr)); }
  return {system, m_vars};
}

ExprPtr Parser::parseExpr(const std::string &str) {
  std::string_view s(str);
  ExprPtr expr = parseAdd(s);
  skipWhitespace(s);
  if (!s.empty()) { throw Parser::Exception("unexpected input at end: '" + std::string(s) + "'"); }
  return expr;
}

ExprPtr Parser::parseAdd(std::string_view &s) {
  ExprPtr lhs = parseMul(s);
  while (true) {
    skipWhitespace(s);
    char op = s.empty() ? '\0' : s.front();
    BinaryOpType type;

    switch (op) {
    case '+': type = BinaryOpType::kAdd; break;
    case '-': type = BinaryOpType::kSub; break;
    default: return lhs;
    }
    s.remove_prefix(1);
    auto rhs = parseMul(s);
    lhs = new BinaryOp(type, lhs, rhs);
  }
}

ExprPtr Parser::parseMul(std::string_view &s) {
  ExprPtr lhs = parseUnary(s);
  while (true) {
    skipWhitespace(s);
    char op = s.empty() ? '\0' : s.front();
    BinaryOpType type;

    switch (op) {
    case '*': type = BinaryOpType::kMul; break;
    case '/': type = BinaryOpType::kDiv; break;
    default: return lhs;
    }
    s.remove_prefix(1);
    auto rhs = parseUnary(s);
    lhs = new BinaryOp(type, lhs, rhs);
  }
}

ExprPtr Parser::parseUnary(std::string_view &s) {
  skipWhitespace(s);
  if (consume(s, '-')) { return new UnaryOp(UnaryOpType::kNeg, parseUnary(s)); }
  return parsePow(s);
}

ExprPtr Parser::parsePow(std::string_view &s) {
  ExprPtr base = parseAtom(s);
  skipWhitespace(s);
  if (!consume(s, '^')) return base;
  ExprPtr exp = parsePow(s);
  if (auto unary = dynamic_cast<UnaryOp *>(exp); unary && unary->m_operator == UnaryOpType::kNeg) {
    if (auto c = dynamic_cast<Const *>(unary->m_operand)) {
      double val = -c->m_value;
      if (std::abs(val - std::round(val)) < kEps) return new IntPow(base, static_cast<int>(std::round(val)));
    }
  }
  if (auto c = dynamic_cast<Const *>(exp)) {
    if (std::abs(c->m_value - std::round(c->m_value)) < kEps)
      return new IntPow(base, static_cast<int>(std::round(c->m_value)));
  }
  throw Parser::Exception("only integer exponents supported");
}

ExprPtr Parser::parseAtom(std::string_view &s) {
  skipWhitespace(s);
  if (consume(s, '(')) {
    ExprPtr e = parseAdd(s);
    if (!consume(s, ')')) { throw Parser::Exception("expected ')'"); }
    return e;
  }
  if (std::isdigit(s.front()) || s.front() == '.') return parseNumber(s);
  std::string name = parseVarName(s);
  if (consume(s, '(')) {
    ExprPtr arg = parseAdd(s);
    if (!consume(s, ')')) { throw Parser::Exception("expected ')' after function call"); }
    return new UnaryOp(getUnaryOp(name), arg);
  }
  if (!m_vars.name_to_index.contains(name)) { throw Parser::Exception("unknown variable: " + name); }
  return new Var(m_vars.name_to_index[name]);
}

ExprPtr Parser::parseNumber(std::string_view &s) {
  skipWhitespace(s);
  size_t i = 0;
  bool dot = false;
  while (i < s.size() && (std::isdigit(s[i]) || (s[i] == '.' && !dot))) {
    if (s[i] == '.') dot = true;
    ++i;
  }
  if (i == 0) throw Parser::Exception("expected number");
  double value = std::stod(std::string(s.substr(0, i)));
  s.remove_prefix(i);
  return new Const(value);
}

std::string Parser::parseVarName(std::string_view &s) {
  skipWhitespace(s);
  size_t i = 0;
  while (i < s.size() && (std::isalpha(s[i]) || std::isdigit(s[i]) || s[i] == '_')) { ++i; }
  if (i == 0) { throw Parser::Exception("expected varible name"); }
  std::string result{s.substr(0, i)};
  s.remove_prefix(i);
  return result;
}

UnaryOpType Parser::getUnaryOp(std::string_view id) {
  static const std::unordered_map<std::string_view, UnaryOpType> kUnaryMap = {
      {"sin", UnaryOpType::kSin},   {"cos", UnaryOpType::kCos},   {"tan", UnaryOpType::kTan},
      {"sqrt", UnaryOpType::kSqrt}, {"cbrt", UnaryOpType::kCbrt}, {"exp", UnaryOpType::kExp},
      {"ln", UnaryOpType::kLog}};
  auto it = kUnaryMap.find(id);
  if (it == kUnaryMap.end()) { throw Parser::Exception("unknown function: " + std::string(id)); }
  return it->second;
}

void Parser::skipWhitespace(std::string_view &s) {
  while (!s.empty() && std::isspace(s.front())) { s.remove_prefix(1); }
}

bool Parser::consumeWord(std::string_view &s, std::string_view w) {
  skipWhitespace(s);
  if (s.substr(0, w.size()) == w) {
    s.remove_prefix(w.size());
    return true;
  }
  return false;
}

bool Parser::consume(std::string_view &s, char c) {
  if (!s.empty() && s.front() == c) {
    s.remove_prefix(1);
    return true;
  }
  return false;
}

} // namespace parser