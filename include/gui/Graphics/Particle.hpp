#pragma once

#include <QMatrix4x4>
#include <QOpenGLShaderProgram>

#include "gui/graphics/Mesh.hpp"
#include "gui/graphics/OpenGLFunctions.hpp"

class Particle : public Mesh {
public:

  Particle(Mesh&& geometry);

  void draw(const QMatrix4x4& camera_matrix);
  
private:

  QOpenGLShaderProgram* m_program = nullptr;
  OpenGLFunctions* m_gl = nullptr;

  GLint m_camera_uniform = 0;

};