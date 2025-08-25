#include "gui/MainWindow.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <QWidget>

#include "gui/Viewport.hpp"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent) {
  auto viewport = QWidget::createWindowContainer(new Viewport);
  auto test_btn = new QPushButton("Test Button");

  auto layout = new QVBoxLayout();
  layout->addWidget(viewport);
  layout->addWidget(test_btn);

  auto central = new QWidget(this);
  central->setLayout(layout);

  this->setCentralWidget(central);
  this->resize(800, 600);
}

MainWindow::~MainWindow(void) {

  // free resources
}