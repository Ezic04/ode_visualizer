#include "gui/graphics/WorldGrid.hpp"

#include <string>

WorldGrid::WorldGrid(
  const GridParameters& params
) : Plane(100.0f, 100.0f, {{ 0.0f, 0.0f, 0.0f }}),
    m_gl(OpenGLFunctions::getInstance()),
    m_program(new QOpenGLShaderProgram)
{
  std::string shader_path = SHADER_PATH;
  std::string vert_path = shader_path + "/world_grid/world_grid.vert";
  std::string frag_path = shader_path + "/world_grid/world_grid.frag";

  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_path.c_str());
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());
  m_program->link();
  m_program->bind();
 
  m_camera_matrix_uniform = m_program->uniformLocation("u_camera_matrix");
  m_camera_position_uniform = m_program->uniformLocation("u_camera_position");

  m_cell_size_uniform = m_program->uniformLocation("u_cell_size");
  m_fade_start_uniform = m_program->uniformLocation("u_fade_start");
  m_fade_end_uniform = m_program->uniformLocation("u_fade_end");
  m_grid_color_uniform = m_program->uniformLocation("u_grid_color");
  m_x_axis_color_uniform = m_program->uniformLocation("u_x_axis_color");
  m_z_axis_color_uniform = m_program->uniformLocation("u_z_axis_color");

  this->setParameters(params);

  m_program->release();
}

WorldGrid::~WorldGrid(void) {
  delete m_program;
}

void WorldGrid::setParameters(const GridParameters& params) {
  m_program->bind();

  m_program->setUniformValue(m_cell_size_uniform,     params.cell_size);
  m_program->setUniformValue(m_fade_start_uniform,    params.fade_start_distance);
  m_program->setUniformValue(m_fade_end_uniform,      params.fade_end_distance);
  m_program->setUniformValue(m_grid_color_uniform,    params.grid_color);
  m_program->setUniformValue(m_x_axis_color_uniform,  params.x_axis_color);
  m_program->setUniformValue(m_z_axis_color_uniform,  params.z_axis_color);

  m_program->release();
}

void WorldGrid::setCellSize(float cell_size) {
  m_program->bind();
  m_program->setUniformValue(m_cell_size_uniform, cell_size);
  m_program->release();
}

void WorldGrid::setFadeStartDistance(float fade_start_distance) {
  m_program->bind();
  m_program->setUniformValue(m_fade_start_uniform, fade_start_distance);
  m_program->release();
}

void WorldGrid::setFadeEndDistance(float fade_end_distance) {
  m_program->bind();
  m_program->setUniformValue(m_fade_end_uniform, fade_end_distance);
  m_program->release();
}

void WorldGrid::setGridColor(const QVector3D& grid_color) {
  m_program->bind();
  m_program->setUniformValue(m_grid_color_uniform, grid_color);
  m_program->release();
}

void WorldGrid::setXAxisColor(const QVector3D& x_axis_color) {
  m_program->bind();
  m_program->setUniformValue(m_x_axis_color_uniform, x_axis_color);
  m_program->release();
}

void WorldGrid::setZAxisColor(const QVector3D& z_axis_color) {
  m_program->bind();
  m_program->setUniformValue(m_z_axis_color_uniform, z_axis_color);
  m_program->release();
}

void WorldGrid::draw(
  const QMatrix4x4& camera_matrix,
  const QVector3D& camera_position,
  const QVector3D& focus_point_position
) {
  m_program->bind();
  m_gl->glBindVertexArray(m_VAO);
  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);

  m_program->setUniformValue(m_camera_matrix_uniform, camera_matrix);
  m_program->setUniformValue(m_camera_position_uniform, camera_position);

  m_gl->glDepthMask(GL_FALSE);
  m_gl->glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
  m_gl->glDepthMask(GL_TRUE);

  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_gl->glBindVertexArray(0);
  m_program->release();
}