#pragma once

#include <QApplication>

#include "gui/Components/MainWindow.hpp"

class App : public QApplication{
public:

  App(int& argc, char** argv);

private:

  MainWindow m_main_window;

};