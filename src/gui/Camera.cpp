#include "gui/Camera.hpp"

#include <QtMath>
#include <qmatrix4x4.h>
#include <qquaternion.h>
#include <qvectornd.h>

static const QVector3D k_world_up(0.0f, 1.0f, 0.0f);
static const QVector3D k_world_origin(0.0f, 0.0f, 0.0f);

Camera::Camera(void) {
  this->resetTransform();
}

void Camera::zoom(const float zoom_distance) {
  m_focus_point_distance -= zoom_distance;
  this->recalculatePosition();
}

void Camera::move(const QVector2D& offset) {
  m_focus_point -= m_right * offset.x();
  m_focus_point += m_up * offset.y();
  this->recalculatePosition();
}

void Camera::orbit(const QVector2D& offset) {

  QQuaternion yaw = QQuaternion::fromAxisAndAngle(0.0f, -1.0f, 0.0f, offset.x());
  QQuaternion pitch = QQuaternion::fromAxisAndAngle(-1.0f, 0.0f, 0.0f, offset.y());

  m_rotation = yaw * m_rotation * pitch;

  this->recalculateVectors();
  this->recalculatePosition();
}

void Camera::resetTransform(void) {
  m_focus_point = QVector3D(0.0f, 0.0f, 0.0f);
  m_focus_point_distance = 4.0f;
  m_rotation = QQuaternion::fromEulerAngles(0.0f, 0.0f, 0.0f);
  this->recalculateVectors();
  this->recalculatePosition();
}

QMatrix4x4 Camera::getCameraMatrix(void) const {
  QMatrix4x4 view;
  view.lookAt(m_position, m_position + m_front, m_up);

  QMatrix4x4 projection;
  projection.perspective(
    m_FOV, 
    m_screen_width / (float)m_screen_height, 
    m_near_clip_distance,
    m_far_clip_distance
  );

  return projection * view;
}

void Camera::recalculateVectors(void) {
  m_front = m_rotation.rotatedVector(QVector3D(0.0f, 0.0f, -1.0f));
  m_up = m_rotation.rotatedVector(QVector3D(0.0f, 1.0f, 0.0f));
  m_right = QVector3D::crossProduct(m_front, m_up);
}

void Camera::recalculatePosition(void) {
  m_position = m_focus_point - (m_front * m_focus_point_distance);
}