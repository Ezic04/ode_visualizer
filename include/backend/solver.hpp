#pragma once
#include "backend/expr.hpp"
#include "backend/utility.hpp"
#include <vector>

namespace solver {

std::vector<FloatType> euler(const std::vector<expr::ExprPtr> &system, const std::vector<FloatType> &vars,
                             FloatType step);

std::vector<FloatType> heun(const std::vector<expr::ExprPtr> &system, const std::vector<FloatType> &vars,
                            FloatType step);

std::vector<FloatType> rk4(const std::vector<expr::ExprPtr> &system, const std::vector<FloatType> &vars,
                           FloatType step);

} // namespace solver