#pragma once

#include <vector>
#include <functional>

#include "IO/Window.hpp"

namespace IO {

/*
 * @brief Class for assigning 
 *  and calling both mouse and 
 *  key callbacks.
 */
class InputHandler {
public:

  /*
   * @brief Creates a new 
   *  input handler object.
   * 
   * @param window Pointer to
   *  a window object that will
   *  be asked for key and mouse
   *  states.
   */
  InputHandler(Window* window);

  /* 
   * @brief Attaches a key callback
   *  that will be executed upon key
   *  press. If a given key already 
   *  has a callback assigned to it
   *  the new callback will take its
   *  place.
   * 
   * @param keycode Key code of the 
   *  key that should have the callback
   *  assigned.
   * @param action Callback to attach.
   */
  void attachKeyCallback(int keycode, const std::function<void(void)>& action);

  /*
   * @brief Detaches a key callback. 
   *  If a given key doesn't have a
   *  callback assigned the method 
   *  returns.
   * 
   * @param keycode Key code of the 
   *  key that should have it's callback
   *  detached.
   */
  void detachKeyCallback(int keycode);

  /*
   * @brief Attaches a mouse callback.
   *  If there's already a mouse callback
   *  attached the new callback will take
   *  it's place.
   * 
   * @param action Callback to attach.
   */
  void attachMouseCallback(const std::function<void(const Window::MouseState&)>& action);

  /*
   * @brief Detaches the mouse callback
   *  by replacing it with the default
   *  empty callback.
   */
  void detachMouseCallback(void);

  /*
   * @brief Requests the key and mouse
   *  state from the window and executes
   *  callbacks if needed.
   */
  void handleInputs(void);

private:

  /*
   * @brief Structure describing 
   *  an attached key callback.
   */
  struct KeyCallback {
    int keycode;
    std::function<void(void)> action;
  };

  /** Default empty mouse callback */
  static constexpr auto k_default_mouse_callback = [](const Window::MouseState&) -> void { return; };
  
  std::vector<KeyCallback> m_key_callbacks;
  std::function<void(const Window::MouseState&)> m_mouse_callback;
  Window* m_window;

};

};
