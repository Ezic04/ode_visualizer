#pragma once

#include <QMainWindow>

#include "gui/SimulationControler.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow(void);

private:
  SimulationControler m_adapter;
};