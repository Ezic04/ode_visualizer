#pragma once 

#include <QVector3D>

#include "gui/graphics/Mesh.hpp"
#include "gui/graphics/GridShader.hpp"
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
  ~WorldGrid(void) = default;
  
  inline WorldGrid::GridParameters getParameters(void) const { return m_parameters; }

  inline void setParameters(const GridParameters& parameters) { m_parameters = parameters; }

  inline void setCellSize(float cell_size) { m_parameters.cell_size = cell_size; }
  inline void setFadeStartDistance(float fade_start_distance) { m_parameters.fade_start_distance = fade_start_distance; }
  inline void setFadeEndDistance(float fade_end_distance) { m_parameters.fade_end_distance = fade_end_distance; }
  inline void setGridColor(const QVector3D& grid_color) { m_parameters.grid_color = grid_color; }
  inline void setXAxisColor(const QVector3D& x_axis_color) { m_parameters.x_axis_color = x_axis_color; }
  inline void setZAxisColor(const QVector3D& z_axis_color) { m_parameters.z_axis_color = z_axis_color; }

  void draw(GridShader* shader) const;

private:

  OpenGLFunctions* m_gl = nullptr;
  GridParameters m_parameters;

};