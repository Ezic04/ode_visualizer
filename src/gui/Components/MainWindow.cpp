#include "gui/components/MainWindow.hpp"

#include <QWidget>
#include <QShortcut>
#include <QDockWidget>
#include <QSurfaceFormat>
#include <qdockwidget.h>
#include <qnamespace.h>

#include "gui/components/Viewport.hpp"
#include "gui/components/ControlPanel.hpp"

MainWindow::MainWindow(
  QWidget *parent
) : QMainWindow(parent), 
    m_simulation_controller(new SimulationController)
{
  // disable vsync globally 
  QSurfaceFormat format;
  format.setSwapInterval(0);
  QSurfaceFormat::setDefaultFormat(format);

  // allocations
  auto* viewport = new Viewport;
  auto* control_panel = new ControlPanel;
  auto* dock = new QDockWidget("Control Panel", this);
  
  // widget setup
  control_panel->setMaximumWidth(400);
  control_panel->setMinimumSize(200, 150);

  dock->setWidget(control_panel);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  // inter-panel communication
  connect(m_simulation_controller, &SimulationController::simulationUpdated, viewport, &Viewport::renderFrame);
  connect(viewport, &Viewport::frameFinished, m_simulation_controller, &SimulationController::updateSimulation);
  connect(control_panel, &ControlPanel::equationsChanged, m_simulation_controller, &SimulationController::updateEquations);

  // shortcuts
  connect(new QShortcut(QKeySequence(Qt::Key_C), this), &QShortcut::activated, 
    this, [=](void){ dock->isVisible() ? dock->hide() : dock->show(); });

  // main window properties
  this->resize(1280, 720);
  this->setMinimumSize(640, 360);
  this->addDockWidget(Qt::LeftDockWidgetArea, dock);
  this->setCentralWidget(QWidget::createWindowContainer(viewport));
}

MainWindow::~MainWindow(void) {
  delete m_simulation_controller;
}