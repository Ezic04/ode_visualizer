#include "gui/components/MainWindow.hpp"

#include "gui/components/ControlPanel.hpp"
#include "gui/components/SimulationManager.hpp"
#include "gui/components/Viewport.hpp"

#include <qdockwidget.h>
#include <QDockWidget>
#include <qnamespace.h>
#include <QShortcut>
#include <QSurfaceFormat>
#include <QWidget>

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent) {
  // allocations
  auto *viewport = new Viewport;
  m_simulation_manager = new SimulationManager(viewport);

  auto *control_panel = new ControlPanel;
  auto *dock = new QDockWidget("Control Panel", this);

  // widget setup
  control_panel->setMaximumWidth(400);
  control_panel->setMinimumSize(250, 200);

  dock->setWidget(control_panel);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  // inter-panel communication
  // connect(m_simulation_manager, &SimulationManager::simulationUpdated,
  // viewport, &Viewport::renderFrame);
  connect(viewport, &Viewport::frameFinished, m_simulation_manager, &SimulationManager::update);
  connect(control_panel, &ControlPanel::equationsChanged, m_simulation_manager, &SimulationManager::addMotionSystem);
  connect(m_simulation_manager, &SimulationManager::parserFailed, control_panel, &ControlPanel::onParserFailed);

  // shortcuts
  connect(new QShortcut(QKeySequence(Qt::Key_C), this), &QShortcut::activated, this, [dock](void) {
    dock->isVisible() ? dock->hide() : dock->show();
  });

  // main window properties
  this->resize(1280, 720);
  this->setMinimumSize(640, 360);
  this->addDockWidget(Qt::LeftDockWidgetArea, dock);
  this->setCentralWidget(QWidget::createWindowContainer(viewport));
}

MainWindow::~MainWindow(void) { delete m_simulation_manager; }