#pragma once

#include "expr/expr.hpp"
#include "solver/solver.hpp"
#include "utility/utility.hpp"

namespace simulation {

constexpr FloatType step = 0.01;

class Simulation {
public:
  Simulation(solver::System system, expr::VariableMap var_names);
  ~Simulation(void);

  void run(void);
  // void addEntity(const graphics::Vec3 &position);

private:

  void updatePositions();
  // graphics::Vec3 toVec3(const std::vector<FloatType> &vec);

  solver::System m_system;
  expr::VariableMap m_var_names;
  // std::vector<graphics::Vec3> m_positions;
  FloatType m_time;

};

}