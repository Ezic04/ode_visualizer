#include "gui/graphics/Particle.hpp"

Particle::Particle(
  Mesh&& geometry
) : Mesh(std::move(geometry)),
    m_gl(OpenGLFunctions::getInstance())
{
  std::string shader_path = SHADER_PATH;
  std::string vert_path = shader_path + "/particle/particle.vert";
  std::string frag_path = shader_path + "/particle/particle.frag";

  m_program = new QOpenGLShaderProgram;
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_path.c_str());
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());
  m_program->link();
  m_program->bind();

  m_camera_uniform = m_program->uniformLocation("camera_matrix");
}

void Particle::draw(const QMatrix4x4& camera_matrix) {
  m_program->bind();
  m_gl->glBindVertexArray(m_VAO);
  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

  m_program->setUniformValue(m_camera_uniform, camera_matrix);
  
  m_gl->glDrawElementsInstanced(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0, m_instance_count);

  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_gl->glBindVertexArray(0);
  m_program->release();
}