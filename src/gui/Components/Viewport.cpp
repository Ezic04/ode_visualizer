#include "gui/components/Viewport.hpp"

#include <GL/gl.h>
#include <array>
#include <stdexcept>
#include <vector>

#include <QVector3D>

/* DELETE THIS */

std::vector<float> vertices = {-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};
std::vector<unsigned int> indices = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};
std::vector<std::array<float, 3>> instances = {};

/* DELETE THIS */

static const QVector3D k_background_color(22 / 255.0f, 22 / 255.0f, 22 / 255.0f);

Viewport::Viewport(QWindow *parent) : QOpenGLWindow(QOpenGLWindow::UpdateBehavior::NoPartialUpdate, parent) {
  // QSurfaceFormat format;
  // format.setSamples(8);
  // this->setFormat(format);
}

Viewport::~Viewport(void) {
  delete (m_program);
}

void Viewport::initializeGL(void) {
  if (!this->initializeOpenGLFunctions()) {
    throw std::runtime_error("Failed to initialize viewport's OpenGL context.");
  }

  m_mesh.initializeGL(vertices, indices, instances);

  std::string shader_path = SHADER_PATH;
  std::string vert_path = shader_path + "/shader.vert";
  std::string frag_path = shader_path + "/shader.frag";

  m_program = new QOpenGLShaderProgram;
  m_program->addShaderFromSourceFile(QOpenGLShader::Vertex, vert_path.c_str());
  m_program->addShaderFromSourceFile(QOpenGLShader::Fragment, frag_path.c_str());
  m_program->link();
  m_program->bind();

  m_model_uniform = m_program->uniformLocation("model_matrix");
  m_camera_uniform = m_program->uniformLocation("camera_matrix");

  glEnable(GL_DEPTH_TEST);
}

void Viewport::resizeGL(int w, int h) {}

void Viewport::paintGL(void) {
  QVector4D vieport_size = getVieportSize();
  glViewport(GLint(vieport_size.x()), GLint(vieport_size.y()), GLint(vieport_size.z()), GLint(vieport_size.w()));

  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  glClearColor(k_background_color.x(), k_background_color.y(), k_background_color.z(), 1.0f);

  m_program->bind();
  glBindVertexArray(m_mesh.getVAO());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getIBO());

  m_program->setUniformValue(m_model_uniform, QMatrix4x4());
  m_program->setUniformValue(m_camera_uniform, m_camera.getCameraMatrix());
  glDrawElementsInstanced(GL_TRIANGLES, m_mesh.getIndexCount(), GL_UNSIGNED_INT, 0, m_mesh.getInstanceCount());

  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
  m_program->release();

  emit frameFinished();
}

void Viewport::mousePressEvent(QMouseEvent *event) {
  Qt::MouseButtons button_flags = event->buttons();

  if (button_flags & Qt::MiddleButton || button_flags & Qt::RightButton) { m_last_mouse_position = event->pos(); }
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
  m_mesh.updateInstances(positions);
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