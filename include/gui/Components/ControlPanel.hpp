#pragma once

#include "gui/components/EquationsList.hpp"
#include <QFrame>

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
  
  EquationsList* m_equations_list = nullptr;

};