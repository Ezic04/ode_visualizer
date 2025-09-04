#pragma once

#include <QSize>
#include <QTextEdit>
#include <QListWidget>

class EquationTextBox : public QTextEdit{
  Q_OBJECT
public:

  EquationTextBox(QWidget* parent = nullptr);

  virtual QSize sizeHint(void) const override;

protected:
  virtual void resizeEvent(QResizeEvent* event) override;

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