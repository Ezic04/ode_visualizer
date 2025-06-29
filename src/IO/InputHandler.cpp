#include "IO/InputHandler.hpp"

#include <algorithm>

using namespace IO;

InputHandler::InputHandler(
  Window* window
) : m_window(window), 
    m_mouse_callback(k_default_mouse_callback) 
{}

void InputHandler::attachKeyCallback(
  int keycode, 
  const std::function<void(void)>& action
) {
  for (auto& callback : m_key_callbacks) {
    if (callback.keycode == keycode) {
      callback.action = action;
      return;
    }
  }
  m_key_callbacks.emplace_back(KeyCallback{keycode, action});
}

void InputHandler::detachKeyCallback(int keycode) {
  m_key_callbacks.erase(std::find_if(
    m_key_callbacks.begin(),
    m_key_callbacks.end(),
    [&keycode](const KeyCallback& callback) {
      return callback.keycode == keycode;
    }
  ));
}

void InputHandler::attachMouseCallback(
  const std::function<void(const Window::MouseState&)>& action
) { m_mouse_callback = action; }

void InputHandler::detachMouseCallback(void) {
  m_mouse_callback = k_default_mouse_callback;
}

void InputHandler::handleInputs(void) {
  m_mouse_callback(m_window->getMouseState());
  auto key_state = m_window->getKeyState();
  for (const auto& key_callback : m_key_callbacks) {
    if (key_state[key_callback.keycode])
      key_callback.action();
  }
}