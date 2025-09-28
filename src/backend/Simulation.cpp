#include "backend/Simulation.hpp"

#include "backend/MotionSystem.hpp"
#include "backend/parser.hpp"

#include <cstddef>
#include <ranges>
#include <variant>
#include <vector>

void Simulation::addMotionSystem(const std::string &equations) {
  auto [system, var_names] = parser::parse(equations);
  m_motion_systems.emplace_front(MotionSystem{.m_equations_system = system, .var_names = var_names, .dt = 1.0f / 60.f});
}

void Simulation::removeMotionSystemBase(size_t idx) {
  auto it = m_motion_systems.begin();
  for (size_t i = 0; i < idx; ++i) { ++it; }
  m_motion_systems.erase_after(it);
}

void Simulation::addEntity(std::vector<float> initial_conditions) {
  static size_t counter = 0;
  std::visit([initial_conditions = std::move(initial_conditions)](
                 auto &obj) { obj.entities.emplace_back(++counter, std::move(initial_conditions)); },
             m_motion_systems.front());
}

void Simulation::update(std::forward_list<std::vector<std::array<float, 3>>> &entities_positions) {
  for (auto &&[system, entity_positions]: std::views::zip(m_motion_systems, entities_positions)) {
    std::visit([&entity_positions](auto &obj) { obj.update(entity_positions); }, system);
  }
}
