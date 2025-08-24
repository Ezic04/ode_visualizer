#include "gui/Viewport.hpp"
#include <stdexcept>

/* DELETE THIS */
static const char vert_source[] = "#version 330                                   \n"
                                  "layout (location = 0) in vec3 pos;             \n"
                                  "out vec4 vColour;                              \n"
                                  "void main() {                                  \n"
                                  "  gl_Position = vec4(pos, 1.0);                \n"
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
  // init here
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

}

void Viewport::resizeGL(int w, int h) {

}

void Viewport::paintGL(void) {
  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT 
    | GL_DEPTH_BUFFER_BIT 
    | GL_STENCIL_BUFFER_BIT
  );

  m_program->bind();

  glBindVertexArray(m_mesh.getVAO());
  glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_mesh.getIBO());
  glDrawElements(GL_TRIANGLES, m_mesh.getIndexCount(), GL_UNSIGNED_INT, nullptr);

  m_program->release();

  requestUpdate();
}