#include "gui/Mesh.hpp"

Mesh::Mesh(Mesh&& other) {
  m_VAO = other.m_VAO;
  m_IBO = other.m_IBO;
  m_VBO = other.m_VBO;

  other.m_VAO = 0;
  other.m_IBO = 0;
  other.m_VBO = 0;  
}

Mesh::~Mesh(void) {
  if (m_VAO != 0) { glDeleteVertexArrays(1, &m_VAO); }
  if (m_IBO != 0) { glDeleteBuffers(1, &m_IBO); }
  if (m_VBO != 0) { glDeleteBuffers(1, &m_VBO); }
}

bool Mesh::initializeGL(
  const std::vector<float>& vertices,
  const std::vector<unsigned int>& indices 
) {
  if (!this->initializeOpenGLFunctions()) { return false; } 

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  glGenBuffers(1, &m_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(
    GL_ELEMENT_ARRAY_BUFFER, 
    sizeof(unsigned int) * indices.size(), 
    indices.data(), 
    GL_STATIC_DRAW
  );

  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(
    GL_ARRAY_BUFFER, 
    sizeof(float) * vertices.size(), 
    vertices.data(), 
    GL_STATIC_DRAW
  );

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);

  m_index_count = indices.size();
  m_vertex_count = vertices.size();

  return true;
}