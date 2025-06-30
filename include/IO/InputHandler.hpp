#pragma once

#include <vector>
#include <functional>

#include "IO/Window.hpp"

namespace IO {

class InputHandler {
public:

  InputHandler(Window* window);

  void attachKeyCallback(int keycode, const std::function<void(void)>& action);
  void detachKeyCallback(int keycode);
  void attachMouseCallback(const std::function<void(const Window::MouseState&)>& action);
  void detachMouseCallback(void);
  void handleInputs(void);

private:

  static constexpr auto k_default_mouse_callback = [](const Window::MouseState&) -> void { return; };

  struct KeyCallback {
    int keycode;
    std::function<void(void)> action;
  };

  std::vector<KeyCallback> m_key_callbacks;
  std::function<void(const Window::MouseState&)> m_mouse_callback;
  Window* m_window;

};

};
