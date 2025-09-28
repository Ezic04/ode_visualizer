#pragma once

#include "backend/Simulation.hpp"
#include "gui/components/Viewport.hpp"

#include <forward_list>
#include <QObject>
#include <vector>

class SimulationManager: public QObject {
  Q_OBJECT
public:
  SimulationManager(Viewport *viewport);

signals:
  void parserFailed(const std::string &message);

public slots:
  void addMotionSystem(const std::string &equations);
  void update();

private:
  Simulation m_simulation;
  Viewport *m_viewport;
  std::forward_list<std::vector<std::array<float, 3>>> m_entitys_positions;
};