#pragma once

#include <array>
#include <chrono>
#include <vector>

#include "backend/parser.hpp"

namespace simulation {

class Simulation {
public:
  Simulation() = default;
  void setEquationsSystem(const std::vector<expr::ExprPtr> &system, parser::VariableMap var_names);
  void update();
  void addEntity(const std::array<float, 3> &position);
  const std::vector<std::array<float, 3>> &getPositions();

private:
  std::chrono::time_point<std::chrono::steady_clock, std::chrono::duration<float>> m_prev_time =
      std::chrono::steady_clock::now();
  std::vector<expr::ExprPtr> m_equations_system;
  parser::VariableMap m_var_names;
  std::vector<std::array<float, 3>> m_positions;
  float m_time = 0.0;
};

} // namespace simulation