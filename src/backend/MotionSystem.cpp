#include "backend/MotionSystem.hpp"

#include <array>
#include <ranges>
#include <vector>

#include "backend/solver.hpp"

void MotionSystem::update(std::vector<std::array<float, 3>> &entity_positions) {
  for (auto &&[entity, pos] : std::views::zip(entities, entity_positions)) {
    solver::rk4(m_equations_system, entity.vars, dt);
    std::copy_n(entity.vars.begin(), 3, pos.begin());
  }
}