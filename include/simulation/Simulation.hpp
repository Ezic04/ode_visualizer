#pragma once
#include "expr/expr.hpp"
#include <array>
#include <cstdint>

constexpr uint8_t kDim = 3;

class Simulation {
  expr::VaribleMap var_names;
  expr::ExprPtr system[kDim];

public:
  Simulation(std::array<std::string, kDim> equations, std::string free_varible = "t");
};
