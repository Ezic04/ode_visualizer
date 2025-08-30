#include "gui/MainWindow.hpp"

#include <QHBoxLayout>
#include <QPushButton>
#include <QWidget>

#include "gui/ControlPanel.hpp"
#include "gui/SimulationController.hpp"
#include "gui/Viewport.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), m_simulation_controller(new SimulationController) {
  auto viewport = new Viewport;
  connect(m_simulation_controller, &SimulationController::simulationUpdated, viewport, &Viewport::renderFrame);
  connect(viewport, &Viewport::frameFinished, m_simulation_controller, &SimulationController::updateSimulation);

  auto control_panel = new ControlPanel;
  connect(control_panel, &ControlPanel::equationsChanged, m_simulation_controller,
          &SimulationController::updateEquations);

  auto layout = new QHBoxLayout();
  layout->addWidget(control_panel);
  layout->addWidget(QWidget::createWindowContainer(viewport));

  auto central = new QWidget(this);
  central->setLayout(layout);

  this->setCentralWidget(central);

  this->setMinimumSize(640, 360);
  this->resize(1280, 720);
}

MainWindow::~MainWindow(void) {

  // free resources
}