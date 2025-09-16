#pragma once 

#include <QVector3D>
#include <QOpenGLShaderProgram>

#include "gui/graphics/Mesh.hpp"
#include "gui/graphics/OpenGLFunctions.hpp"



class WorldGrid : public Plane {
public:

  struct GridParameters {
    GridParameters(
      void
    ) : cell_size(1.0f),
        fade_start_distance(10.0f),
        fade_end_distance(30.0f),
        grid_color({0.29f, 0.29f, 0.29f}),
        x_axis_color({1.0f, 0.0f, 0.0f}),
        z_axis_color({0.0f, 0.0f, 1.0f})
    {}
    
    float cell_size = 1.0f;
    float fade_start_distance;
    float fade_end_distance;
    QVector3D grid_color;
    QVector3D x_axis_color;
    QVector3D z_axis_color;
  };

  WorldGrid(const GridParameters& params = GridParameters());
  ~WorldGrid(void);
  
  void setParameters(const GridParameters& params);

  void setCellSize(float cell_size);
  void setFadeStartDistance(float fade_start_distance);
  void setFadeEndDistance(float fade_end_distance);
  void setGridColor(const QVector3D& grid_color);
  void setXAxisColor(const QVector3D& x_axis_color);
  void setZAxisColor(const QVector3D& z_axis_color);

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
  
  GLuint m_cell_size_uniform = 0;
  GLuint m_fade_start_uniform = 0;
  GLuint m_fade_end_uniform = 0;
  GLuint m_grid_color_uniform = 0;
  GLuint m_x_axis_color_uniform = 0;
  GLuint m_z_axis_color_uniform = 0;

};