#pragma once

#include <QMainWindow>

#include "gui/SimulationController.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:

  MainWindow(QWidget* parent = nullptr);
  ~MainWindow(void);

private:

  SimulationController m_simulation_controller;

};