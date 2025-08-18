#pragma once

#include <vector>

#include "IO/InputHandler.hpp"
#include "IO/Window.hpp"
#include "expr/expr.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Program.hpp"
#include "graphics/Vec3.hpp"
#include "solver/solver.hpp"
#include "utility/utility.hpp"

namespace simulation {

constexpr FloatType step = 0.01;

class Simulation {
public:
  Simulation(solver::System system, expr::VariableMap var_names);
  ~Simulation(void);

  void run(void);
  void addEntity(const graphics::Vec3 &position);

private:
  void setupGrphics();
  void updatePositions();
  graphics::Vec3 toVec3(const std::vector<FloatType> &vec);

  solver::System m_system;
  expr::VariableMap m_var_names;
  std::vector<graphics::Vec3> m_positions;
  FloatType m_time;

  std::vector<graphics::Mesh> m_entities;
  IO::Window m_window;
  IO::InputHandler m_input_handler;
  graphics::Camera m_camera;
  graphics::Program m_graphics_program;
};

} // namespace simulation