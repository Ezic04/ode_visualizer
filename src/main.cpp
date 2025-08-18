#include <iostream>

#include "expr/expr.hpp"
#include "simulation/Simulation.hpp"
#include "solver/parser.hpp"

int main() {
  try {
    auto [system, var_names] = solver::parseSystem({"x' = y", "y' = -x", "z' = 0"});
    simulation::Simulation sim(system, var_names);
    sim.addEntity({1.0f, 0.0f, 0.0f});
    sim.run();
  } catch (expr::ParserException e) { std::cout << e.what(); }
}