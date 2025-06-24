#include <iostream>

#include "graphics/Window.hpp"

int main() {

  graphics::Window* w;

  try {
    w = new graphics::Window(1280, 720, "Demo Window");
  } catch (std::runtime_error& error) {
    std::cout << error.what();
  }

  while(true) {}

}