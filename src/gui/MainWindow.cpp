#include "gui/MainWindow.hpp"

#include <QWidget>
#include <QPushButton>
#include <QVBoxLayout>

#include "gui/Viewport.hpp"

MainWindow::MainWindow(QWidget* parent) : QMainWindow(parent) {
  auto viewport = QWidget::createWindowContainer(new Viewport);

  auto layout = new QVBoxLayout();
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