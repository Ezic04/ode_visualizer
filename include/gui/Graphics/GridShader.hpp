#pragma once 

#include <QopenGLShaderProgram>

#include "gui/graphics/Camera.hpp"

class WorldGrid;

class GridShader : protected QOpenGLShaderProgram {
public:

  GridShader(void);

  inline void bind(void) { QOpenGLShaderProgram::bind(); }
  inline void release(void) { QOpenGLShaderProgram::release(); }

  void updateCameraParams(const Camera& camera);
  void updateGridParams(const WorldGrid& grid);

private:

  GLuint m_camera_matrix_uniform = 0;
  GLuint m_camera_position_uniform = 0;
  
  GLuint m_cell_size_uniform = 0;
  GLuint m_fade_start_uniform = 0;
  GLuint m_fade_end_uniform = 0;
  GLuint m_grid_color_uniform = 0;
  GLuint m_x_axis_color_uniform = 0;
  GLuint m_z_axis_color_uniform = 0;

};