#include <iostream>

#include "graphics/Window.hpp"

int main() {

  try {
    graphics::Window w(1280, 720, "Demo Window");
  } catch (std::runtime_error& error) {
    std::cout << error.what();
  }

  while(true) {}

}
