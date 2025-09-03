#pragma once

#include <QOpenGLWidget>
#include <QOpenGLShaderProgram>
#include <QOpenGLFunctions_4_5_Core>

class ShaderBackdrop : public QOpenGLWidget, protected QOpenGLFunctions_4_5_Core {
  Q_OBJECT
public:

  ShaderBackdrop(QWidget *parent = nullptr);

  virtual void initializeGL(void) override;
  virtual void resizeGL(int w, int h) override;
  virtual void paintGL(void) override;

  virtual void resizeEvent(QResizeEvent* event) override;

protected:

  QOpenGLShaderProgram* m_program = nullptr;
  GLuint m_vbo;

  unsigned int frameCount = 0;
};