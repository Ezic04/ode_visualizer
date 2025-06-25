#include <cmath>
#include <iostream>
#include <print>

#include "expr/expr.hpp"
#include "solver/solver.hpp"
#include "utility/utility.hpp"

constexpr FloatType step = 0.01;

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
    FloatType x_euler = x;
    FloatType x_heun = x;
    for (size_t i = 0; i <= 400; ++i) {
      if (i % 100 == 0) {
        std::println("t={}: x={}, x_euler={}, x_heun={}", t, std::exp(t), x_euler, x_heun);
      }
      // x_euler = solver::euler(expr, x_euler, t, step, {{"x", x_euler}, {"t", t}});
      // x_heun = solver::heun(expr, x_heun, t, step, {{"x", x_heun}, {"t", t}});
      t += step;
    }
  } catch (std::exception &e) { std::cout << e.what() << '\n'; }
  return 0;
}
