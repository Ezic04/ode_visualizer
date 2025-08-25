#pragma once

#include <vector>

#include "expr/expr.hpp"
#include "solver/solver.hpp"
#include "utility/utility.hpp"

constexpr FloatType step = 0.01;

class Simulation {
public:
  Simulation() = default;
  void setSystem(solver::System system, expr::VariableMap var_names);
  void nextStep(void);
  void addEntity(const std::vector<FloatType> &position);
  std::vector<std::vector<FloatType>> getPositions();

private:
  solver::System m_system;
  expr::VariableMap m_var_names;
  std::vector<std::vector<FloatType>> m_positions;
  FloatType m_time;
};
