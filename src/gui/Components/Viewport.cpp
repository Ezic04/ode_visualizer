#include "gui/components/Viewport.hpp"
#include <gl/gl.h>
#include <qopenglext.h>

#include <array>
#include <vector>

#include <QVector3D>
#include "gui/graphics/WorldGrid.hpp"

static const QVector3D k_background_color(22 / 255.0f, 22 / 255.0f, 22 / 255.0f); // maybe change this to a member var

Viewport::Viewport(
  QWindow *parent
) : QOpenGLWindow(QOpenGLWindow::UpdateBehavior::NoPartialUpdate, parent)
{}

Viewport::~Viewport(void) {
  delete m_mesh;
  delete m_program;
  delete m_world_grid;
}

void Viewport::initializeGL(void) {

  //don't initialize any of this from the constructor
  m_gl = OpenGLFunctions::getInstance(); 

  m_world_grid = new WorldGrid;
  m_mesh = new Mesh(Mesh::Sphere(1.0f, 18, {{0.0f, 0.0f, 0.0f}}));

  std::string shader_path = SHADER_PATH;
  std::string vert_path = shader_path + "/shader.vert";
  std::string frag_path = shader_path + "/shader.frag";

  // TODO: move this to mesh
  m_program = new QOpenGLShaderProgram;
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_path.c_str());
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());
  m_program->link();
  m_program->bind();

  m_model_uniform = m_program->uniformLocation("model_matrix");
  m_camera_uniform = m_program->uniformLocation("camera_matrix");


  m_gl->glEnable(GL_DEPTH_TEST);
  m_gl->glEnable(GL_BLEND);
  m_gl->glBlendEquation(GL_FUNC_ADD);
  m_gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  m_program->release();
}

void Viewport::paintGL(void) {
  QVector4D vieport_size = this->getVieportSize();
  m_gl->glViewport(GLint(vieport_size.x()), GLint(vieport_size.y()), GLint(vieport_size.z()), GLint(vieport_size.w()));

  m_gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  m_gl->glClearColor(k_background_color.x(), k_background_color.y(), k_background_color.z(), 1.0f);

  m_program->bind();
  m_gl->glBindVertexArray(m_mesh->getVAO());
  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh->getIBO());

  m_program->setUniformValue(m_model_uniform, QMatrix4x4());
  m_program->setUniformValue(m_camera_uniform, m_camera.getCameraMatrix());

  m_gl->glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
  m_gl->glDrawElementsInstanced(GL_TRIANGLES, m_mesh->getIndexCount(), GL_UNSIGNED_INT, 0, m_mesh->getInstanceCount());

  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_gl->glBindVertexArray(0);
  m_program->release();

  m_world_grid->draw(m_camera.getFocusPoint(), m_camera.getCameraMatrix());
  
  emit frameFinished();
}

void Viewport::mousePressEvent(QMouseEvent *event) {
  Qt::MouseButtons button_flags = event->buttons();

  if (button_flags & Qt::MiddleButton 
    || button_flags & Qt::RightButton
  ) { m_last_mouse_position = event->pos(); }
};

void Viewport::mouseDoubleClickEvent(QMouseEvent *event) {
  if (event->buttons() & Qt::RightButton) { m_camera.resetTransform(); }
}

void Viewport::mouseMoveEvent(QMouseEvent *event) {
  Qt::MouseButtons button_flags = event->buttons();

  if (button_flags & Qt::MiddleButton) {
    QPoint pos_delta = event->pos() - m_last_mouse_position;
    m_last_mouse_position = event->pos();
    m_camera.move(QVector2D(pos_delta.x() / 100.0f, pos_delta.y() / 100.0f));
  }

  if (button_flags & Qt::RightButton) {
    QPoint pos_delta = event->pos() - m_last_mouse_position;
    m_last_mouse_position = event->pos();
    m_camera.orbit(QVector2D(pos_delta.x() / 10.0f, pos_delta.y() / 10.0f));
  }
}

void Viewport::wheelEvent(QWheelEvent *event) {
  QPoint degrees = event->angleDelta();
  if (!degrees.isNull()) { m_camera.zoom(degrees.y() / 100.0f); }
}

void Viewport::renderFrame(const std::vector<std::array<float, 3>> &positions) {
  // m_mesh->updateInstances(positions);
  requestUpdate();
}

QVector4D Viewport::getVieportSize(void) {
  const qreal retinaScale = devicePixelRatio();

  float target_aspect_ratio = m_camera.getAspectRatio();
  float window_aspect_ratio = this->width() / (float)this->height();

  if (window_aspect_ratio > target_aspect_ratio) { // window is wider
    int target_height = this->width() / target_aspect_ratio;
    return QVector4D(0, (this->height() - target_height) / 2.0f, this->width() * retinaScale,
                     target_height * retinaScale);
  } else { // window is taller
    int target_width = this->height() * target_aspect_ratio;
    return QVector4D((this->width() - target_width) / 2.0f, 0, target_width * retinaScale,
                     this->height() * retinaScale);
  }
}