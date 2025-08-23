#pragma once

#include <QWindow>
#include <QPainter>

#include <QEvent>
#include <QExposeEvent>

#include <QOpenGLFunctions>
#include <QOpenGLPaintDevice>

/**
 * @author Slawomir Brzozka
 * @author Julian Konowalski
 *
 * @brief Basic window with it's own 
 *  OpenGL context. Can be inherited 
 *  to construct OpenGL scene. 
 */
class OpenGLWindow : public QWindow, protected QOpenGLFunctions {
  Q_OBJECT
public:

  /**
   * @brief Constructs a new OpenGLWindow object
   *  and attaches it to a parent component (if 
   *  the parent component is specified).
   *
   * @param parent Pointer to QWindow object that
   *  will be assigned as the OpenGLWindow's parent
   *  component.
   */
  explicit OpenGLWindow(QWindow *parent = nullptr);

  /**
   * @brief Frees the resources allocated
   *  by the OpenGLWindow object. 
   */
  ~OpenGLWindow(void);

  /**
   * @brief Clears frame, depth and stencil
   *  buffers and adjusts the paint device
   *  size and pixel ratio.
   *
   * @see m_device
   */
  virtual void render(void);

  /**
   * @brief Sets if the window should 
   *  animate. If the flag is set to 
   *  true the object immediately 
   *  requests a frame update.
   *
   * @param animating New value of the
   *  animating flag.
   *
   * @see m_animating
   */
  void setAnimating(bool animating);

public slots:

  /**
   * @brief Starts the render loop
   *  by calling the render method.
   *  The call is made only when the
   *  object is exposed. Additionally
   *  if the object is not initialized 
   *  the initialize method is called
   *  before the rendering starts.
   *
   * @see render
   * @see initialize
   * @see isExposed
   */
  void renderNow(void);

protected:
 
  /**
   * @brief Initializes the object
   *  by creating a new context and
   *  loading OpenGL functions. This
   *  method cannot be called from the
   *  constructor, as it requires the
   *  object to be fully constructed
   *  beforehand. Otherwise it will 
   *  result in a program crash.
   *
   * @see m_context
   * @see initializeOpenGLFunctions
   */
  virtual void initialize(void);

  /**
   * @brief Takes action upon an 
   *  event. OpenGLWindow objects 
   *  only react to update request 
   *  events. Any other type of event 
   *  will be passed to the parent 
   *  QWindow class.
   *
   * @param event Event that should
   *  be handled.
   *
   * @return Boolean indicating if the
   *  event was handled successfully.
   *
   * @see QEvent
   * @see QWindow::event
   */
  bool event(QEvent *event) override;

  /**
   * @brief Called when the state of the
   *  window changes (unexposed to exposed
   *  or vice versa). If the window is exposed
   *  the renderNow method is called. Otherwise
   *  no further action is taken.
   *
   * @param event Pointer to expose event that 
   *  triggered the method call.
   *
   * @see QExposeEvent
   */
  void exposeEvent(QExposeEvent *event) override;

private:

  /**
   * @brief Flag indicating if
   *  the object is animating.
   *  In the animating state the
   *  object automatically sends
   *  an update request to generate
   *  the next frame after finishing
   *  the current render pass. 
   *  Otherwise no further action is
   *  taken after the render process
   *  finishes.
   */
  bool m_animating = false;

  /**
   * @brief Internal OpenGL context
   *
   * @see QOpenGLContext
   */
  QOpenGLContext *m_context = nullptr;

  /**
   * @brief Internal paint device that
   *  enables painting to the OpenGL
   *  context using QPainer.
   *
   * @see QOpenGLContext
   * @see QOpenGLPaintDevice
   */
  QOpenGLPaintDevice *m_device = nullptr;

};