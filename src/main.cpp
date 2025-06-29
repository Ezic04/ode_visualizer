#include <string>
#include <vector>

#include "IO/InputHandler.hpp"
#include "IO/Window.hpp"

#include "graphics/Mesh.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Program.hpp"

std::string shader_path = SHADER_PATH;

std::string vert_path = shader_path + "/shader.vert";
std::string frag_path = shader_path + "/shader.frag";



std::vector<float> vertices = {
  -1.0f, -1.0f, 0.0f,
  0.0f, -1.0f, 1.0f,
  1.0f, -1.0f, 0.0f,
  0.0f, 1.0f, 0.0f
};

std::vector<unsigned int> indices = {
  0, 3, 1,
  1, 3, 2,
  2, 3, 0,
  0, 1, 2
};

int main() {
  IO::Window window(800, 600, "Test Window");
  IO::InputHandler input_handler(&window);
  graphics::Program program(vert_path, frag_path);
  graphics::Mesh mesh(vertices, indices, program);
  graphics::Camera camera(graphics::Camera::Parameters{
    .position       = {-5.0f, 0.0f, 0.0f},
    .screen_width   = 800, 
    .screen_height  = 600
  });

  input_handler.attachKeyCallback(87, [&](void){ camera.moveLongitudinal(0.001f); });
  input_handler.attachKeyCallback(83, [&](void){ camera.moveLongitudinal(-0.001f); });
  input_handler.attachKeyCallback(68, [&](void){ camera.moveLateral(0.001f); });
  input_handler.attachKeyCallback(65, [&](void){ camera.moveLateral(-0.001); });
  input_handler.attachKeyCallback(32, [&](void){ camera.moveVertical(0.001); });
  input_handler.attachKeyCallback(341, [&](void){ camera.moveVertical(-0.001); });
  input_handler.attachMouseCallback([&](const IO::Window::MouseState& mouse_state) {
    camera.tiltPitch(mouse_state.dy * 0.1);
    camera.tiltYaw(mouse_state.dx * 0.1);
  });

  while(!window.shouldClose()) {
    window.clear();
    window.pollEvents();

    input_handler.handleInputs();

    camera.render(mesh);
    mesh.rotate({0.005f, 0.005f, 0.005f});

    window.swapBuffers();
  }
}
