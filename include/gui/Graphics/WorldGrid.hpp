#pragma once 

#include <QVector3D>
#include <QOpenGLShaderProgram>

#include "gui/graphics/Mesh.hpp"
#include "gui/graphics/OpenGLFunctions.hpp"

class WorldGrid : public Mesh {
public:
  WorldGrid(void);
  ~WorldGrid(void);
  
  void draw(const QVector3D& camera_position, const QMatrix4x4& camera_matrix);

private:

  OpenGLFunctions* m_gl = nullptr;
  QOpenGLShaderProgram* m_program = nullptr;
  GLuint m_camera_position_uniform = 0;
  GLuint m_camera_matrix_uniform = 0;
  
};