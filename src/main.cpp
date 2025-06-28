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
  graphics::Camera camera;

  while(!window.shouldClose()) {
    window.clear();
    window.pollEvents();

    camera.render(mesh);

    window.swapBuffers();
  }
}
