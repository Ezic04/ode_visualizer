#include "graphics/Mesh.hpp"

#include <vector>
#include <cassert>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

using namespace graphics;

Mesh::Mesh(
  const std::vector<float>& vertices, 
  const std::vector<unsigned int>& indices,
  Program& program
) : m_VAO(0),
    m_VBO(0),
    m_IBO(0),
    m_transforms(new glm::vec3[k_transform_count]),
    m_model_matrix(new glm::mat4(1.0f)),
    m_index_count(indices.size()),
    m_program(&program)
{
  glm::vec3* transforms = static_cast<glm::vec3*>(m_transforms);
  transforms[ROTATION] = glm::vec3(0.0f, 0.0f, 0.0f);
  transforms[POSITION] = glm::vec3(0.0f, 0.0f, 0.0f);
  transforms[SCALE] = glm::vec3(1.0f, 1.0f, 1.0f);

  glGenVertexArrays(1, &m_VAO);
  glBindVertexArray(m_VAO);

  glGenBuffers(1, &m_IBO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * m_index_count, &indices[0], GL_STATIC_DRAW);

  glGenBuffers(1, &m_VBO);
  glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
  glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), &vertices[0], GL_STATIC_DRAW);

  glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);
  glEnableVertexAttribArray(0);

  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);

  glBindVertexArray(0);
}

Mesh::Mesh(
  const std::string& filepath,
  Program& program
) {
  //load_file
  //Mesh::Mesh(vertices, indices);
}

Mesh::~Mesh(void) {
  if (m_VAO != 0) { glDeleteVertexArrays(1, &m_VAO); }
  if (m_VBO != 0) { glDeleteBuffers(1, &m_VBO); }
  if (m_IBO != 0) { glDeleteBuffers(1, &m_IBO); }
  delete(static_cast<glm::mat4*>(m_model_matrix));
}

void Mesh::scale(const Vec3& s) {
  glm::vec3& current_scale = static_cast<glm::vec3*>(m_transforms)[SCALE];
  current_scale = glm::vec3(current_scale.x * s.x, current_scale.y * s.y, current_scale.z * s.z);
  this->calculateModelMatrix();
}

void Mesh::translate(const Vec3& t) {
  static_cast<glm::vec3*>(m_transforms)[POSITION] += glm::vec3(t.x, t.y, t.z);
  this->calculateModelMatrix();
}

void Mesh::rotate(const Vec3& r) {
  static_cast<glm::vec3*>(m_transforms)[ROTATION] += glm::vec3(r.x, r.y, r.z);
  this->calculateModelMatrix();
}

void Mesh::setScale(const Vec3& s) {
  static_cast<glm::vec3*>(m_transforms)[SCALE] = glm::vec3(s.x, s.y, s.z);
  this->calculateModelMatrix();
}

void Mesh::setTranslation(const Vec3& t) {
  static_cast<glm::vec3*>(m_transforms)[POSITION] = glm::vec3(t.x, t.y, t.z);
  this->calculateModelMatrix();
}

void Mesh::setRotation(const Vec3& r) {
  static_cast<glm::vec3*>(m_transforms)[ROTATION] = glm::vec3(r.x, r.y, r.z);
  this->calculateModelMatrix();
}

Vec3 Mesh::getScale(void) const {
  const glm::vec3& current_scale = static_cast<glm::vec3*>(m_transforms)[SCALE];
  return Vec3(current_scale.x, current_scale.y, current_scale.z);
}

Vec3 Mesh::getTranslation(void) const {
  const glm::vec3& current_translation = static_cast<glm::vec3*>(m_transforms)[POSITION];
  return Vec3(current_translation.x, current_translation.y, current_translation.z);
}

Vec3 Mesh::getRotation(void) const {
  const glm::vec3& current_rotation = static_cast<glm::vec3*>(m_transforms)[ROTATION];
  return Vec3(current_rotation.x, current_rotation.y, current_rotation.z);
}

void Mesh::calculateModelMatrix(void) {
  const glm::vec3& position = static_cast<glm::vec3*>(m_transforms)[POSITION];
  const glm::vec3& rotation = static_cast<glm::vec3*>(m_transforms)[ROTATION];
  const glm::vec3& scale    = static_cast<glm::vec3*>(m_transforms)[SCALE];

  glm::mat4 model_matrix(1.0f);
  model_matrix = glm::translate(model_matrix, position);
  model_matrix = glm::rotate(model_matrix, glm::radians(rotation.x) ,glm::vec3(1.0f, 0.0f, 0.0f));
  model_matrix = glm::rotate(model_matrix, glm::radians(rotation.y) ,glm::vec3(0.0f, 1.0f, 0.0f));
  model_matrix = glm::rotate(model_matrix, glm::radians(rotation.z) ,glm::vec3(0.0f, 0.0f, 1.0f));
  model_matrix = glm::scale(model_matrix, scale);

  *static_cast<glm::mat4*>(m_model_matrix) = model_matrix;
}