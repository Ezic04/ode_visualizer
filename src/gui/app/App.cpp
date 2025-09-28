#include "gui/app/App.hpp"

#include <QFile>
#include <QString>
#include <QPalette>
#include <QLatin1String>

App::App(int& argc, char** argv) : QApplication(argc, argv) {
  
  QFile stylesheet_file(STYLESHEET_FILE);
  if (stylesheet_file.open(QFile::ReadOnly)) {
    QString stylesheet = QLatin1String(stylesheet_file.readAll());
    this->setStyleSheet(stylesheet);
  }

  QPalette palette = this->palette();
  palette.setColor(QPalette::Highlight, "#202020");
  this->setPalette(palette);

  m_main_window.show();
}