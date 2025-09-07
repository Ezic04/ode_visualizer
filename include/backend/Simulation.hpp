#pragma once

#include <array>
#include <chrono>
#include <vector>

#include "backend/parser.hpp"

namespace simulation {

struct MotionSystemState {
  std::vector<expr::ExprPtr> m_equations_system;
  parser::VariableMap var_names;
  std::vector<std::vector<float>> entity_vars;
  std::vector<std::array<float, 3>> entity_positions;
};

class Simulation {
 public:
  Simulation() : m_motion_states(1) {};
  void setEquationsSystem(const std::vector<expr::ExprPtr> &system, parser::VariableMap var_names);
  void update();
  void addEntity(std::vector<float> &&initial_conditions);
  const std::vector<std::array<float, 3>> &getPositions();

 private:
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<float>> m_prev_time =
      std::chrono::steady_clock::now();
  std::vector<MotionSystemState> m_motion_states;
};

}  // namespace simulation