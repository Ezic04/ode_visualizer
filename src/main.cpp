#include <cmath>
#include <iostream>
#include <print>

#include "expr/expr.hpp"
#include "solver/solver.hpp"
#include "utility/utility.hpp"

constexpr FloatType step = 0.01;
constexpr int spu = 1 / step;

int main() {
  try {
    FloatType x = 1.0;
    FloatType t = 0.0;
    std::string expr_str;
    std::cout << "x' = ";
    std::cin >> expr_str;
    std::cout << "x(0) = ";
    std::cin >> x;
    auto [expr, var_map] = expr::parseExpr(expr_str);
    FloatType x_euler, x_heun, x_rk4;
    x_euler = x_heun = x_rk4 = x;
    for (size_t i = 0; i <= spu * 10; ++i) {
      if (i % spu == 0) {
        std::println("t={}: x={}, x_euler={}, x_heun={}, x_rk4={}", t, std::exp(t), x_euler, x_heun, x_rk4);
      }
      x_euler = solver::euler({expr}, {x_euler, t}, step).front();
      x_heun = solver::heun({expr}, {x_heun, t}, step).front();
      x_rk4 = solver::rk4({expr}, {x_rk4, t}, step).front();
      t += step;
    }
  } catch (std::exception &e) { std::cout << e.what() << '\n'; }
  return 0;
}
