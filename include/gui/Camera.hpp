#pragma once

#include <QVector2D>
#include <QVector3D>
#include <QMatrix4x4>
#include <qquaternion.h>
#include <qvectornd.h>

class Camera {
public:

  Camera(void);

  void zoom(const float zoom);
  void move(const QVector2D& offset);
  void orbit(const QVector2D& offset);
  void resetTransform(void);


  inline void setFOV(const float FOV) { m_FOV = FOV; }
  inline void setNearClipDistance(const float distance) { m_near_clip_distance = distance; }
  inline void setFarClipDistance(const float distance) { m_far_clip_distance = distance; }
  inline void setAspectRatio(const float ratio) { m_aspect_ratio = ratio; }


  QMatrix4x4 getCameraMatrix(void) const;

  inline QVector3D getPosition(void) const { return m_position; }
  inline QVector3D getFocusPoint(void) const { return m_focus_point; }

  inline float getFOV(void) const { return m_FOV; }
  inline float getNearClipDistance(void) const { return m_near_clip_distance; }
  inline float getFarClipDistance(void) const { return m_far_clip_distance; }
  inline float getAspectRatio(void) const { return m_aspect_ratio; }

private:

  void recalculateVectors(void);
  void recalculatePosition(void);

  QVector3D m_position;
  QQuaternion m_rotation;

  QVector3D m_front;
  QVector3D m_right;
  QVector3D m_up;

  QVector3D m_focus_point;

  float m_focus_point_distance;
  
  float m_FOV = 45.0f;
  float m_near_clip_distance = 0.1f;
  float m_far_clip_distance = 100.0f;

  float m_aspect_ratio = 16.0f / 9.0f;

};