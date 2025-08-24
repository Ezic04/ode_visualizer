#include "gui/Camera.hpp"

#include <QtMath>

static const QVector3D k_world_up(0.0f, 1.0f, 0.0f);
static const QVector3D k_world_origin(0.0f, 0.0f, 0.0f);

QMatrix4x4 getCameraMatrix(const Camera& camera) {
  // float pitch = qDegreesToRadians(camera.rotation.x());
  // float yaw = qDegreesToRadians(camera.rotation.z());

  // QVector3D front = QVector3D(cosf(yaw), sinf(pitch), sinf(yaw)).normalized();
  // QVector3D right(QVector3D::crossProduct(front, k_world_up));
  // QVector3D up(QVector3D::crossProduct(right, front));
 
  // QMatrix4x4 view;
  // view.lookAt(camera.position, camera.position + front, up);

  // QMatrix4x4 projection;
  // projection.perspective(
  //   camera.FOV, 
  //   camera.screen_width / (float)camera.screen_height, 
  //   camera.near_clip_plane, 
  //   camera.far_clip_plane
  // );

  QMatrix4x4 view;
  view.lookAt(camera.position, k_world_origin, k_world_up);

  QMatrix4x4 projection;
  projection.perspective(
    camera.FOV, 
    camera.screen_width / (float)camera.screen_height, 
    camera.near_clip_plane,
    camera.far_clip_plane
  );

  return projection * view;
}