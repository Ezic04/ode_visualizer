#include "backend/solver.hpp"

#include <vector>

#include "backend/utility.hpp"

using namespace expr;

namespace solver {

void euler(const std::vector<ExprPtr> &system, std::vector<float> &vars, float step) {
  const size_t vars_size = vars.size();
  const size_t system_size = system.size();
  assertm(vars_size == system_size + 1, "Incorect system or varibles size");
  for (size_t i = 0; i < system_size; ++i) { vars[i] += step * system[i]->eval(vars); }
  vars.back() += step;
}

void heun(const std::vector<ExprPtr> &system, std::vector<float> &vars, float step) {
  const size_t vars_size = vars.size();
  const size_t system_size = system.size();
  assertm(vars_size == system_size + 1, "Incorect system or varibles size");
  std::vector<float> system_eval(system_size);
  std::vector<float> euler_vars(vars_size);
  for (size_t i = 0; i < system_size; ++i) {
    system_eval[i] = system[i]->eval(vars);
    euler_vars[i] = vars[i] + step * system_eval[i];
  }
  euler_vars.back() = vars.back() + step;
  for (size_t i = 0; i < system_size; ++i) { vars[i] += step / 2 * (system_eval[i] + system[i]->eval(euler_vars)); }
}

void rk4(const std::vector<ExprPtr> &system, std::vector<float> &vars, float step) {
  const size_t vars_size = vars.size();
  const size_t system_size = system.size();
  assertm(vars_size == system_size + 1, "Incorect system or varibles size");
  float half_step = step / 2.0;
  float post_half_step = vars.back() + half_step;
  // k1
  std::vector<float> k1(system_size);
  std::vector<float> k2_vars(vars_size);
  for (size_t i = 0; i < system_size; ++i) {
    float expr_eval = system[i]->eval(vars);
    k1[i] = expr_eval;
    k2_vars[i] = vars[i] + half_step * expr_eval;
  }
  k2_vars.back() = post_half_step;
  // k2
  std::vector<float> k2(system_size);
  std::vector<float> k3_vars(vars_size);
  for (size_t i = 0; i < system_size; ++i) {
    float expr_eval = system[i]->eval(k2_vars);
    k2[i] = expr_eval;
    k3_vars[i] = vars[i] + half_step * expr_eval;
  }
  k3_vars.back() = post_half_step;
  // k3
  std::vector<float> k3(system_size);
  std::vector<float> k4_vars(vars_size);
  for (size_t i = 0; i < system_size; ++i) {
    float expr_eval = system[i]->eval(k3_vars);
    k3[i] = expr_eval;
    k4_vars[i] = vars[i] + step * expr_eval;
  }
  k4_vars.back() = vars.back() + step;
  // k4
  std::vector<float> k4(system_size);
  for (size_t i = 0; i < system_size; ++i) { k4[i] = (system[i]->eval(k4_vars)); }
  for (size_t i = 0; i < system_size; ++i) { vars[i] += step / 6.0 * (k1[i] + 2.0 * (k2[i] + k3[i]) + k4[i]); }
}

}  // namespace solver
