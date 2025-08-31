#include "gui/Components/Viewport.hpp"

#include <stdexcept>

/* DELETE THIS */
static const char vert_source[] = "#version 330                                   \n"
                                  "layout (location = 0) in vec3 pos;             \n"
                                  "out vec4 vColour;                              \n"
                                  "uniform mat4 MVP;                              \n"
                                  "void main() {                                  \n"
                                  "  gl_Position = MVP * vec4(pos, 1.0);          \n"
                                  "	 vColour = vec4(clamp(pos, 0.0f, 1.0f), 1.0f);\n"
                                  "}                                              \n";

static const char frag_source[] = "#version 330           \n"
                                  "in vec4 vColour;       \n"
                                  "out vec4 colour;       \n"
                                  "void main() {          \n"
                                  "    colour = vColour;  \n"
                                  "}                      \n";

std::vector<float> vertices = {-1.0f, -1.0f, 0.0f, 0.0f, -1.0f, 1.0f, 1.0f, -1.0f, 0.0f, 0.0f, 1.0f, 0.0f};

std::vector<unsigned int> indices = {0, 3, 1, 1, 3, 2, 2, 3, 0, 0, 1, 2};
/* DELETE THIS */

Viewport::Viewport(QWindow *parent) : QOpenGLWindow(QOpenGLWindow::UpdateBehavior::NoPartialUpdate, parent) {

  // init here

}

Viewport::~Viewport(void) {
  delete (m_program);
}

void Viewport::initializeGL(void) {

  if (!this->initializeOpenGLFunctions()) {
    throw std::runtime_error("Failed to initialize viewport's OpenGL context.");
  }

  m_program = new QOpenGLShaderProgram;
  if (!m_program) { 
    throw std::runtime_error("Failed to initialize Viewport's GPU program"); 
  }
  
  m_mesh.initializeGL(vertices, indices);

  m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vert_source);
  m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, frag_source);
  m_program->link();
  m_program->bind();

  m_MVP_uniform = m_program->uniformLocation("MVP");

  glEnable(GL_DEPTH_TEST);
}

void Viewport::resizeGL(int w, int h) {}

void Viewport::paintGL(void) {
  QVector4D vieport_size = getVieportSize();
  glViewport(GLint(vieport_size.x()), GLint(vieport_size.y()), GLint(vieport_size.z()), GLint(vieport_size.w()));
  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT | GL_STENCIL_BUFFER_BIT);

  m_program->bind();

  QMatrix4x4 MVP_matrix = m_camera.getCameraMatrix();

  QMatrix4x4 model_matrix;
  model_matrix.translate(m_position.x(), m_position.y(), m_position.z());
  MVP_matrix *= model_matrix;

  m_program->setUniformValue(m_MVP_uniform, MVP_matrix);

  glBindVertexArray(m_mesh.getVAO());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getIBO());
  glDrawElements(GL_TRIANGLES, m_mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);

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

void Viewport::renderFrame(const std::vector<std::array<FloatType, 3>> &positions) {
  m_position = {float(positions[0][0]), float(positions[0][1]), float(positions[0][2])};
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