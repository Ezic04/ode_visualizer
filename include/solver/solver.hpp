#pragma once
#include "expr/expr.hpp"
#include "utility/utility.hpp"
#include <cstddef>
#include <vector>

namespace solver {

using System = std::vector<expr::ExprPtr>;
using State = std::vector<FloatType>;

// x' = f(x,t)
State euler(const System &system, const State &vars, size_t ind_idx, FloatType step);

// State heun(const System &system, const State &vars, FloatType t, FloatType step);
// State rk4(const System &system, const State &vars, FloatType t, FloatType step);

} // namespace solver