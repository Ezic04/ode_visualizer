#pragma once

#include "expr/tree.hpp"

namespace expr {

/**
 * Parses a string expression into an expression tree.
 * @param str_expr the string expression to parse
 * @return a shared pointer to the root of the expression tree
 */
ExprPtr parse_expr(const std::string& str_expr);

}  // namespace expr