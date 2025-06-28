#include <string>
#include <vector>

#include "graphics/Mesh.hpp"
#include "graphics/Window.hpp"
#include "graphics/Camera.hpp"
#include "graphics/Program.hpp"

std::string vert_path = "C:/Users/Julek/Desktop/Szkoła/GitProjects/ode_visualizer/shader/shader.vert";
std::string frag_path = "C:/Users/Julek/Desktop/Szkoła/GitProjects/ode_visualizer/shader/shader.frag";

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
  graphics::Window window(800, 600, "Test Window");
  graphics::Program program(vert_path, frag_path);
  graphics::Mesh mesh(vertices, indices, program);
  graphics::Camera camera(graphics::Camera::Parameters{
    .position       = {-5.0f, 0.0f, 0.0f},
    .screen_width   = 800, 
    .screen_height  = 600
  });

  while(!window.shouldClose()) {
    window.clear();
    window.pollEvents();

    const bool* const key_state = window.getKeyState();
    if(key_state[87]) { camera.translate({0.001f, 0.0f, 0.0f}); }
    if(key_state[83]) { camera.translate({-0.001f, 0.0f, 0.0f}); }
    if(key_state[68]) { camera.translate({0.0f, 0.0f, 0.001f}); }
    if(key_state[65]) { camera.translate({0.0f, 0.0f, -0.001f}); }

    camera.render(mesh);
    mesh.rotate({0.005f, 0.005f, 0.005f});

    window.swapBuffers();
  }
}
