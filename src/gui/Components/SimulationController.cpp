#include "gui/components/SimulationController.hpp"

#include "backend/parser.hpp"

using namespace simulation;
using namespace parser;

#include <print>

SimulationController::SimulationController() {
  auto [system, var_names] = parser::parse("x' = y\ny' = -x\nz' = 0");

  var_names.addVariable("t");  // temporary solution

  simulation.setEquationsSystem(system, var_names);
  simulation.addEntity({1.0f, 0.0f, 0.0f, 0.0f});  // latst is time
  simulation.addEntity({-1.0f, 0.0f, 0.0f, 0.0f});
}

void SimulationController::updateSimulation() {
  simulation.update();
  emit simulationUpdated(simulation.getPositions());
}

void SimulationController::updateEquations(const std::string &equations) {
  try {
    auto [system, var_names] = parser::parse(equations);

    var_names.addVariable("t");  // temporary solution

    simulation.setEquationsSystem(system, var_names);
  } catch (Parser::Exception &e) { emit parserFailed(e.what()); }
}