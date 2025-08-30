#pragma once

#include <vector>

#include <QMouseEvent>
#include <QWheelEvent>

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>

#include "gui/Mesh.hpp"
#include "gui/Camera.hpp"

class Viewport : public QOpenGLWindow, protected QOpenGLFunctions_4_5_Core {
  Q_OBJECT
public:

  Viewport(QWindow* parent = nullptr);
  ~Viewport(void);

protected:

  virtual void initializeGL(void) override;
  virtual void resizeGL(int w, int h) override;
  virtual void paintGL(void) override;

  virtual void mousePressEvent(QMouseEvent* event) override;
  virtual void mouseDoubleClickEvent(QMouseEvent* event) override;
  virtual void mouseMoveEvent(QMouseEvent* event) override;
  virtual void wheelEvent(QWheelEvent* event) override;

public slots:

  // idk what vector it should be, int as a placeholder
  void onStateUpdate(const std::vector<int>& state);

signals:

  void frameFinished(void);

private:

  void updateGLViewport(void);
  QVector4D getVieportSize(void);

  QOpenGLShaderProgram* m_program = nullptr;
  Camera m_camera;
  Mesh m_mesh;
  GLint m_MVP_uniform;

  QPoint m_last_mouse_position;

};