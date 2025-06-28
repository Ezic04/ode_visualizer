#include "graphics/Camera.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/Program.hpp"

using namespace graphics;

Camera::Camera(

) : m_matrices(new glm::mat4[k_matrix_count]) 
{

}

Camera::~Camera(void) {
  delete(static_cast<glm::mat4*>(m_matrices));
}

void Camera::move(float x, float y, float z) {

}

void Camera::rotate(float x, float y, float z) {

}

void Camera::setPosition(float x, float y, float z) {

}

void Camera::setRotation(float x, float y, float z) {

}

void Camera::render(const Mesh& mesh) {

  /* delete this from here */
    glm::mat4 projection = glm::perspective(45.0f, 800 / (float)600, 0.1f, 100.0f);
    glm::mat4 view = glm::lookAt(
      glm::vec3(5,0,0),
      glm::vec3(0,0,0),
      glm::vec3(0,1,0)
    );
  /* delete this from here */

  const Program* const program = mesh.getProgram();
  if (!program->bind()) { return; }

  glUniformMatrix4fv(program->getUniformModelID(), 1, GL_FALSE, glm::value_ptr(*static_cast<const glm::mat4* const>(mesh.getModelMatrix())));
  glUniformMatrix4fv(program->getUniformProjectionID(), 1, GL_FALSE, glm::value_ptr(projection));
  glUniformMatrix4fv(program->getUniformViewID(), 1, GL_FALSE, glm::value_ptr(view));

  glBindVertexArray(mesh.getVAO());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIBO());
  glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  program->unbind();
}

void Camera::render(const std::vector<Mesh>& scene) {

}

void Camera::render(const std::vector<Mesh*>& scene) {

}