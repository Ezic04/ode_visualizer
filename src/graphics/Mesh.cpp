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
  transforms[TRANSLATION] = glm::vec3(0.0f, 0.0f, 0.0f);
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

void Mesh::scale(float x, float y, float z) {
  glm::mat4 scale_matrix = glm::scale(glm::mat4(1.0f), glm::vec3(x, y, z));
  glm::vec3& scale = static_cast<glm::vec3*>(m_transforms)[SCALE];
  scale = glm::vec3(scale_matrix * glm::vec4(scale, 1.0f));
  this->calculateModelMatrix();
}

void Mesh::translate(float x, float y, float z) {
  static_cast<glm::vec3*>(m_transforms)[TRANSLATION] += glm::vec3(x, y, z);
  this->calculateModelMatrix();
}

void Mesh::rotate(float x, float y, float z) {
  static_cast<glm::vec3*>(m_transforms)[ROTATION] += glm::vec3(x, y, z);
  this->calculateModelMatrix();
}

void Mesh::setScale(float x, float y, float z) {
  static_cast<glm::vec3*>(m_transforms)[SCALE] = glm::vec3(x, y, z);
  this->calculateModelMatrix();
}

void Mesh::setTranslation(float x, float y, float z) {
  static_cast<glm::vec3*>(m_transforms)[TRANSLATION] = glm::vec3(x, y, z);
  this->calculateModelMatrix();
}

void Mesh::setRotation(float x, float y, float z) {
  static_cast<glm::vec3*>(m_transforms)[ROTATION] = glm::vec3(x, y, z);
  this->calculateModelMatrix();
}

void Mesh::render(void) {

  assert(m_index_count != 0);

  /* delete this from here */
    glm::mat4 projection = glm::perspective(45.0f, 800 / (float)600, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
      glm::vec3(5,0,0),
      glm::vec3(0,0,0),
      glm::vec3(0,1,0)
    );
  /* delete this from here */

  if (!m_program->bind()) { return; }

  glUniformMatrix4fv(m_program->getUniformModelID(), 1, GL_FALSE, glm::value_ptr(*static_cast<glm::mat4*>(m_model_matrix)));
  glUniformMatrix4fv(m_program->getUniformProjectionID(), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(m_program->getUniformViewID(), 1, GL_FALSE, glm::value_ptr(view));

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  m_program->unbind();
}

void Mesh::calculateModelMatrix(void) {
  const glm::vec3& translation = static_cast<glm::vec3*>(m_transforms)[TRANSLATION];
  const glm::vec3& rotation    = static_cast<glm::vec3*>(m_transforms)[ROTATION];
  const glm::vec3& scale       = static_cast<glm::vec3*>(m_transforms)[SCALE];

  glm::mat4 model_matrix(1.0f);
  model_matrix = glm::translate(model_matrix, translation);
  model_matrix = glm::rotate(model_matrix, glm::radians(rotation.x) ,glm::vec3(1.0f, 0.0f, 0.0f));
  model_matrix = glm::rotate(model_matrix, glm::radians(rotation.y) ,glm::vec3(0.0f, 1.0f, 0.0f));
  model_matrix = glm::rotate(model_matrix, glm::radians(rotation.z) ,glm::vec3(0.0f, 0.0f, 1.0f));
  model_matrix = glm::scale(model_matrix, scale);

  *static_cast<glm::mat4*>(m_model_matrix) = model_matrix;
}