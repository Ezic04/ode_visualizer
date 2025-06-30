#pragma once
#include "expr/expr.hpp"
#include "utility/utility.hpp"
#include <vector>

namespace solver {

using System = std::vector<expr::ExprPtr>;

// x' = f(x,t)
std::vector<FloatType> euler(const System &system, const std::vector<FloatType> &vars, FloatType step);

std::vector<FloatType> heun(const System &system, const std::vector<FloatType> &vars, FloatType step);

std::vector<FloatType> rk4(const System &system, const std::vector<FloatType> &vars, FloatType step);

} // namespace solver