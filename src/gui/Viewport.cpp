#include "gui/Viewport.hpp"
#include "gui/Camera.hpp"

#include <qnamespace.h>
#include <qopenglwindow.h>
#include <qvectornd.h>
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

std::vector<float> vertices = {
  -1.0f, -1.0f, 0.0f,
  0.0f, -1.0f, 1.0f,
  1.0f, -1.0f, 0.0f,
  0.0f, 1.0f, 0.0f
};

std::vector<unsigned int> indices = {
  0, 3, 1,
  1, 3, 2,
  2, 3, 0,
  0, 1, 2
};
/* DELETE THIS */

Viewport::Viewport(
  QWindow* parent
) : QOpenGLWindow(
      QOpenGLWindow::UpdateBehavior::NoPartialUpdate,
      parent
    )
{
  m_camera.setScreenWidth(width());
  m_camera.setScreenHeight(height());
}

Viewport::~Viewport(void) {

  // free resources

}

void Viewport::initializeGL(void) {

  // make the program shit the bed
  if (!this->initializeOpenGLFunctions()) { 
    throw std::runtime_error("Failed to initialize viewport's OpenGL context.");
  }

  m_mesh.initializeGL(vertices, indices);

  m_program = new QOpenGLShaderProgram;
  m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vert_source);
  m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, frag_source);
  m_program->link();
  m_program->bind();

  m_MVP_uniform = m_program->uniformLocation("MVP");

  glEnable(GL_DEPTH_TEST);
}

void Viewport::resizeGL(int w, int h) {
  m_camera.setScreenWidth(w);
  m_camera.setScreenHeight(h);
}

static unsigned int frame_count = 0;

void Viewport::paintGL(void) {
  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT 
    | GL_DEPTH_BUFFER_BIT 
    | GL_STENCIL_BUFFER_BIT
  );

  m_program->bind();

  QMatrix4x4 model;
  model.rotate(frame_count, 0.5f, 0.0f, 0.0f);
  QMatrix4x4 MVP_matrix = m_camera.getCameraMatrix() * model;

  m_program->setUniformValue(m_MVP_uniform, MVP_matrix);

  glBindVertexArray(m_mesh.getVAO());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getIBO());
  glDrawElements(GL_TRIANGLES, m_mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);

  m_program->release();

  // ++frame_count;

  requestUpdate();
}

void Viewport::mousePressEvent(QMouseEvent* event) {
  Qt::MouseButtons button_flags = event->buttons();

  if (button_flags & Qt::MiddleButton
    || button_flags & Qt::RightButton
  ) { m_last_mouse_position = event->pos(); }
};

void Viewport::mouseDoubleClickEvent(QMouseEvent* event) {
  if (event->buttons() & Qt::RightButton) {
    m_camera.resetTransform();
  }
}

void Viewport::mouseMoveEvent(QMouseEvent* event) {
  Qt::MouseButtons button_flags = event->buttons();

  if (button_flags & Qt::MiddleButton) {
    QPoint pos_delta = event->pos() - m_last_mouse_position;
    m_last_mouse_position = event->pos();
    m_camera.move(QVector2D(
      pos_delta.x() / 100.0f, 
      pos_delta.y() / 100.0f
    ));
  }

  if (button_flags & Qt::RightButton) {
    QPoint pos_delta = event->pos() - m_last_mouse_position;
    m_last_mouse_position = event->pos();
    m_camera.orbit(QVector2D(
      pos_delta.x() / 10.0f, 
      pos_delta.y() / 10.0f
    ));
  }

}

void Viewport::wheelEvent(QWheelEvent* event) {
  QPoint degrees = event->angleDelta();
  if (!degrees.isNull()) {
    m_camera.zoom(degrees.y() / 100.0f);
  }
}