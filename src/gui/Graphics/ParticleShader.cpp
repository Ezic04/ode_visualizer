#include "gui/graphics/ParticleShader.hpp"

#include "gui/graphics/Particle.hpp"

ParticleShader::ParticleShader(void) : QOpenGLShaderProgram() {
  std::string shader_path = SHADER_PATH;
  std::string vert_path = shader_path + "/particle/particle.vert";
  std::string frag_path = shader_path + "/particle/particle.frag";
  
  this->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_path.c_str());
  this->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());
  this->link();
  QOpenGLShaderProgram::bind();

  m_object_color = this->uniformLocation("u_object_color");
  m_camera_matrix_uniform = this->uniformLocation("u_camera_matrix");
  m_camera_position_uniform = this->uniformLocation("u_camera_position");

  QOpenGLShaderProgram::release();
}

void ParticleShader::updateCameraParams(const Camera& camera) {
  this->setUniformValue(m_camera_position_uniform, camera.getPosition());
  this->setUniformValue(m_camera_matrix_uniform, camera.getCameraMatrix());
}

void ParticleShader::updateParticleParams(const Particle& particle) {
  this->setUniformValue(m_object_color, {1.0f, 1.0f, 1.0f});
}