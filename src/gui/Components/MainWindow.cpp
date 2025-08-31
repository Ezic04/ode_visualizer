#include "gui/Components/MainWindow.hpp"

#include <stdexcept>

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>


#include "gui/Components/ControlPanel.hpp"
#include "gui/Components/SimulationController.hpp"
#include "gui/Components/Viewport.hpp"


MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  auto viewport = new Viewport;
  auto control_panel = new ControlPanel;
  m_simulation_controller = new SimulationController;

  if (!viewport) { throw std::runtime_error("Failed to allocate the Viewport component"); }
  if (!control_panel) { throw std::runtime_error("Failed to allocate the Control Panel component"); }
  if (!m_simulation_controller) { throw std::runtime_error("Failed to allocate the Simulation Controller component"); }

  connect(m_simulation_controller, &SimulationController::simulationUpdated, viewport, &Viewport::renderFrame);
  connect(viewport, &Viewport::frameFinished, m_simulation_controller, &SimulationController::updateSimulation);
  connect(control_panel, &ControlPanel::equationsChanged, m_simulation_controller,
          &SimulationController::updateEquations);

  auto layout = new QHBoxLayout();
  auto central = new QWidget(this);

  if (!layout) { throw std::runtime_error("Failed to create the Main Window layout"); }
  if (!central) { throw std::runtime_error("Failed to allocate Main Window's central component"); }

  layout->addWidget(control_panel);
  layout->addWidget(QWidget::createWindowContainer(viewport));

  central->setLayout(layout);
  this->setCentralWidget(central);

  this->setMinimumSize(640, 360);
  this->resize(1280, 720);
}

MainWindow::~MainWindow(void) {
  delete m_simulation_controller;
}