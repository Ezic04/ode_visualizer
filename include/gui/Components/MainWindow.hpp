#pragma once

#include <QMainWindow>

#include "gui/components/SimulationManager.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow(void);

private:
  SimulationManager *m_simulation_manager;
};