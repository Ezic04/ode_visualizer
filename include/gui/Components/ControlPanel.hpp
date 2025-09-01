#pragma once

#include <QFrame>
#include <QPushButton>
#include <QTextEdit>
#include <QWidget>

#include <QMouseEvent>

class ControlPanel : public QFrame {
  Q_OBJECT
public:
  ControlPanel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~ControlPanel(void);

signals:

  void equationsChanged(const std::string &equation);

private slots:

  void onSubmit(void);

private:

  QTextEdit *m_textbox = nullptr;
  QPushButton *m_submit_button = nullptr;
  
};