#include "backend/Simulation.hpp"

#include "backend/solver.hpp"

namespace simulation {

void Simulation::setEquationsSystem(const std::vector<expr::ExprPtr> &system, parser::VariableMap var_names) {
  m_equations_system = system;
  m_var_names = var_names;
  m_time = 0;
}

void Simulation::addEntity(const std::array<float, 3> &position) {
  m_positions.emplace_back(position);
}

void Simulation::update() {
  const std::chrono::duration<float> step = (std::chrono::steady_clock::now() - m_prev_time);
  for (auto &pos : m_positions) {
    auto tmp = solver::rk4(m_equations_system, {pos[0], pos[1], pos[2], m_time}, step.count());
    pos = {tmp[0], tmp[1], tmp[2]};
    m_time += step.count();
  }
  m_prev_time = std::chrono::steady_clock::now();
}

const std::vector<std::array<float, 3>> &Simulation::getPositions() {
  return m_positions;
}

} // namespace simulation