#pragma once
#include <stdexcept>
#include <unordered_map>

#include "backend/expr.hpp"

namespace parser {

struct VariableMap;

std::pair<std::vector<expr::ExprPtr>, VariableMap> parse(const std::string &equations,
                                                         const std::string &free_variable = "t");

struct VariableMap {
  std::unordered_map<std::string, size_t> name_to_index;
  std::vector<std::string> index_to_name;

  void addVariable(const std::string &name) {
    auto [it, inserted] = name_to_index.emplace(name, name_to_index.size());
    if (inserted) { index_to_name.emplace_back(name); }
  }
};

class Parser {
public:
  friend std::pair<std::vector<expr::ExprPtr>, VariableMap> parse(const std::string &equations,
                                                                  const std::string &free_variable);
  /**
   * Exception thrown by the parser when it encounters an error.
   */
  class Exception : public std::runtime_error {
  public:
    Exception(const std::string &message) : std::runtime_error(message) {}
  };

private:
  Parser() = default;
  std::pair<std::vector<expr::ExprPtr>, VariableMap> parseSystem(const std::string &equations,
                                                                 const std::string &free_variable);

  /**
   * Parses a string expression into an expression tree.
   * @param str_expr the string expression to parse
   * @return a shared pointer to the root of the expression tree
   */
  expr::ExprPtr parseExpr(const std::string &str_expr);

  expr::ExprPtr parseAdd(std::string_view &s);
  expr::ExprPtr parseMul(std::string_view &s);
  expr::ExprPtr parseUnary(std::string_view &s);
  expr::ExprPtr parsePow(std::string_view &s);
  expr::ExprPtr parseAtom(std::string_view &s);
  expr::ExprPtr parseNumber(std::string_view &s);
  std::string parseVarName(std::string_view &s);
  expr::UnaryOpType getUnaryOp(std::string_view id);
  void skipWhitespace(std::string_view &s);
  bool consumeWord(std::string_view &s, std::string_view w);
  bool consume(std::string_view &s, char c);

  VariableMap m_vars;
};

} // namespace parser
