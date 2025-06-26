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
    m_index_count(0),
    m_program(&program)
{
  m_index_count = indices.size();

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
) : m_VAO(0),
    m_VBO(0),
    m_IBO(0),
    m_index_count(0),
    m_program(&program)
{
  //load_file
  //Mesh::Mesh(vertices, indices);
}

Mesh::~Mesh(void) {
  this->clear();
}

void Mesh::render(void) {

  assert(m_index_count != 0);

    //delete this from here
    glm::mat4 projection = glm::perspective(45.0f, 800 / (float)600, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
      glm::vec3(4,3,3),
      glm::vec3(0,0,0),
      glm::vec3(0,1,0)
    );
    glm::mat4 model = glm::mat4(1.0f);
    model = glm::translate(model, glm::vec3(0.0f, 0.0f, 1.0f)); 

  m_program->bind();

  glUniformMatrix4fv(m_program->getUniformModelID(), 1, GL_FALSE, glm::value_ptr(model));
  glUniformMatrix4fv(m_program->getUniformProjectionID(), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(m_program->getUniformViewID(), 1, GL_FALSE, glm::value_ptr(view));

  glBindVertexArray(m_VAO);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  m_program->unbind();
}

void Mesh::clear(void) {
  if (m_VAO != 0) { glDeleteVertexArrays(1, &m_VAO); }
  if (m_VBO != 0) { glDeleteBuffers(1, &m_VBO); }
  if (m_IBO != 0) { glDeleteBuffers(1, &m_IBO); }
  m_VAO = 0; m_VBO = 0; m_IBO = 0; m_index_count = 0;
}