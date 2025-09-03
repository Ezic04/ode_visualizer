#include "gui/components/SimulationController.hpp"

#include <iostream>

using namespace simulation;

SimulationController::SimulationController() {
  auto [system, var_names] = parser::parseSystem("x' = y\ny' = -x\nz' = 0");
  simulation.setEquationsSystem(system, var_names);
  simulation.addEntity({1.0f, 0.0f, 0.0f});
  simulation.addEntity({-1.0f, 0.0f, 0.0f});
}

void SimulationController::updateSimulation() {

  simulation.update();
  emit simulationUpdated(simulation.getPositions());
}

void SimulationController::updateEquations(const std::string &equations) {
  try {
    auto [system, var_names] = parser::parseSystem(equations);
    simulation.setEquationsSystem(system, var_names);
  } catch (std::exception &e) { std::cout << e.what() << '\n'; }
}