#include "gui/Viewport.hpp"
#include "gui/Camera.hpp"

#include <qmatrix4x4.h>
#include <qwindowdefs.h>
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
  m_camera.screen_width = width();
  m_camera.screen_height = height();
  m_camera.position = {0.0f, 0.0f, -4.0f};
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
  m_camera.screen_width = w;
  m_camera.screen_height = h;
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
  QMatrix4x4 MVP_matrix = getCameraMatrix(m_camera) * model;

  m_program->setUniformValue(m_MVP_uniform, MVP_matrix);

  glBindVertexArray(m_mesh.getVAO());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getIBO());
  glDrawElements(GL_TRIANGLES, m_mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);

  m_program->release();

  ++frame_count;

  requestUpdate();
}