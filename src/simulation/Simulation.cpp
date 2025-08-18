#include "simulation/Simulation.hpp"
#include "graphics/Mesh.hpp"

using namespace simulation;

Simulation::Simulation(
  void
) : m_window(800, 600, "ODE Visualizer"),
    m_input_handler(&m_window),
    m_camera(graphics::Camera::Parameters{
      .position       = { -5.0f, 0.0f, 0.0f },
      .screen_width   = 800,
      .screen_height  = 600
    }),
    m_graphics_program(VERT_PATH, FRAG_PATH)
{
  m_input_handler.attachKeyCallback(87, [&](void) { m_camera.moveLongitudinal(0.001f); });
  m_input_handler.attachKeyCallback(83, [&](void) { m_camera.moveLongitudinal(-0.001f); });
  m_input_handler.attachKeyCallback(68, [&](void) { m_camera.moveLateral(0.001f); });
  m_input_handler.attachKeyCallback(65, [&](void) { m_camera.moveLateral(-0.001); });
  m_input_handler.attachKeyCallback(32, [&](void) { m_camera.moveVertical(0.001); });
  m_input_handler.attachKeyCallback(341, [&](void) { m_camera.moveVertical(-0.001); });
  m_input_handler.attachMouseCallback([&](const IO::Window::MouseState& mouse_state) {
    m_camera.tiltPitch(mouse_state.dy * 0.1);
    m_camera.tiltYaw(mouse_state.dx * 0.1);
  }); 
}

Simulation::~Simulation(void) {

  // free resources

}

void Simulation::run(void) {
  while(!m_window.shouldClose()) {
    m_window.clear();
    m_window.pollEvents();
    m_input_handler.handleInputs();
    for(auto& entity : m_entities) {
      auto entity_position = entity.getTranslation();

      // simulation tick

      m_camera.render(entity);
    }
    m_window.swapBuffers();
  }
}

void Simulation::addEntity(const graphics::Vec3& position) {
  graphics::Mesh m = graphics::getDemoMesh(m_graphics_program);
  m.translate(position);
  m_entities.emplace_back(std::move(m));
}

// std::vector<float> vertices = {-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};

// std::vector<unsigned int> indices = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};

// Simulation::Simulation(std::array<std::string, kDim> equations, std::string free_varible)
//     : is_running(false), time(0.0), win(800, 600, "ode_visualiser"), cam(graphics::Camera::Parameters()),
//       gpu_prog(shader_path + "/shader.vert", shader_path + "/shader.frag") {
//   for (auto &eq : equations) {
//     auto i = 0;
//     while (std::isspace(eq[i])) { ++i; }
//     auto begin = i;
//     while (!std::isspace(eq[i])) { ++i; }
//     auto end = i - 1;
//     if (eq[end] != '\'') { throw expr::ParserException("lhs must be derivative of "); }
//     while (std::isspace(eq[i])) { ++i; }
//     if (eq[i] != '=') { throw expr::ParserException("varible name contains spaces or equal sign not found"); }
//     std::string var_name = eq.substr(begin, end);
//     var_names.index_of(var_name);
//     eq = eq.substr(i + 1, eq.size());
//   }
//   var_names.index_of(free_varible);
//   // for (auto it : var_names.index_to_name) { std::cout << it; }
//   for (const auto &it : equations) { system.emplace_back(expr::parseExpr(it, var_names)); }
// }

// void Simulation::addEntity(graphics::Vec3 initial_position) {
//   entities.emplace_back(Mesh(vertices, indices, gpu_prog));
//   entities.back().setTranslation(initial_position);
// }

// void Simulation::run(const bool *simulate) {
//   int i = 0;
//   while (*simulate) {
//     if (is_running) {
//       for (auto &e : entities) {
//         win.clear();
//         win.pollEvents();
//         // if (!(++i % 100)) { std::println("t={}: x={},  x_rk4={}", time, std::sin(time), e.x); }
//         cam.render(e);
//         e.setTranslation(nextPosition(e.getTranslation()));
//         time += step;
//         win.swapBuffers();
//       }
//       // FloatType x = 1.0;
//       // FloatType t = 0.0;
//       // FloatType x_euler, x_heun, x_rk4;
//       // x_euler = x_heun = x_rk4 = x;
//       // for (size_t i = 0; i <= spu * 10; ++i) {
//       //   if (i % spu == 0) {
//       //     std::println("t={}: x={}, x_euler={}, x_heun={}, x_rk4={}", t, std::exp(t), x_euler, x_heun, x_rk4);
//       //     x_euler = solver::euler({system[0]}, {x_euler, t}, step).front();
//       //     x_heun = solver::heun({system[0]}, {x_heun, t}, step).front();
//       //     x_rk4 = solver::rk4({system[0]}, {x_rk4, t}, step).front();
//       //     t += step;
//       //   }
//       // }
//     }
//   }
// }

// Vec3 Simulation::nextPosition(const Vec3 &position) {
//   return toVec3(solver::rk4(system, {position.x, position.y, position.z, time}, step));
// }

// Vec3 Simulation::toVec3(const std::vector<FloatType> &vec) {
//   return {static_cast<float>(vec[0]), static_cast<float>(vec[1]), static_cast<float>(vec[2])};
// }