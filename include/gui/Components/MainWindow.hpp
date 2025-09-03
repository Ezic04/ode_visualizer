#pragma once

#include <QMainWindow>

#include "gui/components/SimulationController.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow(void);

private:
  SimulationController* m_simulation_controller;
};