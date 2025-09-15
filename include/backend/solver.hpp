#pragma once
#include <vector>

#include "backend/expr.hpp"

namespace solver {

void euler(const std::vector<expr::ExprPtr> &system, std::vector<float> &vars, float step);

void heun(const std::vector<expr::ExprPtr> &system, std::vector<float> &vars, float step);

void rk4(const std::vector<expr::ExprPtr> &system, std::vector<float> &vars, float step);

}  // namespace solver