#pragma once

#include <QMainWindow>

#include "gui/components/Viewport.hpp"
#include "gui/components/SimulationManager.hpp"

class MainWindow : public QMainWindow {
  Q_OBJECT
public:
  MainWindow(QWidget *parent = nullptr);
  ~MainWindow(void) = default;

private slots:

  void openPreferences(void);

private:

  void setupMenuBar(void);

  Viewport m_viewport;
  SimulationManager m_simulation_manager;
};