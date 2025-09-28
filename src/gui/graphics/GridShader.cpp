#include "gui/graphics/GridShader.hpp"

#include "gui/graphics/WorldGrid.hpp"

GridShader::GridShader(void) : QOpenGLShaderProgram() {
  std::string shader_path = SHADER_PATH;
  std::string vert_path = shader_path + "/world_grid/world_grid.vert";
  std::string frag_path = shader_path + "/world_grid/world_grid.frag";

  this->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_path.c_str());
  this->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());
  this->link();
  QOpenGLShaderProgram::bind();
 
  m_camera_matrix_uniform = this->uniformLocation("u_camera_matrix");
  m_camera_position_uniform = this->uniformLocation("u_camera_position");

  m_cell_size_uniform = this->uniformLocation("u_cell_size");
  m_fade_start_uniform = this->uniformLocation("u_fade_start");
  m_fade_end_uniform = this->uniformLocation("u_fade_end");
  m_grid_color_uniform = this->uniformLocation("u_grid_color");
  m_x_axis_color_uniform = this->uniformLocation("u_x_axis_color");
  m_z_axis_color_uniform = this->uniformLocation("u_z_axis_color");

  QOpenGLShaderProgram::release();
}

void GridShader::updateCameraParams(const Camera& camera) {
  this->setUniformValue(m_camera_position_uniform, camera.getPosition());
  this->setUniformValue(m_camera_matrix_uniform, camera.getCameraMatrix());
}

void GridShader::updateGridParams(const WorldGrid& grid) {
  WorldGrid::GridParameters grid_parameters = grid.getParameters();

  this->setUniformValue(m_cell_size_uniform, grid_parameters.cell_size);
  this->setUniformValue(m_fade_start_uniform, grid_parameters.fade_start_distance);
  this->setUniformValue(m_fade_end_uniform, grid_parameters.fade_end_distance);
  this->setUniformValue(m_grid_color_uniform, grid_parameters.grid_color);
  this->setUniformValue(m_x_axis_color_uniform, grid_parameters.x_axis_color);
  this->setUniformValue(m_z_axis_color_uniform, grid_parameters.z_axis_color);
}