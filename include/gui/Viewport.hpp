#pragma once

#include <QOpenGLWindow>
#include <QOpenGLFunctions_4_5_Core>
#include <QOpenGLShaderProgram>
#include <QOpenGLBuffer>

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

  GLint m_matrixUniform = 0;
  QOpenGLBuffer m_vbo;
  QOpenGLShaderProgram *m_program = nullptr;
  int m_frame = 0;

};