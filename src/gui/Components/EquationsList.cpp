#include "gui/components/EquationsList.hpp"

#include <QLineEdit>
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
  auto* content = new EquationsListItem;

  new_item->setSizeHint(content->sizeHint());
  m_list->addItem(new_item);
  m_list->setItemWidget(new_item, content);
}

void EquationsList::removeEquation(void) {
  delete m_list->takeItem(m_list->currentRow());
}




EquationsListItem::EquationsListItem(
  QWidget* parent
) : QWidget(parent)
{
  auto* layout = new QHBoxLayout(this);
  auto* line_edit = new QLineEdit("x' = x", this);
  layout->addWidget(line_edit);
}