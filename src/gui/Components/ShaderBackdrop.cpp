#include "gui/Components/ShaderBackdrop.hpp"

#include <stdexcept>

#include <QPainterPath>

ShaderBackdrop::ShaderBackdrop(
  QWidget* parent
) : QOpenGLWidget(parent) 
{
}

void ShaderBackdrop::initializeGL(void) {
  if (!this->initializeOpenGLFunctions()) {
    throw std::runtime_error("Failed to initialize ShaderBackrop's OpenGL context. ");
  }

  static const char *vertexShaderSource =
      R"(
      #version 330 core
      layout(location = 0) in vec2 position;
      out vec2 uv;
      void main() {
          uv = (position + 1.0) / 2.0;
          gl_Position = vec4(position, 0.0, 1.0);
      }
  )";

  static const char *fragmentShaderSource =
      R"(
      #version 330 core
      in vec2 uv;
      out vec4 fragColor;
      uniform float time;
      void main() {
          // Example: animated gradient
          fragColor = vec4(uv.x, uv.y, abs(sin(time)), 1.0);
      }
  )";

  m_program = new QOpenGLShaderProgram;
  m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  m_program->link();

  // Full-screen quad
  GLfloat vertices[] = { -1.f, -1.f, 1.f, -1.f, -1.f, 1.f, 1.f, 1.f };
  glGenBuffers(1, &m_vbo);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
}

void ShaderBackdrop::resizeGL(int w, int h) {

}

void ShaderBackdrop::paintGL(void) {
  glClear(GL_COLOR_BUFFER_BIT);

  m_program->bind();
  m_program->setUniformValue("time", float(frameCount++) * 0.001f);

  glEnableVertexAttribArray(0);
  glBindBuffer(GL_ARRAY_BUFFER, m_vbo);
  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 0, nullptr);
  glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
  glDisableVertexAttribArray(0);

  this->update();
}

void ShaderBackdrop::resizeEvent(QResizeEvent* event) {
  QPainterPath path;
  path.addRoundedRect(rect(), 10, 10);
  setMask(QRegion(path.toFillPolygon().toPolygon()));
 
  QOpenGLWidget::resizeEvent(event);
}