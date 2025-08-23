#include "gui/Viewport.hpp"

#include <QScreen>

/* DELETE THIS */
static const char vertexShaderSource[]= "attribute highp vec4 posAttr;\n"
                                        "attribute lowp vec4 colAttr;\n"
                                        "varying lowp vec4 col;\n"
                                        "uniform highp mat4 matrix;\n"
                                        "void main() {\n"
                                        "   col = colAttr;\n"
                                        "   gl_Position = matrix * posAttr;\n"
                                        "}\n";

static const char fragmentShaderSource[]= "varying lowp vec4 col;\n"
                                          "void main() {\n"
                                          "   gl_FragColor = col;\n"
                                          "}\n";

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
  this->initializeOpenGLFunctions();

  static const GLfloat vertices_colors[] = {+0.0f, +0.707f, 1.0f,  0.0f,    0.0f, -0.5f, -0.500f, 0.0f,
                                            1.0f,  0.0f,    +0.5f, -0.500f, 0.0f, 0.0f,  1.0f};

  m_vbo.create();
  m_vbo.bind();
  m_vbo.allocate(vertices_colors, sizeof(vertices_colors));

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), nullptr);
  glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(GLfloat), reinterpret_cast<void *>(2 * sizeof(GLfloat)));

  m_program = new QOpenGLShaderProgram(this);
  m_program->addShaderFromSourceCode(QOpenGLShader::Vertex, vertexShaderSource);
  m_program->addShaderFromSourceCode(QOpenGLShader::Fragment, fragmentShaderSource);
  m_program->bindAttributeLocation("posAttr", 0);
  m_program->bindAttributeLocation("colAttr", 1);
  m_program->link();
  m_program->bind();

  m_matrixUniform = m_program->uniformLocation("matrix");
  Q_ASSERT(m_matrixUniform != -1);
}

void Viewport::resizeGL(int w, int h) {

}

void Viewport::paintGL(void) {
  const qreal retinaScale = devicePixelRatio();
  glViewport(0, 0, width() * retinaScale, height() * retinaScale);

  glClear(GL_COLOR_BUFFER_BIT);

  m_program->bind();

  QMatrix4x4 matrix;
  matrix.perspective(60.0f, 4.0f / 3.0f, 0.1f, 100.0f);
  matrix.translate(0, 0, -2);
  matrix.rotate(100.0f * m_frame / screen()->refreshRate(), 0, 1, 0);

  m_program->setUniformValue(m_matrixUniform, matrix);

  glEnableVertexAttribArray(0);
  glEnableVertexAttribArray(1);

  glDrawArrays(GL_TRIANGLES, 0, 3);

  glDisableVertexAttribArray(0);
  glDisableVertexAttribArray(1);

  m_program->release();

  ++m_frame;

  requestUpdate();
}