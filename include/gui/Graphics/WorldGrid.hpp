#pragma once 

#include <QVector3D>
#include <QOpenGLShaderProgram>

#include "gui/graphics/Mesh.hpp"
#include "gui/graphics/OpenGLFunctions.hpp"

class WorldGrid : public Plane {
public:

  WorldGrid(void);
  ~WorldGrid(void);
  
  void draw(
    const QMatrix4x4& camera_matrix,
    const QVector3D& camera_position,
    const QVector3D& focus_point_position
  );

private:

  OpenGLFunctions* m_gl = nullptr;
  QOpenGLShaderProgram* m_program = nullptr;

  GLuint m_camera_matrix_uniform = 0;
  GLuint m_camera_position_uniform = 0;
  GLuint m_focus_point_position_uniform = 0;
  
};