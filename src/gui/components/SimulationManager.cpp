#include "gui/components/SimulationManager.hpp"

#include "backend/parser.hpp"

#include <array>
#include <vector>

using namespace parser;

SimulationManager::SimulationManager(Viewport *viewport): m_viewport(viewport) {
  m_simulation.addMotionSystem("x' = -y\ny'=x\nz' = 0");
  // last is time
  m_simulation.addEntity({1.0f, 0.0f, 0.0f, 0.0f});
  m_simulation.addEntity({-1.0f, 0.0f, 0.0f, 0.0f});
  m_entitys_positions.emplace_front(std::vector<std::array<float, 3>>(2));
}

void SimulationManager::update() {
  m_simulation.update(m_entitys_positions);
  m_viewport->renderFrame(m_entitys_positions.front()); // FIXME
}

void SimulationManager::addMotionSystem(const std::string &equations) {
  try {
    m_simulation.addMotionSystem(equations);
  } catch (Parser::Exception &e) { emit parserFailed(e.what()); }
}