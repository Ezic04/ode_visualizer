#include "solver/solver.hpp"

#include "utility/utility.hpp"
#include <vector>

namespace solver {

std::vector<FloatType> euler(const System &system, const std::vector<FloatType> &vars, FloatType step) {
  const size_t vars_size = vars.size();
  const size_t system_size = system.size();
  assertm(vars_size == system_size + 1, "Incorect system or varibles size");
  std::vector<FloatType> new_state;
  new_state.reserve(system_size);
  for (size_t i = 0; i < system_size; ++i) { new_state.emplace_back(vars[i] + step * system[i]->eval(vars)); }
  return std::move(new_state);
}

std::vector<FloatType> heun(const System &system, const std::vector<FloatType> &vars, FloatType step) {
  const size_t vars_size = vars.size();
  const size_t system_size = system.size();
  assertm(vars_size == system_size + 1, "Incorect system or varibles size");
  std::vector<FloatType> system_eval;
  system_eval.reserve(system_size);
  std::vector<FloatType> euler_vars;
  euler_vars.reserve(vars_size);
  for (size_t i = 0; i < system_size; ++i) {
    system_eval.emplace_back(system[i]->eval(vars));
    euler_vars.emplace_back(vars[i] + step * system_eval[i]);
  }
  euler_vars.emplace_back(vars.back() + step);
  std::vector<FloatType> new_state;
  new_state.reserve(system_size);
  for (size_t i = 0; i < system_size; ++i) {
    new_state.emplace_back(vars[i] + step / 2 * (system_eval[i] + system[i]->eval(euler_vars)));
  }
  return std::move(new_state);
}

std::vector<FloatType> rk4(const System &system, const std::vector<FloatType> &vars, FloatType step) {
  const size_t vars_size = vars.size();
  const size_t system_size = system.size();
  assertm(vars_size == system_size + 1, "Incorect system or varibles size");
  FloatType half_step = step / 2.0;
  FloatType post_half_step = vars.back() + half_step;
  // k1
  std::vector<FloatType> k1;
  k1.reserve(system_size);
  std::vector<FloatType> k2_vars;
  k2_vars.reserve(vars_size);
  for (size_t i = 0; i < system_size; ++i) {
    FloatType expr_eval = system[i]->eval(vars);
    k1.emplace_back(expr_eval);
    k2_vars.emplace_back(vars[i] + half_step * expr_eval);
  }
  k2_vars.emplace_back(post_half_step);
  // k2
  std::vector<FloatType> k2;
  k2.reserve(system_size);
  std::vector<FloatType> k3_vars;
  k3_vars.reserve(vars_size);
  for (size_t i = 0; i < system_size; ++i) {
    FloatType expr_eval = system[i]->eval(k2_vars);
    k2.emplace_back(expr_eval);
    k3_vars.emplace_back(vars[i] + half_step * expr_eval);
  }
  k3_vars.emplace_back(post_half_step);
  // k3
  std::vector<FloatType> k3;
  k3.reserve(system_size);
  std::vector<FloatType> k4_vars;
  k4_vars.reserve(vars_size);
  for (size_t i = 0; i < system_size; ++i) {
    FloatType expr_eval = system[i]->eval(k3_vars);
    k3.emplace_back(expr_eval);
    k4_vars.emplace_back(vars[i] + step * expr_eval);
  }
  k4_vars.emplace_back(vars.back() + step);
  // k4
  std::vector<FloatType> k4;
  k4.reserve(system_size);
  for (size_t i = 0; i < system_size; ++i) { k4.emplace_back(system[i]->eval(k4_vars)); }
  // rk4
  std::vector<FloatType> new_system;
  new_system.reserve(system_size);
  for (size_t i = 0; i < system_size; ++i) {
    new_system.emplace_back(vars[i] + step / 6.0 * (k1[i] + 2.0 * (k2[i] + k3[i]) + k4[i]));
  }
  return new_system;
}

} // namespace solver