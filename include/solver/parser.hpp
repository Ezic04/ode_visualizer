#pragma once
#include "expr/expr.hpp"
#include "solver/solver.hpp"
#include <utility>
#include <vector>

namespace solver {

std::pair<System, expr::VariableMap> parseSystem(std::vector<std::string> equations, std::string free_varible = "t");

}
