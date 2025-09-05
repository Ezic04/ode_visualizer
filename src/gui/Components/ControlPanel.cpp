#include "gui/components/ControlPanel.hpp"

#include <QPushButton>
#include <QVBoxLayout>
#include <qpushbutton.h>

#include "gui/components/EquationsList.hpp"

ControlPanel::ControlPanel(
    QWidget *parent, 
    Qt::WindowFlags f
) : m_equations_list(new EquationsList(this))
{
  auto* submit_btn = new QPushButton("Submit", this);

  connect(submit_btn, &QPushButton::pressed, 
    this, &ControlPanel::onSubmit);

  auto* layout = new QVBoxLayout(this);
  layout->addWidget(m_equations_list);
  layout->addWidget(submit_btn);

  this->setLayout(layout);
  this->setObjectName("control-panel");
}

ControlPanel::~ControlPanel(void) {

}

void ControlPanel::onSubmit(void) {
  QString active_equation = m_equations_list->getCurrentEquation();
  emit equationsChanged(active_equation.toStdString());
}