#include "gui/components/PreferencesPanel.hpp"

PreferencesPanel::PreferencesPanel(
  QWidget* parent
) : QDialog(parent)
{
  this->setWindowTitle("Preferences");
  this->resize(300, 200);
}