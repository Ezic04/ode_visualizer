#pragma once

#include <QOpenGLShaderProgram>

#include "gui/graphics/Camera.hpp"

class Particle;

class ParticleShader : protected QOpenGLShaderProgram {
public:

  ParticleShader(void);

  inline void bind(void) { QOpenGLShaderProgram::bind(); }
  inline void release(void) { QOpenGLShaderProgram::release(); }

  void updateCameraParams(const Camera& camera);
  void updateParticleParams(const Particle& particle);

private:

  GLuint m_object_color = 0;
  GLuint m_camera_matrix_uniform = 0;
  GLuint m_camera_position_uniform = 0;

};