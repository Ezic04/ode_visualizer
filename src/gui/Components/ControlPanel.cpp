#include "gui/Components/ControlPanel.hpp"

#include <stdexcept>

#include <QString>
#include <QVBoxLayout>

ControlPanel::ControlPanel(
    QWidget *parent, 
    Qt::WindowFlags f
) {
  this->setMinimumWidth(300);
  this->setMaximumWidth(400);
  this->setStyleSheet("background-color: #2E3440");

  auto layout = new QVBoxLayout();
  m_textbox = new QTextEdit(this);
  m_submit_button = new QPushButton("Submit", this);

  if (!layout) { throw std::runtime_error("Failed to create Control Panel layout"); }
  if (!m_textbox) { throw std::runtime_error("Failed to create Control Panel textbox"); }
  if (!m_submit_button) { throw std::runtime_error("Failed to create Control Panel submit button"); }

  connect(m_submit_button, &QPushButton::pressed, this, &ControlPanel::onSubmit);
  
  layout->addWidget(m_textbox);
  layout->addWidget(m_submit_button);

  this->setLayout(layout);
}

ControlPanel::~ControlPanel(void) {
  delete m_textbox;
  delete m_submit_button;
}

void ControlPanel::onSubmit(void) {
  QString content = m_textbox->toPlainText();
  emit equationsChanged(content.toStdString());
}