#include "backend/Simulation.hpp"

#include <chrono>
#include <print>
#include <ranges>
#include <vector>

#include "backend/solver.hpp"

using namespace std::chrono_literals;

namespace simulation {

void Simulation::addEquationsSystem(const std::vector<expr::ExprPtr> &system, parser::VariableMap var_names) {
  m_equation_systems.emplace_front(system, var_names);
}

void Simulation::addEntity(std::vector<float> &&initial_conditions) {
  m_equation_systems.begin()->entities.emplace_back(1, std::move(initial_conditions));
  m_equation_systems.begin()->entity_positions.emplace_back();
}

void Simulation::update() {
  auto now = std::chrono::steady_clock::now();
  float dt = std::chrono::duration<float>(std::chrono::steady_clock::now() - m_prev_time).count();
  for (auto &system : m_equation_systems) {
    for (auto &&[entity, pos] : std::views::zip(system.entities, system.entity_positions)) {
      solver::rk4(system.m_equations_system, entity.vars, dt);
      std::copy_n(entity.vars.begin(), 3, pos.begin());
    }
  }
  m_prev_time = std::chrono::steady_clock::now();
}

const std::vector<std::array<float, 3>> &Simulation::getPositions() {
  return m_equation_systems.begin()->entity_positions;
}

}  // namespace simulation