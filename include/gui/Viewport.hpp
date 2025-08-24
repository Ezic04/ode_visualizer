#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>

#include "gui/Mesh.hpp"

class Viewport : public QOpenGLWindow, protected QOpenGLFunctions_4_5_Core {
  Q_OBJECT
public:

  Viewport(QWindow* parent = nullptr);
  ~Viewport(void);

protected:

  virtual void initializeGL(void) override;
  virtual void resizeGL(int w, int h) override;
  virtual void paintGL(void) override;

private:

  QOpenGLShaderProgram* m_program = nullptr;
  Mesh m_mesh;
};