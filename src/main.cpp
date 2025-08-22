// #include "expr/expr.hpp"
// #include "simulation/Simulation.hpp"
// #include "solver/parser.hpp"

#include <QApplication>

#include "gui/MainWindow.hpp"

// try {
//   auto [system, var_names] = solver::parseSystem({"x' = y", "y' = -x", "z' = 0"});
//   simulation::Simulation sim(system, var_names);
//   sim.addEntity({1.0f, 0.0f, 0.0f});
//   sim.run();
// } catch (expr::ParserException e) { std::cout << e.what(); }

int main(int argc, char **argv) {
  QGuiApplication app(argc, argv);

  QSurfaceFormat format;
  format.setSamples(16);

  TriangleWindow window;
  window.setFormat(format);
  window.resize(640, 480);
  window.show();

  window.setAnimating(true);

  return app.exec();
}
