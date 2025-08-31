#include "gui/Graphics/Mesh.hpp"
#include <qopenglext.h>

Mesh::~Mesh(void) {
  if (m_VAO != 0) { glDeleteVertexArrays(1, &m_VAO); }
  if (m_IBO != 0) { glDeleteBuffers(1, &m_IBO); }
  if (m_vertices_VBO != 0) { glDeleteBuffers(1, &m_vertices_VBO); }
  if (m_instances_VBO!= 0) { glDeleteBuffers(1, &m_instances_VBO); }
}

bool Mesh::initializeGL(
  const std::vector<float>& vertices,
  const std::vector<unsigned int>& indices,
  const std::vector<float>& instances
) {
  if (!this->initializeOpenGLFunctions()) { return false; }

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  glGenBuffers(1, &m_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

  glGenBuffers(1, &m_vertices_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_vertices_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  glGenBuffers(1, &m_instances_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_instances_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * instances.size(), instances.data(), GL_DYNAMIC_DRAW);
  
  glEnableVertexAttribArray(1);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
  glVertexAttribDivisor(1, 1);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  m_index_count = indices.size();
  m_vertex_count = vertices.size();
  m_instance_count = instances.size() / 3;

  return true;
}

void Mesh::updateInstances(const std::vector<float>& instances) {
  const unsigned int instance_count = instances.size() / 3;
  glBindBuffer(GL_ARRAY_BUFFER, m_instances_VBO);
  if (instance_count != m_instance_count) {
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * instances.size(), instances.data(), GL_DYNAMIC_DRAW);
    m_instance_count = instance_count; 
  } else {
    glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(float) * instances.size(), instances.data());
  }
}