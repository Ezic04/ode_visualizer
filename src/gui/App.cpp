#include "gui/App.hpp"

#include "gui/MainWindow.hpp"

App::App(int& argc, char** argv) : QApplication(argc, argv) {
  m_main_window.show();
}