#include "graphics/Window.hpp"

#include <iostream>
#include <cassert>

#include <stdexcept>
#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace graphics;

Window::Window(int width, int height, const char* title) : m_is_initialized(false) {

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
    throw std::runtime_error("Failed to initialize a GLFW window instance.");
  }
  //glfwGetFramebufferSize(static_cast<GLFWwindow*>(m_window), &width, &height);
  glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_window));
  glfwSetErrorCallback([](int error, const char* desc) { 
    std::cout << "GLFW error: " << error << " " << desc; 
  });

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    throw std::runtime_error("Failed to initialize OpenGL context");
  }

  //glEnable(GL_DEPTH_TEST); // enable depth buffer
  //glViewport(0, 0, width, height);

  m_is_initialized = true;

}

Window::~Window(void) {
  if(!m_is_initialized) { return; } //nothing to do here
  glfwDestroyWindow(static_cast<GLFWwindow*>(m_window));
  glfwTerminate();
}

bool Window::shouldClose(void) {
  assert(m_is_initialized);
  return glfwWindowShouldClose(static_cast<GLFWwindow*>(m_window)) != 0;
}

void Window::clear(void) {
  assert(m_is_initialized);
  glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
  glClear(GL_COLOR_BUFFER_BIT);
}

void Window::swapBuffers(void) {
  assert(m_is_initialized);
  glfwSwapBuffers(static_cast<GLFWwindow*>(m_window));
}

void Window::pollEvents(void) {
  assert(m_is_initialized);
  glfwPollEvents();
}