#include <string>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <glad/glad.h>

#include "graphics/Mesh.hpp"
#include "graphics/Window.hpp"

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

  glm::mat4 projection = glm::perspective(45.0f, 800 / (float)600, 0.1f, 100.0f);
  glm::mat4 view = glm::lookAt(
    glm::vec3(4,3,3),
    glm::vec3(0,0,0),
    glm::vec3(0,1,0)
  );

  while(!window.shouldClose()) {
    window.clear();

    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f));

    program.use();

    glUniformMatrix4fv(program.getUniformModelID(), 1, GL_FALSE, glm::value_ptr(model));
    glUniformMatrix4fv(program.getUniformProjectionID(), 1, GL_FALSE, glm::value_ptr(projection));
    glUniformMatrix4fv(program.getUniformViewID(), 1, GL_FALSE, glm::value_ptr(view));

    mesh.render();

    glUseProgram(0);

    window.swapBuffers();
  }

}
