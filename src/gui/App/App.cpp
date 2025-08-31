#include "gui/App/App.hpp"

App::App(int& argc, char** argv) : QApplication(argc, argv) {
  m_main_window.show();
}