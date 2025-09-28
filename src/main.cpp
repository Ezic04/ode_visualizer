#include "gui/App/App.hpp"

#include <print>

int main(int argc, char **argv) {
  App app(argc, argv);
  return app.exec();
}