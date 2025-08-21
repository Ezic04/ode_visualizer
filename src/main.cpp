#include <iostream>

#include "expr/expr.hpp"
#include "simulation/Simulation.hpp"
#include "solver/parser.hpp"

#include <QApplication>
#include <QPushButton>

int main(int argc, char *argv[]) {
  try {
    auto [system, var_names] = solver::parseSystem({"x' = y", "y' = -x", "z' = 0"});
    simulation::Simulation sim(system, var_names);
    sim.addEntity({1.0f, 0.0f, 0.0f});
    sim.run();
  } catch (expr::ParserException e) { std::cout << e.what(); }
  QApplication app(argc, argv);
  QPushButton button("Hello, Qt + Clang + VSCode!");
  button.resize(250, 80);
  button.show();
  return app.exec();
}