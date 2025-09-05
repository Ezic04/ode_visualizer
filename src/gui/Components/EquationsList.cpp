#include "gui/components/EquationsList.hpp"

#include <QSize>
#include <QScrollBar>
#include <QHBoxLayout>
#include <QVBoxLayout>
#include <QPushButton>
#include <QResizeEvent>
#include <QListWidgetItem>

EquationsList::EquationsList(
  QWidget* parent
) : QWidget(parent),
    m_list(new QListWidget(this))
{
  auto* add_btn = new QPushButton("+", this);
  auto* rem_btn = new QPushButton("-", this);

  add_btn->setFixedSize(40, 40);
  rem_btn->setFixedSize(40, 40);

  m_list->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);

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

EquationsList::~EquationsList(void) {
  delete m_list;
}

void EquationsList::addEquation(void) {
  auto* content = new EquationTextBox;
  content->resize(m_list->viewport()->size());

  auto* new_item = new QListWidgetItem;
  new_item->setSizeHint(content->sizeHint());
  connect(content, &EquationTextBox::resized,
    [=](const QSize& new_size){ new_item->setSizeHint(content->sizeHint()); });

  m_list->addItem(new_item);
  m_list->setItemWidget(new_item, content);

  connect(this, &EquationsList::resized,
    content, &EquationTextBox::onParentResize);
}

void EquationsList::removeEquation(void) {
  delete m_list->takeItem(m_list->currentRow());
}

void EquationsList::resizeEvent(QResizeEvent* event) {
  QWidget::resizeEvent(event);
  emit resized(m_list->viewport()->size());
}

/************/
/* TEXT BOX */
/************/

EquationTextBox::EquationTextBox(
  QWidget* parent
) : QTextEdit("x' = 0", parent)
{
  this->setLineWrapMode(QTextEdit::NoWrap);
  this->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
  this->setHorizontalScrollBarPolicy(Qt::ScrollBarAsNeeded);
  connect(this, &EquationTextBox::textChanged, 
    this, &EquationTextBox::onTextChanged);
}

QSize EquationTextBox::sizeHint(void) const {
  const QSize document_size = this->document()->size().toSize();
  return {
    this->width(),
    document_size.width() > this->width() ? (
      document_size.height() + this->horizontalScrollBar()->height()
    ) : (document_size.height())
  };
}

void EquationTextBox::resizeEvent(QResizeEvent* event) {
  QTextEdit::resizeEvent(event);
  this->updateGeometry();
  emit resized({ this->width(), this->height() });
}

void EquationTextBox::onTextChanged(void) {
  const QSize document_size = this->document()->size().toSize();
  if (document_size.height() == this->height()) { return; }
  this->resize({ 
    this->width(), 
    document_size.width() > this->width() ?
      document_size.height() + this->horizontalScrollBar()->height()
      : document_size.height()
  });
}

void EquationTextBox::onParentResize(const QSize& size) {
  if (size.width() == this->width()) { return; }
  this->resize({ size.width(), this->height() });
}