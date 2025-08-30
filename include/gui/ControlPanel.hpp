#pragma once

#include <QFrame>
#include <QWidget>
#include <QTextEdit>
#include <QPushButton>

#include <QMouseEvent>

#include <QPropertyAnimation>

class ControlPanel : public QFrame {
  Q_OBJECT
public:

  ControlPanel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~ControlPanel(void);

  virtual void mousePressEvent(QMouseEvent* event);

signals:

  void equationsChanged(const std::string& equation);

private slots:

  void onSubmit(void);

private:

  void hide(void);
  void show(void);

  QTextEdit* m_textbox = nullptr;
  QPushButton* m_submit_button = nullptr;
  QPropertyAnimation* m_animation = nullptr;

  bool m_hidden = false;

};