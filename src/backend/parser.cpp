#include "backend/parser.hpp"

#include <cctype>
#include <cmath>
#include <ranges>
#include <string>
#include <string_view>

#include "backend/expr.hpp"
#include "backend/parser.hpp"

#include <vector>

using namespace expr;

namespace parser {

ExprPtr parseAdd(std::string_view &s, const VariableMap &var_map);

UnaryOpType getUnaryOp(std::string_view id) {
  static const std::unordered_map<std::string_view, UnaryOpType> kUnaryMap = {
      {"sin", UnaryOpType::kSin},   {"cos", UnaryOpType::kCos},   {"tan", UnaryOpType::kTan},
      {"sqrt", UnaryOpType::kSqrt}, {"cbrt", UnaryOpType::kCbrt}, {"exp", UnaryOpType::kExp},
      {"ln", UnaryOpType::kLog}};
  auto it = kUnaryMap.find(id);
  if (it == kUnaryMap.end()) { throw ParserException("unknown function: " + std::string(id)); }
  return it->second;
}

void skipWhitespace(std::string_view &s) {
  while (!s.empty() && std::isspace(s.front())) { s.remove_prefix(1); }
}

bool consume(std::string_view &s, char c) {
  if (!s.empty() && s.front() == c) {
    s.remove_prefix(1);
    return true;
  }
  return false;
}

bool consumeWord(std::string_view &s, std::string_view w) {
  skipWhitespace(s);
  if (s.substr(0, w.size()) == w) {
    s.remove_prefix(w.size());
    return true;
  }
  return false;
}

std::string parseVarName(std::string_view &s) {
  skipWhitespace(s);
  size_t i = 0;
  while (i < s.size() && (std::isalpha(s[i]) || std::isdigit(s[i]) || s[i] == '_')) { ++i; }
  if (i == 0) { throw ParserException("expected varible name"); }
  std::string result{s.substr(0, i)};
  s.remove_prefix(i);
  return result;
}

ExprPtr parseNumber(std::string_view &s) {
  skipWhitespace(s);
  size_t i = 0;
  bool dot = false;
  while (i < s.size() && (std::isdigit(s[i]) || (s[i] == '.' && !dot))) {
    if (s[i] == '.') dot = true;
    ++i;
  }
  if (i == 0) throw ParserException("expected number");
  double value = std::stod(std::string(s.substr(0, i)));
  s.remove_prefix(i);
  return new Const(value);
}

ExprPtr parseAtom(std::string_view &s, const VariableMap &var_map) {
  skipWhitespace(s);
  if (consume(s, '(')) {
    ExprPtr e = parseAdd(s, var_map);
    if (!consume(s, ')')) { throw ParserException("expected ')'"); }
    return e;
  }
  if (std::isdigit(s.front()) || s.front() == '.') return parseNumber(s);
  std::string name = parseVarName(s);
  if (consume(s, '(')) {
    ExprPtr arg = parseAdd(s, var_map);
    if (!consume(s, ')')) { throw ParserException("expected ')' after function call"); }
    return new UnaryOp(getUnaryOp(name), arg);
  }
  return new Var(var_map.name_to_index.at(name));
}

ExprPtr parsePow(std::string_view &s, const VariableMap &var_map) {
  ExprPtr base = parseAtom(s, var_map);
  skipWhitespace(s);
  if (!consume(s, '^')) return base;
  ExprPtr exp = parsePow(s, var_map);
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
  throw ParserException("only integer exponents supported");
}

ExprPtr parseUnary(std::string_view &s, const VariableMap &var_map) {
  skipWhitespace(s);
  if (consume(s, '-')) { return new UnaryOp(UnaryOpType::kNeg, parseUnary(s, var_map)); }
  return parsePow(s, var_map);
}

ExprPtr parseMul(std::string_view &s, const VariableMap &var_map) {
  ExprPtr lhs = parseUnary(s, var_map);
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
    auto rhs = parseUnary(s, var_map);
    lhs = new BinaryOp(type, lhs, rhs);
  }
}

ExprPtr parseAdd(std::string_view &s, const VariableMap &var_map) {
  ExprPtr lhs = parseMul(s, var_map);
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
    auto rhs = parseMul(s, var_map);
    lhs = new BinaryOp(type, lhs, rhs);
  }
}

ExprPtr parseExpr(const std::string &str, const VariableMap &vars) {
  std::string_view s(str);
  ExprPtr expr = parseAdd(s, vars);
  skipWhitespace(s);
  if (!s.empty()) { throw ParserException("unexpected input at end: '" + std::string(s) + "'"); }
  return expr;
}

std::pair<std::vector<expr::ExprPtr>, VariableMap> parseSystem(const std::string &equations,
                                                               std::string free_variable) {
  std::vector<expr::ExprPtr> system;
  VariableMap var_names;
  std::vector<std::string> exprs;
  for (auto line_range : equations | std::views::split('\n')) {
    std::string line(line_range.begin(), line_range.end());

    auto not_space = [](unsigned char c) { return !std::isspace(c); };
    auto begin_it = std::find_if(line.begin(), line.end(), not_space);
    auto end_it = std::find_if(line.rbegin(), line.rend(), not_space).base();

    if (begin_it >= end_it) continue;
    std::string trimmed(begin_it, end_it);

    auto eq_pos = trimmed.find('=');
    if (eq_pos == std::string::npos) { throw ParserException("equation must contain '='"); }

    std::string lhs = trimmed.substr(0, eq_pos);
    std::string rhs = trimmed.substr(eq_pos + 1);

    auto strip = [&](std::string s) {
      auto b = std::find_if(s.begin(), s.end(), not_space);
      auto e = std::find_if(s.rbegin(), s.rend(), not_space).base();
      return (b >= e) ? std::string{} : std::string(b, e);
    };

    lhs = strip(lhs);
    rhs = strip(rhs);

    if (lhs.empty() || rhs.empty()) { throw ParserException("equation malformed"); }
    if (lhs.back() != '\'') { throw ParserException("lhs must be derivative of variable"); }
    lhs.pop_back();

    var_names.index_of(lhs);
    exprs.emplace_back(rhs);
  }
  var_names.index_of(free_variable);

  for (const auto &expr : exprs) { system.emplace_back(parseExpr(expr, var_names)); }
  return {system, var_names};
}

} // namespace parser