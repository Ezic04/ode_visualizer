#include "gui/Components/ControlPanel.hpp"

#include <QVBoxLayout>
#include <QPainterPath>
#include <qwidget.h>

#include "gui/Components/ShaderBackdrop.hpp"

ControlPanel::ControlPanel(
    QWidget *parent, 
    Qt::WindowFlags f
) : m_textbox(new QTextEdit(this)),
    m_submit_button(new QPushButton("Submit", this))
{

  auto* backdrop = new ShaderBackdrop(this);
  backdrop->setObjectName("control-panel-backdrop");

  auto* layout = new QVBoxLayout(this);
  layout->addWidget(backdrop);
  layout->setContentsMargins(0, 0, 0, 0);

  // layout->addWidget(m_textbox);
  // layout->addWidget(m_submit_button);

  // connect(m_submit_button, &QPushButton::pressed, this, &ControlPanel::onSubmit);
  
  delete m_textbox;
  delete m_submit_button;

  // this->setLayout(layout);
  this->setMinimumWidth(300);
  this->setMaximumWidth(400);
  this->setObjectName("control-panel");
}

ControlPanel::~ControlPanel(void) {
  delete m_textbox;
  delete m_submit_button;
}

void ControlPanel::onSubmit(void) {
  QString content = m_textbox->toPlainText();
  emit equationsChanged(content.toStdString());
}