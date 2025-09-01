#pragma once

#include <QMainWindow>

#include <QShortcut>
#include <qkeysequence.h>

#include "gui/Components/SimulationController.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow(void);

private:
  QShortcut* m_show_controls_shortcut = nullptr;

  SimulationController *m_simulation_controller;
};