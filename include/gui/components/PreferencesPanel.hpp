#pragma once

#include <QDialog>

class PreferencesPanel : public QDialog {
  Q_OBJECT
public:

  PreferencesPanel(QWidget* parent = nullptr);

signals:

  void changeWorldGridCellSize(float cell_size);
  void changeWorldGridFadeStart(float fade_start);
  void changeWorldGridFadeEnd(float fade_end);

};