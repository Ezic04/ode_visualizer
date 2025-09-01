#include "gui/Components/MainWindow.hpp"

#include <QWidget>
#include <QShortcut>
#include <QDockWidget>
#include <QSurfaceFormat>

#include "gui/Components/Viewport.hpp"
#include "gui/Components/ControlPanel.hpp"

MainWindow::MainWindow(
  QWidget *parent
) : QMainWindow(parent), 
    m_simulation_controller(new SimulationController)
{
  // disable vsync globally 
  QSurfaceFormat format;
  format.setSwapInterval(0);
  QSurfaceFormat::setDefaultFormat(format);

  auto* viewport = new Viewport;
  auto* control_panel = new ControlPanel;
  auto* dockable_container = new QDockWidget("Control Panel", this);

  // widget setup
  dockable_container->setWidget(control_panel);
  dockable_container->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  // inter-panel communication
  connect(m_simulation_controller, &SimulationController::simulationUpdated, viewport, &Viewport::renderFrame);
  connect(viewport, &Viewport::frameFinished, m_simulation_controller, &SimulationController::updateSimulation);
  connect(control_panel, &ControlPanel::equationsChanged, m_simulation_controller, &SimulationController::updateEquations);

  // shortcuts
  connect(new QShortcut(QKeySequence(Qt::Key_C), this), &QShortcut::activated, this, [=](){
    if (!dockable_container->isVisible()) { dockable_container->show(); } 
    else { dockable_container->hide(); }
  });

  // main window properties
  this->resize(1280, 720);
  this->setMinimumSize(640, 360);
  this->addDockWidget(Qt::LeftDockWidgetArea, dockable_container);
  this->setCentralWidget(QWidget::createWindowContainer(viewport));
}

MainWindow::~MainWindow(void) {}