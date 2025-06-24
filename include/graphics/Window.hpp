#pragma once 

namespace graphics {

/* 
 * @brief Wrapper around 
 *  GLFW library for creating 
 *  and managing a graphic window
 *  with it's OpenGL context.
 */ 
class Window {
public:

  /*
   * @brief Creates a new window 
   *  with an OpenGL context.
   *
   * @param width Window width 
   *  in pixels
   * @param height Window height 
   *  in pixels
   * @param title Window title
   *
   * @throw std::runtime_error In 
   *  case of failure during execution
   *  of any necessary initialization 
   *  steps.
   */
  Window(int width, int height, const char* title);

  /*
   * @brief Destroys the window 
   *  instance by closing GLFW 
   *  and the OpenGL context.
   */
  ~Window(void);

  /*
   * @brief Checks if the window 
   *  should close.
   * 
   * @return bool True if the 
   *  window should close, false
   *  otherwise.
   */
  [[nodiscard]] bool shouldClose(void);

  /*
   * @brief Clears the window's 
   *  color and depth buffers.
   */
  void clear(void);

  /* 
   * @brief Swaps the window's 
   *  frame buffers. 
   */
  void swapBuffers(void);

  /* 
   * @brief Polls the events
   *  mouse and keyboard events. 
   */
  void pollEvents(void);

private:

  void* m_window; //GLFWwindow* undercover
  bool m_is_initialized;

};
    
}
