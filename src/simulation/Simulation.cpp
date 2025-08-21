#include "simulation/Simulation.hpp"
#include "graphics/Mesh.hpp"

using namespace simulation;

Simulation::Simulation(solver::System system, expr::VariableMap var_names)
    : m_system(system), m_var_names(var_names), m_time(0), m_window(800, 600, "ODE Visualizer"),
      m_input_handler(&m_window),
      m_camera(graphics::Camera::Parameters{
          .position = {0.0f, 0.0f, -5.0f}, .rotation{0, 90, 0}, .screen_width = 800, .screen_height = 600}),
      m_graphics_program(VERT_PATH, FRAG_PATH) {
  setupGrphics();
}

Simulation::~Simulation(void) {

  // free resources
}

void Simulation::setupGrphics() {
  m_input_handler.attachKeyCallback(87, [&](void) { m_camera.moveLongitudinal(0.001f); });
  m_input_handler.attachKeyCallback(83, [&](void) { m_camera.moveLongitudinal(-0.001f); });
  m_input_handler.attachKeyCallback(68, [&](void) { m_camera.moveLateral(0.001f); });
  m_input_handler.attachKeyCallback(65, [&](void) { m_camera.moveLateral(-0.001f); });
  m_input_handler.attachKeyCallback(32, [&](void) { m_camera.moveVertical(0.001f); });
  m_input_handler.attachKeyCallback(341, [&](void) { m_camera.moveVertical(-0.001f); });
  m_input_handler.attachMouseCallback([&](const IO::Window::MouseState &mouse_state) {
    m_camera.tiltPitch(mouse_state.dy * 0.1);
    m_camera.tiltYaw(mouse_state.dx * 0.1);
  });
}

void Simulation::run(void) {
  while (!m_window.shouldClose()) {
    m_window.clear();
    m_window.pollEvents();
    m_input_handler.handleInputs();
    for (size_t i = 0; i < m_entities.size(); ++i) {
      m_positions[i] =
          toVec3(solver::rk4(m_system, {m_positions[i].x, m_positions[i].y, m_positions[i].z, m_time}, step));

      m_entities[i].setTranslation(m_positions[i]);

      m_camera.render(m_entities[i]);
    }
    m_window.swapBuffers();
  }
}

void Simulation::addEntity(const graphics::Vec3 &position) {
  graphics::Mesh m = graphics::getDemoMesh(m_graphics_program);
  m.translate(position);
  m_entities.emplace_back(std::move(m));
  m_positions.emplace_back(position);
}

graphics::Vec3 Simulation::toVec3(const std::vector<FloatType> &vec) {
  return {static_cast<float>(vec[0]), static_cast<float>(vec[1]), static_cast<float>(vec[2])};
}