#include "gui/graphics/WorldGrid.hpp"

WorldGrid::WorldGrid(
  const GridParameters& params
) : Plane(100.0f, 100.0f, {{ 0.0f, 0.0f, 0.0f }}),
    m_gl(OpenGLFunctions::getInstance())
{}

void WorldGrid::draw(GridShader* shader) const {
  shader->updateGridParams(*this);

  m_gl->glBindVertexArray(m_VAO);
  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

  m_gl->glDepthMask(GL_FALSE);
  m_gl->glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
  m_gl->glDepthMask(GL_TRUE);

  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_gl->glBindVertexArray(0);
}