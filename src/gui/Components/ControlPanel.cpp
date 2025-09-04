#include "gui/components/ControlPanel.hpp"

#include <QVBoxLayout>

#include "gui/components/EquationsList.hpp"

ControlPanel::ControlPanel(
    QWidget *parent, 
    Qt::WindowFlags f
) {

  auto* list = new EquationsList;

  auto* layout = new QVBoxLayout(this);
  layout->addWidget(list);

  this->setLayout(layout);
  this->setObjectName("control-panel");
}

ControlPanel::~ControlPanel(void) {

}

void ControlPanel::onSubmit(void) {
  
}