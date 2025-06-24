#pragma once 

namespace graphics {

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

private:

  void* m_window; //GLFWwindow* undercover

};
    
}
