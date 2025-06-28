#include "graphics/Camera.hpp"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "graphics/Program.hpp"

using namespace graphics;

constexpr glm::vec3 k_world_up(0.0f, 1.0f, 0.0f);

Camera::Camera(
  const Camera::Parameters& params 
) : m_matrices(new glm::mat4[k_matrix_count]),
    m_params(params)
{
  this->updateViewMatrix();
  this->updateProjectionMatrix();
  this->updateCameraMatrix();
}

Camera::~Camera(void) {
  delete(static_cast<glm::mat4*>(m_matrices));
}

void Camera::translate(const Vec3& t) {
  m_params.position += t;
  this->updateViewMatrix();
  this->updateCameraMatrix();
}

void Camera::rotate(const Vec3& r) {
  m_params.rotation += r;
  this->updateViewMatrix();
  this->updateCameraMatrix();
}

void Camera::setCameraPrameters(const Camera::Parameters& params) {
  m_params = params;
  this->updateViewMatrix();
  this->updateProjectionMatrix();
  this->updateCameraMatrix();
}

void Camera::render(const Mesh& mesh) {
  const Program* const program = mesh.getProgram();
  if (!program->bind()) { return; }

  glm::mat4 MVP = static_cast<glm::mat4*>(m_matrices)[CAMERA] * *static_cast<const glm::mat4* const>(mesh.getModelMatrix());
  glUniformMatrix4fv(program->getUniformMVPID(), 1, GL_FALSE, glm::value_ptr(MVP));

  glBindVertexArray(mesh.getVAO());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.getIBO());
  glDrawElements(GL_TRIANGLES, mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);

  program->unbind();
}

void Camera::updateViewMatrix(void) {
  float pitch = glm::radians(m_params.rotation.x);
  float yaw   = glm::radians(m_params.rotation.y);

  glm::vec3 position  = glm::vec3(m_params.position.x, m_params.position.y, m_params.position.z);
  glm::vec3 front     = glm::normalize(glm::vec3(cosf(yaw), sinf(pitch), sinf(yaw)));
  glm::vec3 right     = glm::normalize(glm::cross(front, k_world_up));
  glm::vec3 up        = glm::normalize(glm::cross(right, front));

  static_cast<glm::mat4*>(m_matrices)[VIEW] = glm::lookAt(
                                                position,
                                                position + front,
                                                up
                                              );
}

void Camera::updateProjectionMatrix(void) {
  static_cast<glm::mat4*>(m_matrices)[PROJECTION] = glm::perspective(
                                                    m_params.FOV,
                                                    m_params.screen_width / (float)m_params.screen_height,
                                                    m_params.near_clip_plane,
                                                    m_params.far_clip_plane
                                                  ); 
}

void Camera::updateCameraMatrix(void) {
  glm::mat4* matrices = static_cast<glm::mat4*>(m_matrices);
  matrices[CAMERA] = matrices[PROJECTION] * matrices[VIEW];
}