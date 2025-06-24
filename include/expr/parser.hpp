#pragma once
#include <stdexcept>
#include <string_view>

#include "expr/dynamic.hpp"

namespace expr::dynamic {

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
ExprPtr parseExpr(std::string_view str_expr);

} // namespace expr::dynamic