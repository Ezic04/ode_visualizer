#include "graphics/Window.hpp"

#include <iostream>

#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace graphics;

Window::Window(int width, int height, const char* title) {
  
  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialise GLFW");
  }

  glfwWindowHint(GLFW_SAMPLES, 4);  // 4x antialiasing
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);  // for macOS

  m_window = glfwCreateWindow(width, height, title, nullptr, nullptr);

  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to initialise a GLFW window instance.");
  }

  glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_window));

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    throw std::runtime_error("Failed to initialize OpenGL context");
  }

  std::cout << "OpenGL Version: " << glGetString(GL_VERSION) << "\n";

}
