#pragma once
#include <cstdint>
#include <variant>
#include <vector>

#include "backend/expr.hpp"
#include "backend/parser.hpp"

struct Entity {
  uint16_t id;
  std::vector<float> vars;
};

struct MotionSystem {
  std::vector<expr::ExprPtr> m_equations_system;
  parser::VariableMap var_names;
  std::vector<Entity> entities;
  float dt;
  void update(std::vector<std::array<float, 3>>& entity_positions);
};

struct Emiter : public MotionSystem {
  std::vector<float> initial_conditions;
  float time_limit;
  void update(std::vector<std::array<float, 3>>& entity_positions) {};
};

using MotionSystemBase = std::variant<MotionSystem, Emiter>;