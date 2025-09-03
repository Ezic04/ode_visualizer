#pragma once

#include <QWidget>
#include <QListWidget>

class EquationsListItem : public QWidget {
  Q_OBJECT
public:
  EquationsListItem(QWidget* parent = nullptr);

private:

};

class EquationsList : public QWidget {
  Q_OBJECT
public:

  EquationsList(QWidget* parent = nullptr);
 
public slots:

  void addEquation(void);
  void removeEquation(void);

private:

  QListWidget* m_list = nullptr;

};