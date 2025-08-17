#pragma once
#include <array>
#include <cstdint>
#include <vector>

#include "IO/Window.hpp"
#include "expr/expr.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Program.hpp"
#include "graphics/Vec3.hpp"
#include "solver/solver.hpp"
#include "utility/utility.hpp"

constexpr uint8_t kDim = 3;

constexpr FloatType step = 0.01;
constexpr int spu = 1 / step;

using Vec3 = graphics::Vec3;
using Mesh = graphics::Mesh;

namespace simulation {

class Simulation {
public:
  Simulation(std::array<std::string, kDim> equations, std::string free_varible = "t");
  void run(const bool *simualate);
  inline void start() { is_running = true; }
  inline void stop() { is_running = false; }
  void addEntity(Vec3 initial_position);

private:
  Vec3 nextPosition(const Vec3 &position);
  Vec3 toVec3(const std::vector<FloatType> &vec);

  IO::Window win;
  graphics::Camera cam;
  graphics::Program gpu_prog;
  bool is_running;
  expr::VaribleMap var_names;
  solver::System system;
  std::vector<graphics::Mesh> entities;
  FloatType time;
  // std::vector<graphics::Mesh>
};

} // namespace simulation