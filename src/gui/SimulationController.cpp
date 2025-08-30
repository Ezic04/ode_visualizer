#include "gui/SimulationController.hpp"

#include "backend/parser.hpp"
#include <vector>

using namespace simulation;

SimulationController::SimulationController() {
  auto [system, var_names] = parser::parseSystem("x' = y\ny' = -x\nz' = 0");
  simulation.setEquationsSystem(system, var_names);
  simulation.addEntity({1.0f, 0.0f, 0.0f});
}

void SimulationController::updateSimulation() {
  simulation.update();
  const std::vector<FloatType> &positions = simulation.getPositions()[0];
  emit simulationUpdated({{positions[0], positions[1], positions[2]}});
}

void SimulationController::updateEquations(const std::string &equations) {
  auto [system, var_names] = parser::parseSystem(equations);
  simulation.setEquationsSystem(system, var_names);
}