#include "gui/graphics/WorldGrid.hpp"

#include <string>

WorldGrid::WorldGrid(
    void
) : Mesh(Mesh::Plane(100.0f, 100.0f, {{0.0f, 0.0f, 0.0f}})),
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
 
  m_camera_matrix_uniform = m_program->uniformLocation("camera_matrix");
  m_camera_position_uniform = m_program->uniformLocation("camera_position");
  m_focus_point_position_uniform = m_program->uniformLocation("focus_point_position");

  m_program->release();
}

WorldGrid::~WorldGrid(void) {
  delete m_program;
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
  m_program->setUniformValue(m_focus_point_position_uniform, focus_point_position);

  m_gl->glDepthMask(GL_FALSE);
  m_gl->glDrawElements(GL_TRIANGLES, m_index_count, GL_UNSIGNED_INT, nullptr);
  m_gl->glDepthMask(GL_TRUE);

  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_gl->glBindVertexArray(0);
  m_program->release();
}