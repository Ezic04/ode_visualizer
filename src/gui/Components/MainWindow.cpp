#include "gui/Components/MainWindow.hpp"

#include <stdexcept>

#include <QWidget>
#include <QHBoxLayout>
#include <QPushButton>
#include <QDockWidget>
#include <QSurfaceFormat>

#include "gui/Components/Viewport.hpp"
#include "gui/Components/ControlPanel.hpp"
#include "gui/Components/SimulationController.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  QSurfaceFormat format;
  format.setSwapInterval(0);
  QSurfaceFormat::setDefaultFormat(format);

  auto viewport = new Viewport;
  auto control_panel = new ControlPanel;
  auto dockable_container = new QDockWidget("Control Panel", this);
  
  m_simulation_controller = new SimulationController;

  if (!viewport) { throw std::runtime_error("Failed to allocate the Viewport component"); }
  if (!control_panel || !dockable_container) { throw std::runtime_error("Failed to allocate the Control Panel component"); }
  if (!m_simulation_controller) { throw std::runtime_error("Failed to allocate the Simulation Controller component"); }

  dockable_container->setWidget(control_panel);
  dockable_container->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  connect(m_simulation_controller, &SimulationController::simulationUpdated, viewport, &Viewport::renderFrame);
  connect(viewport, &Viewport::frameFinished, m_simulation_controller, &SimulationController::updateSimulation);
  connect(control_panel, &ControlPanel::equationsChanged, m_simulation_controller,
          &SimulationController::updateEquations);

  this->setCentralWidget(QWidget::createWindowContainer(viewport));
  this->addDockWidget(Qt::LeftDockWidgetArea, dockable_container);
  this->setMinimumSize(640, 360);
  this->resize(1280, 720);
}

MainWindow::~MainWindow(void) {
  delete m_simulation_controller;
}