#include "graphics/Window.hpp"

#include <iostream>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace graphics;

Window::Window(void) {
  if (!glfwInit()) {
    std::cout << "Failed to initialise GLFW\n";
  } else {
    std::cout << "Initialised GLFW\n";
  }
}
