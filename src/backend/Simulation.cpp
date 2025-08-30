#include "backend/Simulation.hpp"

#include "backend/solver.hpp"

namespace simulation {

void Simulation::setEquationsSystem(std::vector<expr::ExprPtr> system, parser::VariableMap var_names) {
  m_equations_system = system;
  m_var_names = var_names;
  m_time = 0;
}

void Simulation::addEntity(const std::vector<double> &position) {
  m_positions.emplace_back(position);
}

void Simulation::update() {
  for (auto &pos : m_positions) {
    pos = solver::rk4(m_equations_system, {pos[0], pos[1], pos[2], m_time}, step);
    m_time += step;
  }
}

const std::vector<std::vector<FloatType>> &Simulation::getPositions() {
  return m_positions;
}

} // namespace simulation