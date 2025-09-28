#pragma once

#include <QFrame>

#include "gui/components/EquationsList.hpp"

class ControlPanel : public QFrame {
  Q_OBJECT
public:
  ControlPanel(QWidget *parent = nullptr, Qt::WindowFlags f = Qt::WindowFlags());
  ~ControlPanel(void);

signals:
  void equationsChanged(const std::string &equation);
public slots:
  void onParserFailed(const std::string &message);
private slots:
  void onSubmit(void);

private:
  EquationsList *m_equations_list = nullptr;
};