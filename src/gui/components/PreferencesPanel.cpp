#include "gui/components/PreferencesPanel.hpp"

#include <QLabel>
#include <QSlider>
#include <QVBoxLayout>
#include <QHBoxLayout>

PreferencesPanel::PreferencesPanel(
  QWidget* parent
) : QDialog(parent)
{
  auto* main_layout = new QVBoxLayout;
  
  this->resize(300, 200);
  this->setWindowTitle("Preferences");
  this->setLayout(main_layout);

  // grid cell size
  auto* label = new QLabel("Grid Size", this);
  auto* slider = new QSlider(Qt::Orientation::Horizontal, this);

  auto* layout = new QHBoxLayout;
  main_layout->addLayout(layout);
  layout->addWidget(label);
  layout->addWidget(slider);

  slider->setMinimum(1);
  slider->setMaximum(10);
  slider->setTickInterval(1);
  slider->setTickPosition(QSlider::TicksBothSides);

  connect(slider, &QSlider::valueChanged, this, &PreferencesPanel::changeWorldGridCellSize);

  // grid fade start
  label = new QLabel("Grid Fade Start", this);
  slider = new QSlider(Qt::Orientation::Horizontal, this);
  
  layout = new QHBoxLayout;
  main_layout->addLayout(layout);
  layout->addWidget(label);
  layout->addWidget(slider);

  slider->setMinimum(1);
  slider->setMaximum(100);
  slider->setTickInterval(10);
  slider->setTickPosition(QSlider::TicksBothSides);

  connect(slider, &QSlider::valueChanged, this, &PreferencesPanel::changeWorldGridFadeStart);

  // grid fade end 
  label = new QLabel("Grid Fade End", this);
  slider = new QSlider(Qt::Orientation::Horizontal, this);
  
  layout = new QHBoxLayout;
  main_layout->addLayout(layout);
  layout->addWidget(label);
  layout->addWidget(slider);

  slider->setMinimum(1);
  slider->setMaximum(100);
  slider->setTickInterval(10);
  slider->setTickPosition(QSlider::TicksBothSides);

  connect(slider, &QSlider::valueChanged, this, &PreferencesPanel::changeWorldGridFadeEnd);

}
