#pragma once
#include <stdexcept>
#include <unordered_map>

#include "expr/dynamic.hpp"

namespace expr::dynamic {

struct VariableMap {
  std::unordered_map<std::string, size_t> name_to_index;
  std::vector<std::string> index_to_name;

  size_t index_of(const std::string &name) {
    auto [it, inserted] = name_to_index.emplace(name, name_to_index.size());
    if (inserted) index_to_name.push_back(name);
    return it->second;
  }
};

/**
 * Exception thrown by the parser when it encounters an error.
 */
class ParserException : public std::runtime_error {
public:
  ParserException(const std::string &message) : std::runtime_error(message) {}
};

/**
 * Parses a string expression into an expression tree.
 * @param str_expr the string expression to parse
 * @return a shared pointer to the root of the expression tree
 */
ExprPtr parseExpr(const std::string &str_expr, const VariableMap &vars);

} // namespace expr::dynamic