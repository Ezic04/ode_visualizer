#include "backend/Simulation.hpp"

#include <print>
#include <ranges>
#include <vector>

#include "backend/solver.hpp"

namespace simulation {

void Simulation::setEquationsSystem(const std::vector<expr::ExprPtr> &system, parser::VariableMap var_names) {
  m_motion_states[0].m_equations_system = system;
  m_motion_states[0].var_names = var_names;
}

void Simulation::addEntity(std::vector<float> &&initial_conditions) {
  m_motion_states[0].entity_vars.emplace_back(std::move(initial_conditions));
  m_motion_states[0].entity_positions.emplace_back();
}

void Simulation::update() {
  const std::chrono::duration<float> step = (std::chrono::steady_clock::now() - m_prev_time);
  for (auto &state : m_motion_states) {
    for (auto &&[vars, pos] : std::views::zip(state.entity_vars, state.entity_positions)) {
      solver::euler(state.m_equations_system, vars, step.count());
      std::copy_n(vars.begin(), 3, pos.begin());
    }
  }
  m_prev_time = std::chrono::steady_clock::now();
}

const std::vector<std::array<float, 3>> &Simulation::getPositions() {
  return m_motion_states[0].entity_positions;
}

}  // namespace simulation
