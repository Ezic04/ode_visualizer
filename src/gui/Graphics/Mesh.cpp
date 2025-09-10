#include "gui/graphics/Mesh.hpp"

#include <array>
#include <cstddef>
#include <vector>

Mesh::Mesh(
  const std::vector<float> &vertices, 
  const std::vector<unsigned int> &indices,
  const std::vector<std::array<float, 3>> &instances
) : m_index_count(indices.size()),
    m_vertex_count(vertices.size()),
    m_instance_count(instances.size()),
    m_gl(OpenGLFunctions::getInstance())
{
  m_gl->glGenVertexArrays(1, &m_VAO);
  m_gl->glBindVertexArray(m_VAO);

  m_gl->glGenBuffers(1, &m_IBO);
  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  m_gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);

  m_gl->glGenBuffers(1, &m_vertices_VBO);
  m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_vertices_VBO);
  m_gl->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

  m_gl->glEnableVertexAttribArray(0);
  m_gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);

  m_gl->glGenBuffers(1, &m_instances_VBO);
  m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_instances_VBO);
  m_gl->glBufferData(GL_ARRAY_BUFFER, sizeof(std::array<float, 3>) * instances.size(), instances.data()->data(), GL_DYNAMIC_DRAW);

  m_gl->glEnableVertexAttribArray(1);
  m_gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
  m_gl->glVertexAttribDivisor(1, 1);

  m_gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_gl->glBindVertexArray(0);
}

Mesh::~Mesh(void) {
  if (m_VAO != 0) { m_gl->glDeleteVertexArrays(1, &m_VAO); }
  if (m_IBO != 0) { m_gl->glDeleteBuffers(1, &m_IBO); }
  if (m_vertices_VBO != 0) { m_gl->glDeleteBuffers(1, &m_vertices_VBO); }
  if (m_instances_VBO != 0) { m_gl->glDeleteBuffers(1, &m_instances_VBO); }
}

void Mesh::updateInstances(const std::vector<std::array<float, 3>> &instances) {
  const size_t instance_count = instances.size();
  const size_t data_size = sizeof(std::array<float, 3>) * instance_count;
  const float *const data = instances.data()->data();
  m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_instances_VBO);
  if (instance_count != m_instance_count) {
    m_gl->glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_DYNAMIC_DRAW);
    m_instance_count = instance_count;
  } else {
    m_gl->glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, data);
  }
}

Plane::Plane(
  void
) : Mesh({
    -1.0, -1.0, 0.0,
    -1.0, 1.0, 0.0,
    1.0, 1.0, 0.0,
    1.0, -1.0, 0.0
  }, {
    0, 1, 2,
    0, 2, 3
  }, {}) 
{}

Cube::Cube(
  void
) : Mesh({
    -1.0, -1.0, 1.0,
    -1.0, 1.0, 1.0,
    1.0, 1.0, 1.0,
    1.0, -1.0, 1.0,

    -1.0, -1.0, -1.0,
    -1.0, 1.0, -1.0,
    1.0, 1.0, -1.0,
    1.0, -1.0, -1.0
  },{
    0, 1, 2,
    0, 2, 3,
    3, 2, 6,
    3, 6, 7,
    7, 6, 5,
    7, 5, 4,
    4, 5, 1,
    4, 1, 0,
    0, 3, 7,
    0, 7, 4,
    5, 2, 1,
    5, 6, 2
  }, {{0.0, 0.0, 0.0}})
{}