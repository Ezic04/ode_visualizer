#include "simulation/Simulation.hpp"

#include <cctype>
#include <cmath>
#include <cstddef>
#include <iostream>
#include <print>

#include "expr/expr.hpp"
#include "solver/solver.hpp"

constexpr FloatType step = 0.01;
constexpr int spu = 1 / step;

Simulation::Simulation(std::array<std::string, kDim> equations, std::string free_varible) {
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
  for (auto it : equations) { std::cout << it << '\n'; }
  for (size_t i = 0; i < kDim; ++i) { system[i] = expr::parseExpr(equations[i], var_names); }

  FloatType x = 1.0;
  FloatType t = 0.0;
  FloatType x_euler, x_heun, x_rk4;
  x_euler = x_heun = x_rk4 = x;
  for (size_t i = 0; i <= spu * 10; ++i) {
    if (i % spu == 0) {
      std::println("t={}: x={}, x_euler={}, x_heun={}, x_rk4={}", t, std::exp(t), x_euler, x_heun, x_rk4);
    }
    x_euler = solver::euler({system[0]}, {x_euler, t}, step).front();
    x_heun = solver::heun({system[0]}, {x_heun, t}, step).front();
    x_rk4 = solver::rk4({system[0]}, {x_rk4, t}, step).front();
    t += step;
  }
}
