#include "simulation/Simulation.hpp"

#include <cctype>
#include <cmath>
#include <iostream>
#include <print>

#include "IO/Window.hpp"
#include "expr/expr.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Program.hpp"
#include "graphics/Vec3.hpp"
#include "solver/solver.hpp"

namespace simulation {

std::string shader_path = SHADER_PATH;

std::vector<float> vertices = {-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};

std::vector<unsigned int> indices = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};

Simulation::Simulation(std::array<std::string, kDim> equations, std::string free_varible)
    : is_running(false), time(0.0), win(800, 600, "ode_visualiser"), cam(graphics::Camera::Parameters()),
      gpu_prog(shader_path + "/shader.vert", shader_path + "/shader.frag") {
  for (auto &eq : equations) {
    auto i = 0;
    while (std::isspace(eq[i])) { ++i; }
    auto begin = i;
    while (!std::isspace(eq[i])) { ++i; }
    auto end = i - 1;
    if (eq[end] != '\'') { throw expr::ParserException("lhs must be derivative of "); }
    while (std::isspace(eq[i])) { ++i; }
    if (eq[i] != '=') { throw expr::ParserException("varible name contains spaces or equal sign not found"); }
    std::string var_name = eq.substr(begin, end);
    var_names.index_of(var_name);
    eq = eq.substr(i + 1, eq.size());
  }
  var_names.index_of(free_varible);
  // for (auto it : var_names.index_to_name) { std::cout << it; }
  for (const auto &it : equations) { system.emplace_back(expr::parseExpr(it, var_names)); }
}

void Simulation::addEntity(graphics::Vec3 initial_position) {
  entities.emplace_back(Mesh(vertices, indices, gpu_prog));
  entities.back().setTranslation(initial_position);
}

void Simulation::run(const bool *simulate) {
  int i = 0;
  while (*simulate) {
    if (is_running) {
      for (auto &e : entities) {
        win.clear();
        win.pollEvents();
        // if (!(++i % 100)) { std::println("t={}: x={},  x_rk4={}", time, std::sin(time), e.x); }
        cam.render(e);
        e.setTranslation(nextPosition(e.getTranslation()));
        time += step;
        win.swapBuffers();
      }
      // FloatType x = 1.0;
      // FloatType t = 0.0;
      // FloatType x_euler, x_heun, x_rk4;
      // x_euler = x_heun = x_rk4 = x;
      // for (size_t i = 0; i <= spu * 10; ++i) {
      //   if (i % spu == 0) {
      //     std::println("t={}: x={}, x_euler={}, x_heun={}, x_rk4={}", t, std::exp(t), x_euler, x_heun, x_rk4);
      //     x_euler = solver::euler({system[0]}, {x_euler, t}, step).front();
      //     x_heun = solver::heun({system[0]}, {x_heun, t}, step).front();
      //     x_rk4 = solver::rk4({system[0]}, {x_rk4, t}, step).front();
      //     t += step;
      //   }
      // }
    }
  }
}

Vec3 Simulation::nextPosition(const Vec3 &position) {
  return toVec3(solver::rk4(system, {position.x, position.y, position.z, time}, step));
}

Vec3 Simulation::toVec3(const std::vector<FloatType> &vec) {
  return {static_cast<float>(vec[0]), static_cast<float>(vec[1]), static_cast<float>(vec[2])};
}

} // namespace simulation