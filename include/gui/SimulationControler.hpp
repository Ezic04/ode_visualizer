#pragma once

#include "simulation/Simulation.hpp"
#include <Qobject>

class SimulationControler : public QObject {
  Q_OBJECT

public:
  SimulationControler();
  void run();

signals:
  void newPositions(std::vector<std::vector<FloatType>> positions);

public slots:
  void nextPos();
  void setEquations(std::string equations) {};

private:
  Simulation sim;
};