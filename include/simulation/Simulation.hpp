#pragma once

#include <vector>

#include "IO/Window.hpp"
#include "IO/InputHandler.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Program.hpp"
#include "graphics/Mesh.hpp"
#include "graphics/Vec3.hpp"

namespace simulation {

class Simulation {
public:

  Simulation(void);
  ~Simulation(void);

  void run(void);
  void addEntity(const graphics::Vec3& position);

private:

  std::vector<graphics::Mesh> m_entities;

  IO::Window m_window;
  IO::InputHandler m_input_handler;
  graphics::Camera m_camera;
  graphics::Program m_graphics_program;

};

}