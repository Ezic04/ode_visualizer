#pragma once

#include <QVector3D>
#include <QMatrix4x4>

struct Camera {
  QVector3D position = QVector3D(0.0f, 0.0f, 0.0f);
  QVector3D rotation = QVector3D(0.0f, 0.0f, 0.0f);
  float FOV = 45.0f;
  float near_clip_plane = 0.1f;
  float far_clip_plane = 100.0f;
  uint16_t screen_width = 800;
  uint16_t screen_height = 600;
};

QMatrix4x4 getCameraMatrix(const Camera& camera);