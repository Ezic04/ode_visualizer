#include "simulation/Simulation.hpp"

using namespace simulation;

Simulation::Simulation(
  solver::System system, 
  expr::VariableMap var_names
) : m_system(system), 
    m_var_names(var_names), 
    m_time(0)
{

  //initialize
  
}

Simulation::~Simulation(void) {

  // free resources

}

void Simulation::run(void) {

  // main logic

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