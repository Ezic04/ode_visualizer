#include "gui/components/Viewport.hpp"

#include <array>
#include <vector>

#include <QVector3D>
#include <QVector4D>

static const QVector3D k_background_color(22 / 255.0f, 22 / 255.0f, 22 / 255.0f); // maybe change this to a member var

Viewport::Viewport(
  QWindow *parent
) : QOpenGLWindow(QOpenGLWindow::UpdateBehavior::NoPartialUpdate, parent)
{}

Viewport::~Viewport(void) {
  delete m_particle;
  delete m_world_grid;
  delete m_grid_shader;
  delete m_particle_shader;
}

void Viewport::renderFrame(
  const std::vector<std::array<float, 3>> &positions
) {
  m_particle->update(positions);
  requestUpdate();
}

void Viewport::initializeGL(void) {
  m_gl = OpenGLFunctions::getInstance(); 
  m_gl->glEnable(GL_DEPTH_TEST);
  m_gl->glEnable(GL_BLEND);
  m_gl->glBlendEquation(GL_FUNC_ADD);
  m_gl->glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

  // m_particle = new Particle(Sphere(1.0f, 18, {{ 0.0f, 0.0f, 0.0f }}));
  m_particle = new Particle(Cube(1.0f, 1.0f, 1.0f, {{ 0.0f, 0.0f, 0.0f }}));
  m_particle_shader = new ParticleShader;

  m_world_grid = new WorldGrid;
  m_grid_shader = new GridShader;
}

void Viewport::paintGL(void) {
  this->clearViewport();

  this->drawParticles();
  this->drawGrid();

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

void Viewport::clearViewport(void) {
  QVector4D vieport_size = this->getVieportSize();
  m_gl->glViewport(GLint(vieport_size.x()), GLint(vieport_size.y()), GLint(vieport_size.z()), GLint(vieport_size.w()));

  m_gl->glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);
  m_gl->glClearColor(k_background_color.x(), k_background_color.y(), k_background_color.z(), 1.0f); 
}

void Viewport::drawParticles(void) {
  m_particle_shader->bind();

  // ** this should be in an SSBO 
  m_particle_shader->updateCameraParams(m_camera);
  // ** this should be in an SSBO 

  m_particle->draw(m_particle_shader);
  m_particle_shader->release();
}

void Viewport::drawGrid(void) {
  m_grid_shader->bind();

  // ** also should be in an SSBO
  m_grid_shader->updateCameraParams(m_camera);
  // ** also should be in an SSBO
  
  m_world_grid->draw(m_grid_shader);
  m_grid_shader->release();
}

QVector4D Viewport::getVieportSize(void) {
  const qreal retinaScale = devicePixelRatio();

  float target_aspect_ratio = m_camera.getAspectRatio();
  float window_aspect_ratio = this->width() / (float)this->height();

  if (window_aspect_ratio > target_aspect_ratio) { // window is wider
    int target_height = this->width() / target_aspect_ratio;
    return QVector4D(
      0, 
      (this->height() - target_height) / 2.0f, 
      this->width() * retinaScale,
      target_height * retinaScale);
  } else { // window is taller
    int target_width = this->height() * target_aspect_ratio;
    return QVector4D(
      (this->width() - target_width) / 2.0f, 
      0, 
      target_width * retinaScale,
      this->height() * retinaScale);
  }
}