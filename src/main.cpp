// #include <cmath>
#include <iostream>
// #include <print>
// #include <string>

// #include "expr/expr.hpp"
#include "simulation/Simulation.hpp"
// #include "solver/solver.hpp"
#include "utility/utility.hpp"

constexpr FloatType step = 0.01;
constexpr int spu = 1 / step;

int main() {
  try {
    Simulation s({"x' = x", "y' = y", "z' = z"});
  } catch (std::exception &e) { std::cout << e.what() << '\n'; }
  return 0;
}
