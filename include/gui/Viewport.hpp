#pragma once

#include <array>
#include <qvectornd.h>
#include <vector>

#include <QMouseEvent>
#include <QWheelEvent>

#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLWindow>

#include "backend/utility.hpp"
#include "gui/Camera.hpp"
#include "gui/Mesh.hpp"

class Viewport : public QOpenGLWindow, protected QOpenGLFunctions_4_5_Core {
  Q_OBJECT
public:
  Viewport(QWindow *parent = nullptr);
  ~Viewport(void);

protected:
  virtual void initializeGL(void) override;
  virtual void resizeGL(int w, int h) override;
  virtual void paintGL(void) override;

  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void wheelEvent(QWheelEvent *event) override;

public slots:

  void renderFrame(const std::vector<std::array<FloatType, 3>> &positions);

signals:

  void frameFinished(void);

private:
  void updateGLViewport(void);
  QVector4D getVieportSize(void);

  QOpenGLShaderProgram *m_program = nullptr;
  Camera m_camera;
  Mesh m_mesh;
  GLint m_MVP_uniform;
  QVector3D m_position;

  QPoint m_last_mouse_position;
};