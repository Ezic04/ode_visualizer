#pragma once

#include <vector>

#include <QMouseEvent>
#include <QWheelEvent>

#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>

#include "gui/graphics/Camera.hpp"
#include "gui/graphics/Particle.hpp"
#include "gui/graphics/WorldGrid.hpp"
#include "gui/graphics/OpenGLFunctions.hpp"

class Viewport : public QOpenGLWindow {
  Q_OBJECT
public:
  Viewport(QWindow *parent = nullptr);
  ~Viewport(void);

public slots:

  void renderFrame(const std::vector<std::array<float, 3>> &positions);

signals:

  void frameFinished(void);

private:

  virtual void initializeGL(void) override;
  virtual void paintGL(void) override;

  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

  QVector4D getVieportSize(void);

  QPoint m_last_mouse_position;

  Camera m_camera;
  
  Particle* m_particle = nullptr;
  WorldGrid* m_world_grid = nullptr;

  OpenGLFunctions *m_gl= nullptr;

};