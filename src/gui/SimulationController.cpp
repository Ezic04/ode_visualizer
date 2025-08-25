#include "gui/SimulationController.hpp"

#include <vector>

#include "simulation/Simulation.hpp"
#include "solver/parser.hpp"

SimulationController::SimulationController() {
  auto [system, var_names] = solver::parseSystem({"x' = y", "y' = -x", "z' = 0"});
  sim.setSystem(system, var_names);
  sim.addEntity({1.0f, 0.0f, 0.0f});
}

void SimulationController::nextPos() {
  sim.nextStep();
  emit newPositions(sim.getPositions());
}