#pragma once

#include <QMainWindow>
#include <qobjectdefs.h>

class MainWindow : public QMainWindow {
  Q_OBJECT

public:

  MainWindow(QWidget* parent = nullptr);
  ~MainWindow(void);

};