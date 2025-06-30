#include "IO/Window.hpp"

#include <iostream>
#include <stdexcept>

#include <cassert>
#include <cstring>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

using namespace IO;

Window::Window(
  int width, 
  int height, 
  const std::string& title
) : m_is_initialized(false),
    m_mouse_first_moved(true)
{

  std::memset(m_key_state, 0, sizeof(bool) * 1024);

  if (!glfwInit()) {
    throw std::runtime_error("Failed to initialise GLFW");
  }

  glfwWindowHint(GLFW_SAMPLES, 4);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
  glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
  glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
  glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);

  m_window = glfwCreateWindow(width, height, title.c_str(), nullptr, nullptr);
  if (!m_window) {
    glfwTerminate();
    throw std::runtime_error("Failed to initialize a GLFW window instance.");
  }
  glfwMakeContextCurrent(static_cast<GLFWwindow*>(m_window));
  glfwSetInputMode(static_cast<GLFWwindow*>(m_window), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
  glfwSetWindowUserPointer(static_cast<GLFWwindow*>(m_window), this);
  this->createCallbacks();

  if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
    glfwTerminate();
    throw std::runtime_error("Failed to initialize OpenGL context");
  }

  glEnable(GL_DEPTH_TEST);

  m_is_initialized = true;
  
}

Window::~Window(void) {
  if(!m_is_initialized) { return; }
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
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
}

void Window::swapBuffers(void) {
  assert(m_is_initialized);
  glfwSwapBuffers(static_cast<GLFWwindow*>(m_window));
}

void Window::pollEvents(void) {
  assert(m_is_initialized);
  glfwPollEvents();
}

Window::MouseState Window::getMouseState(void) {
  auto tmp = m_mouse_state; //glfw polls the mouse
  m_mouse_state.dx = 0.0f;  //on mouse event callback
  m_mouse_state.dy = 0.0f;  //so dx and dy can linger
  return tmp;               //holding nonzero values
}

void Window::createCallbacks(void) {
  glfwSetKeyCallback(
    static_cast<GLFWwindow*>(m_window), 
    [](GLFWwindow* glfw_window, int key, int code, int action, int mode) {
      Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
      window->handleKeyEvent(key, action);
    }
  );
  glfwSetCursorPosCallback(
    static_cast<GLFWwindow*>(m_window), 
    [](GLFWwindow* glfw_window, double x_pos, double y_pos) {
      Window* window = static_cast<Window*>(glfwGetWindowUserPointer(glfw_window));
      window->handleMouseEvent(x_pos, y_pos);
    }
  );
  glfwSetErrorCallback([](int error, const char* desc) { 
    std::cout << "GLFW error: " << error << " " << desc; 
  }); 
}

void Window::handleMouseEvent(double x_pos, double y_pos) {
  if (m_mouse_first_moved) {
    m_mouse_state.x_pos = x_pos;
    m_mouse_state.y_pos = y_pos;
    m_mouse_first_moved = false;
  }

  m_mouse_state.dx = x_pos - m_mouse_state.x_pos;
  m_mouse_state.dy = m_mouse_state.y_pos - y_pos;
  m_mouse_state.x_pos = x_pos;
  m_mouse_state.y_pos = y_pos;
}

void Window::handleKeyEvent(int key, int action) {
  if (key < 0 || key > 1024) { return; }
  switch (action) {
    case GLFW_PRESS:    m_key_state[key] = true;  break;
    case GLFW_RELEASE:  m_key_state[key] = false; break;
    default: break;
  }
}