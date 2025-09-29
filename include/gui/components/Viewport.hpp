#pragma once

#include <vector>

#include <QWheelEvent>
#include <QMouseEvent>
#include <QOpenGLWindow>
#include <QOpenGLShaderProgram>

#include "gui/graphics/Camera.hpp"
#include "gui/graphics/Particle.hpp"
#include "gui/graphics/WorldGrid.hpp"
#include "gui/graphics/GridShader.hpp"
#include "gui/graphics/ParticleShader.hpp"
#include "gui/graphics/OpenGLFunctions.hpp"

class Viewport: public QOpenGLWindow {
  Q_OBJECT
public:
  Viewport(QWindow *parent = nullptr);
  ~Viewport(void);

  void renderFrame(const std::vector<std::array<float, 3>> &positions);

  inline WorldGrid::GridParameters getGridParameters(void) const { return m_world_grid->getParameters(); }
  inline void setGridParameters(const WorldGrid::GridParameters& params) { m_world_grid->setParameters(params); }  

public slots:

  inline void setWorldGridCellSize(float cell_size) { m_world_grid->setCellSize(cell_size); }
  inline void setWorldGridFadeStart(float fade_start) { m_world_grid->setFadeStartDistance(fade_start); }
  inline void setWorldGridFadeEnd(float fade_end) { m_world_grid->setFadeEndDistance(fade_end); }

signals:
  void frameFinished(void);

private:
  virtual void initializeGL(void) override;
  virtual void paintGL(void) override;

  // ** move this to an event handler
  virtual void wheelEvent(QWheelEvent *event) override;
  virtual void mouseMoveEvent(QMouseEvent *event) override;
  virtual void mousePressEvent(QMouseEvent *event) override;
  virtual void mouseDoubleClickEvent(QMouseEvent *event) override;
  // ** move this to an event handler

  void clearViewport(void);
  void drawParticles(void);
  void drawGrid(void);

  QVector4D getVieportSize(void);

  QPoint m_last_mouse_position;

  Camera m_camera;

  Particle *m_particle = nullptr;
  ParticleShader *m_particle_shader = nullptr;

  WorldGrid *m_world_grid = nullptr;
  GridShader *m_grid_shader = nullptr;

  OpenGLFunctions *m_gl = nullptr;
};