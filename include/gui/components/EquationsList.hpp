#pragma once

#include <QSize>
#include <QTextEdit>
#include <QListWidget>

/*****************/
/* EQUATION LIST */
/*****************/

class EquationsList : public QWidget {
  Q_OBJECT
public:

  EquationsList(QWidget* parent = nullptr);
  ~EquationsList(void);

  QString getCurrentEquation(void);

public slots:

  void addEquation(void);
  void removeEquation(void);

signals:
  void resized(const QSize& new_viewport_size);

protected:
  virtual void resizeEvent(QResizeEvent* event) override;

private:
  QListWidget* m_list = nullptr;

};

/************/
/* TEXT BOX */
/************/

class EquationTextBox : public QTextEdit{
  Q_OBJECT
public:

  EquationTextBox(QWidget* parent = nullptr);
  ~EquationTextBox(void) = default;

  virtual QSize sizeHint(void) const override;

public slots:
  void onParentResize(const QSize& new_vieport_size);

signals:
  void resized(const QSize& new_size);

protected:
  virtual void resizeEvent(QResizeEvent* event) override;

private slots:
  void onTextChanged(void);

};