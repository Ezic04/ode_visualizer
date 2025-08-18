#include "solver/parser.hpp"

#include <cctype>
#include <utility>

#include "expr/expr.hpp"

namespace solver {

std::pair<System, expr::VariableMap> parseSystem(std::vector<std::string> equations, std::string free_varible) {
  System system;
  expr::VariableMap var_names;
  for (auto &eq : equations) {
    auto i = 0;
    while (std::isspace(eq[i])) { ++i; }
    auto begin = i;
    while (!std::isspace(eq[i])) { ++i; }
    auto end = i - 1;
    if (eq[end] != '\'') { throw expr::ParserException("lhs must be derivative of "); }
    while (std::isspace(eq[i])) { ++i; }
    if (eq[i] != '=') { throw expr::ParserException("varible name contains spaces or equal sign not found"); }
    std::string var_name = eq.substr(begin, end);
    var_names.index_of(var_name);
    eq = eq.substr(i + 1, eq.size());
  }
  var_names.index_of(free_varible);
  // for (auto it : var_names.index_to_name) { std::cout << it; }
  for (const auto &it : equations) { system.emplace_back(expr::parseExpr(it, var_names)); }
  return std::make_pair(system, var_names);
}

} // namespace solver