#pragma once

#include <array>

#include <Qobject>

#include "backend/Simulation.hpp"

class SimulationController : public QObject {
  Q_OBJECT
public:
  SimulationController();
  void run();

signals:
  void simulationUpdated(const std::vector<std::array<FloatType, 3>> &positions);

public slots:
  void updateEquations(const std::string &equations);
  void updateSimulation();

private:
  simulation::Simulation simulation;
};