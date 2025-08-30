#include "gui/MainWindow.hpp"

#include <QWidget>
#include <QPushButton>
#include <QHBoxLayout>

#include "gui/Viewport.hpp"
#include "gui/ControlPanel.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  auto viewport = QWidget::createWindowContainer(new Viewport);
  auto control_panel = new ControlPanel();

  auto layout = new QHBoxLayout();
  layout->addWidget(control_panel);
  layout->addWidget(viewport);

  auto central = new QWidget(this);
  central->setLayout(layout);

  this->setCentralWidget(central);

  this->setMinimumSize(640, 360);
  this->resize(1280, 720);
}

MainWindow::~MainWindow(void) {
  
  // free resources

}