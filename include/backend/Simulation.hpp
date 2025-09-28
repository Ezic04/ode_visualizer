#pragma once

#include <array>
#include <cstddef>
#include <forward_list>
#include <vector>

#include "backend/MotionSystem.hpp"

class Simulation {
public:
  Simulation() = default;
  void addMotionSystem(const std::string &equations);
  void addEmiter(const std::string &equations, int initial);
  void addEntity(std::vector<float> initial_conditions);
  void removeMotionSystemBase(size_t idx);
  void update(
      std::forward_list<std::vector<std::array<float, 3>>> &entities_positions);

private:
  std::forward_list<MotionSystemBase> m_motion_systems;
};