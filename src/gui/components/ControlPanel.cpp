#include "gui/components/ControlPanel.hpp"

#include <QMessageBox>
#include <QPushButton>
#include <QSizePolicy>
#include <QVBoxLayout>

#include "gui/components/EquationsList.hpp"

ControlPanel::ControlPanel(QWidget *parent, Qt::WindowFlags f) : m_equations_list(new EquationsList(this)) {
  auto *submit_btn = new QPushButton("Submit", this);
  submit_btn->setMinimumWidth(100);
  submit_btn->setMinimumHeight(30);

  connect(submit_btn, &QPushButton::pressed, this, &ControlPanel::onSubmit);

  auto *layout = new QVBoxLayout(this);
  layout->addWidget(m_equations_list);
  layout->addWidget(submit_btn);
  layout->setAlignment(submit_btn, Qt::AlignHCenter);

  this->setLayout(layout);
  this->setObjectName("control-panel");
}

ControlPanel::~ControlPanel(void) {
  delete m_equations_list;
}

void ControlPanel::onSubmit(void) {
  QString active_equation = m_equations_list->getCurrentEquation();
  emit equationsChanged(active_equation.toStdString());
}

void ControlPanel::onParserFailed(const std::string &message) {
  QMessageBox::critical(this, "Parser error", QString::fromStdString("Parser failed: " + message), QMessageBox::Ok);
}
