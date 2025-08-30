#include "gui/ControlPanel.hpp"

#include <QString>
#include <QVBoxLayout>

ControlPanel::ControlPanel(
    QWidget *parent, 
    Qt::WindowFlags f
) {
  this->setFixedWidth(400);
  this->setMinimumWidth(0);
  this->setStyleSheet("background-color: #2E3440");

  m_animation = new QPropertyAnimation(this, "maximumWidth");
  m_animation->setDuration(300);
  m_animation->setEasingCurve(QEasingCurve::InOutQuad);

  m_textbox = new QTextEdit(this);
  m_submit_button = new QPushButton("Submit", this);

  connect(m_submit_button, &QPushButton::pressed, this, &ControlPanel::onSubmit);

  auto layout = new QVBoxLayout();
  layout->addWidget(m_textbox);
  layout->addWidget(m_submit_button);

  this->setLayout(layout);
}

ControlPanel::~ControlPanel(void) {
  delete m_textbox;
  delete m_submit_button;
  delete m_animation;
}

void ControlPanel::mousePressEvent(QMouseEvent* event) {
  m_hidden ? this->show() : this->hide();
  m_hidden = !m_hidden;
}

void ControlPanel::hide(void) {
  m_animation->stop();
  m_animation->setStartValue(this->width());
  m_animation->setEndValue(100);
  m_animation->start();
}

void ControlPanel::show(void) {
  m_animation->stop();
  m_animation->setStartValue(this->width());
  m_animation->setEndValue(400);
  m_animation->start();
}

void ControlPanel::onSubmit(void) {
  QString content = m_textbox->toPlainText();
  emit equationsChanged(content.toStdString());
}