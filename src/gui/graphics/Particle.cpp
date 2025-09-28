#include "gui/graphics/Particle.hpp"

Particle::Particle(
  Mesh&& geometry
) : Mesh(std::move(geometry)),
    m_gl(OpenGLFunctions::getInstance())
{}

void Particle::draw(ParticleShader* shader) {
  shader->updateParticleParams(*this);

  m_gl->glBindVertexArray(m_VAO);
  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  
  m_gl->glDrawElementsInstanced(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, 0, m_instance_count);

  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_gl->glBindVertexArray(0);
}