#pragma once

#include <vector>

#include "backend/parser.hpp"
#include "backend/utility.hpp"

constexpr FloatType step = 0.01;

namespace simulation {

class Simulation {
public:
  Simulation() = default;
  void setEquationsSystem(std::vector<expr::ExprPtr> system, parser::VariableMap var_names);
  void update();
  void addEntity(const std::vector<FloatType> &position);
  const std::vector<std::vector<FloatType>> &getPositions();

private:
  std::vector<expr::ExprPtr> m_equations_system;
  parser::VariableMap m_var_names;
  std::vector<std::vector<FloatType>> m_positions;
  FloatType m_time;
};

} // namespace simulation