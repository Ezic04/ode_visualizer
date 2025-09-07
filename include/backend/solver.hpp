#pragma once
#include <vector>

#include "backend/expr.hpp"


namespace solver {

std::vector<float> euler(const std::vector<expr::ExprPtr> &system, std::vector<float> &vars, float step);

std::vector<float> heun(const std::vector<expr::ExprPtr> &system, const std::vector<float> &vars, float step);

std::vector<float> rk4(const std::vector<expr::ExprPtr> &system, const std::vector<float> &vars, float step);

}  // namespace solver