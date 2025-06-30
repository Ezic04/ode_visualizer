#pragma once 

#include <string>

namespace IO {

/* 
 * @brief Wrapper around 
 *  GLFW library for creating 
 *  and managing a graphic window
 *  with it's OpenGL context.
 */ 
class Window {
public:

  /*
   * @brief Structure for storing 
   *  and passing around mouse 
   *  state data.
   */
  struct MouseState {
    float x_pos = 0.0f;
    float y_pos = 0.0f;
    float dx    = 0.0f;
    float dy    = 0.0f;
  };

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
  Window(int width, int height, const std::string& title);

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

  /*
   * @brief Returns the array
   *  of bools representing the
   *  state of each key.
   * 
   * @return Array of bools representing
   *  current state of all the keys.
   */
  const bool* const getKeyState(void) { return m_key_state; }

  /*
   * @brief Returns mouse state
   *  data containing current mouse
   *  position and change in position 
   *  since the last mouse poll.
   * 
   * @return Mouse state data.
   */
  MouseState getMouseState(void);

private:

  void createCallbacks(void);
  void handleMouseEvent(double x_pos, double y_pos);
  void handleKeyboardEvent(int key, int action);

  void* m_window; //GLFWwindow* undercover
  bool m_key_state[1024];
  MouseState m_mouse_state;
  bool m_mouse_first_moved;
  bool m_is_initialized;

};
    
}