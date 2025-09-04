#include "gui/components/EquationsList.hpp"

#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QListWidgetItem>

EquationsList::EquationsList(
  QWidget* parent
) : QWidget(parent),
    m_list(new QListWidget(this))
{
  auto* add_btn = new QPushButton("+", this);
  auto* rem_btn = new QPushButton("-", this);

  m_list->setBaseSize(300, 400);
  m_list->setMinimumSize(150, 200);
  m_list->setMaximumSize(300, 400);
  m_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

  add_btn->setFixedSize(40, 40);
  rem_btn->setFixedSize(40, 40);

  auto* buttons_layout = new QVBoxLayout();
  buttons_layout->addWidget(add_btn);
  buttons_layout->addWidget(rem_btn);

  auto* main_layout = new QHBoxLayout(this);
  main_layout->addWidget(m_list);
  main_layout->addLayout(buttons_layout);

  connect(add_btn, &QPushButton::clicked, 
    this, &EquationsList::addEquation);

  connect(rem_btn, &QPushButton::clicked, 
    this, &EquationsList::removeEquation);
}

void EquationsList::addEquation(void) {
  auto* new_item = new QListWidgetItem;
  auto* content = new EquationTextBox;

  new_item->setSizeHint(content->sizeHint());
  //add list item resizing on input text change,
  //ideally using signals and slots
  m_list->addItem(new_item);
  m_list->setItemWidget(new_item, content);
}

void EquationsList::removeEquation(void) {
  delete m_list->takeItem(m_list->currentRow());
}




EquationTextBox::EquationTextBox(
  QWidget* parent
) : QTextEdit("x' = 0", parent)
{
  this->setLineWrapMode(QTextEdit::NoWrap);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  this->setSizePolicy(QSizePolicy::Preferred, QSizePolicy::Minimum);

  this->setMinimumWidth(100);
  this->setMaximumWidth(250);
}

QSize EquationTextBox::sizeHint(void) const {
  return this->document()->size().toSize();
}

void EquationTextBox::resizeEvent(QResizeEvent* event) {
  this->updateGeometry();
  QTextEdit::resizeEvent(event);
}