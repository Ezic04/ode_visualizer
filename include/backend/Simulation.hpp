#pragma once

#include <array>
#include <chrono>
#include <cstdint>
#include <forward_list>
#include <vector>

#include "backend/parser.hpp"

namespace simulation {

struct Entity {
  uint16_t id;
  std::vector<float> vars;
};

struct MotionSystemState {
  std::vector<expr::ExprPtr> m_equations_system;
  parser::VariableMap var_names;
  std::vector<Entity> entities;
  std::vector<std::array<float, 3>> entity_positions;
};

struct Emiter {
  MotionSystemState system;
  std::vector<float> initial_conditions;
  float time_limit;
};

class Simulation {
 public:
  Simulation() = default;
  void addEquationsSystem(const std::vector<expr::ExprPtr> &system, parser::VariableMap var_names);
  void update();
  void addEntity(std::vector<float> &&initial_conditions);
  const std::vector<std::array<float, 3>> &getPositions();

 private:
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<float>> m_prev_time =
      std::chrono::steady_clock::now();
  std::forward_list<MotionSystemState> m_equation_systems;
  std::forward_list<Emiter> m_emiter_systems;
};

}  // namespace simulation