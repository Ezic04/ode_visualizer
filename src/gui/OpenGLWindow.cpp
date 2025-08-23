#include "gui/OpenGLWindow.hpp"

OpenGLWindow::OpenGLWindow(
  QWindow *parent
) : QWindow(parent),
    m_device(new QOpenGLPaintDevice)
{
  this->setSurfaceType(QWindow::OpenGLSurface);
}

OpenGLWindow::~OpenGLWindow(void) {
  delete(m_context);
  delete(m_device);
}

void OpenGLWindow::render(void) {
  glClear(GL_COLOR_BUFFER_BIT 
    | GL_DEPTH_BUFFER_BIT 
    | GL_STENCIL_BUFFER_BIT
  );

  m_device->setSize(this->size() * this->devicePixelRatio());
  m_device->setDevicePixelRatio(this->devicePixelRatio());
}

void OpenGLWindow::setAnimating(bool animating) {
  m_animating = animating;
  if (animating) { this->requestUpdate(); }
}

void OpenGLWindow::renderNow(void) {
  if (!this->isExposed()) { return; }
  else if (!m_context) { this->initialize(); }

  m_context->makeCurrent(this);
  this->render();
  m_context->swapBuffers(this);
  
  if (m_animating) { this->requestUpdate(); }
}

void OpenGLWindow::initialize(void) {
  m_context = new QOpenGLContext(this);

  m_context->setFormat(this->requestedFormat());
  m_context->create();
  m_context->makeCurrent(this);

  this->initializeOpenGLFunctions();
}

bool OpenGLWindow::event(QEvent *event) {
  switch (event->type()) {
    case QEvent::UpdateRequest: 
      this->renderNow(); 
      return true;
    default: 
      return QWindow::event(event);
  }
}

void OpenGLWindow::exposeEvent(QExposeEvent *event) {
  Q_UNUSED(event);
  if (this->isExposed()) { this->renderNow(); }
}