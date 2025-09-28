#include "gui/components/MainWindow.hpp"

#include <QWidget>
#include <QMenuBar>
#include <QShortcut>
#include <QDockWidget>
#include <QSurfaceFormat>

#include "gui/components/ControlPanel.hpp"
#include "gui/components/PreferencesPanel.hpp"

MainWindow::MainWindow(
  QWidget *parent
) : QMainWindow(parent),
    m_simulation_manager(&m_viewport)
{
  // allocations
  auto *control_panel = new ControlPanel;
  auto *dock = new QDockWidget("Control Panel", this);

  // widget setup
  control_panel->setMaximumWidth(400);
  control_panel->setMinimumSize(250, 200);

  dock->setWidget(control_panel);
  dock->setAllowedAreas(Qt::LeftDockWidgetArea | Qt::RightDockWidgetArea);

  // inter-panel communication
  connect(&m_viewport, &Viewport::frameFinished, &m_simulation_manager, &SimulationManager::update);
  connect(control_panel, &ControlPanel::equationsChanged, &m_simulation_manager, &SimulationManager::addMotionSystem);
  connect(&m_simulation_manager, &SimulationManager::parserFailed, control_panel, &ControlPanel::onParserFailed);

  // shortcuts
  connect(new QShortcut(QKeySequence(Qt::Key_C), this), &QShortcut::activated, this, [dock](void) {
    dock->isVisible() ? dock->hide() : dock->show();
  });

  // main window properties
  this->setupMenuBar();
  this->resize(1280, 720);
  this->setMinimumSize(640, 360);
  this->addDockWidget(Qt::LeftDockWidgetArea, dock);
  this->setCentralWidget(QWidget::createWindowContainer(&m_viewport));
}

void MainWindow::openPreferences(void) {
  PreferencesPanel* panel = new PreferencesPanel(this);
  panel->exec(); 
}

void MainWindow::setupMenuBar(void) {
  auto* menu_bar = this->menuBar();

  // file menu
  QMenu* file_menu = menu_bar->addMenu("File");
  QAction* preferences_action = file_menu->addAction("Preferences");
  QAction* exit_action = file_menu->addAction("Exit");

  connect(preferences_action, &QAction::triggered, this, &MainWindow::openPreferences);
  connect(exit_action, &QAction::triggered, &QCoreApplication::quit);

  // other menus?
}