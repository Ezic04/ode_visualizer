#include "simulation/Simulation.hpp"

void Simulation::setSystem(solver::System system, expr::VariableMap var_names) {
  m_system = system;
  m_var_names = var_names;
  m_time = 0;
}

void Simulation::addEntity(const std::vector<double> &position) {
  m_positions.emplace_back(position);
}

void Simulation::nextStep(void) {
  for (auto &pos : m_positions) { pos = solver::rk4(m_system, {pos[0], pos[1], pos[2], m_time}, step); }
}

std::vector<std::vector<FloatType>> Simulation::getPositions() {
  return m_positions;
}

// void Simulation::addEntity(const graphics::Vec3 &position) {
//   graphics::Mesh m = graphics::getDemoMesh(m_graphics_program);
//   m.translate(position);
//   m_entities.emplace_back(std::move(m));
//   m_positions.emplace_back(position);
// }

// graphics::Vec3 Simulation::toVec3(const std::vector<FloatType> &vec) {
//   return {static_cast<float>(vec[0]), static_cast<float>(vec[1]), static_cast<float>(vec[2])};
// }