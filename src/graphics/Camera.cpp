#include "graphics/Camera.hpp"

#include <cmath>

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
  this->setRotation(params.rotation);
  this->updateViewMatrix();
  this->updateProjectionMatrix();
  this->updateCameraMatrix();
}

Camera::~Camera(void) {
  delete(static_cast<glm::mat4*>(m_matrices));
}

void Camera::setTranslation(const Vec3& t) {
  m_params.position = t;
  this->updateViewMatrix();
  this->updateCameraMatrix(); 
}

void Camera::setRotation(const Vec3& r) {
  m_params.rotation = r;

  if(m_params.rotation.x > m_params.max_pitch) {
    m_params.rotation.x = m_params.max_pitch;
  } else if (m_params.rotation.x < m_params.min_pitch) {
    m_params.rotation.x = m_params.min_pitch;
  }

  if(m_params.rotation.z > m_params.max_roll) {
    m_params.rotation.z = m_params.max_roll;
  } else if (m_params.rotation.z < m_params.min_roll) {
    m_params.rotation.z = m_params.min_roll;
  }

  this->updateViewMatrix();
  this->updateCameraMatrix(); 
}

void Camera::moveLongitudinal(float distance) {
  const Vec3& front = m_vectors[FRONT];
  Vec3 normalized = Vec3::normalize(Vec3(front.x, 0.0f, front.z)); // squash along the Y axis
  this->translate(Vec3(normalized.x, normalized.y, normalized.z) * distance);
}

void Camera::moveLateral(float distance) {
  this->translate(m_vectors[RIGHT] * distance);
}

void Camera::moveVertical(float distance) {
  Vec3 up(k_world_up.x, k_world_up.y, k_world_up.z);
  this->translate(up * distance);
}


void Camera::tiltPitch(float tilt) {
  float test_val = m_params.rotation.x + tilt;
  if (
    test_val > m_params.max_pitch || 
    test_val < m_params.min_pitch
  ) { return; }
  this->rotate(Vec3(tilt, 0.0f, 0.0f));
}

void Camera::tiltYaw(float tilt) {
  this->rotate(Vec3(0.0f, tilt, 0.0f));
}

void Camera::tiltRoll(float tilt) {
  float test_val = m_params.rotation.x + tilt;
  if (
    test_val > m_params.max_roll|| 
    test_val < m_params.min_roll
  ) { return; }
  this->rotate(Vec3(0.0f, 0.0f, tilt));
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

void Camera::updateViewMatrix(void) {
  float pitch = glm::radians(m_params.rotation.x);
  float yaw   = glm::radians(m_params.rotation.y);

  glm::vec3 front     = glm::normalize(glm::vec3(
    cosf(yaw) * cosf(pitch),
    sinf(pitch),
    sinf(yaw) * cosf(pitch)
  ));
  glm::vec3 position  = glm::vec3(m_params.position.x, m_params.position.y, m_params.position.z); 
  glm::vec3 right     = glm::normalize(glm::cross(front, k_world_up));
  glm::vec3 up        = glm::normalize(glm::cross(right, front));

  m_vectors[FRONT]  = Vec3(front.x, front.y, front.z);
  m_vectors[RIGHT]  = Vec3(right.x, right.y, right.z);

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