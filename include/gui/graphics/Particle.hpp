#pragma once

#include "gui/graphics/Mesh.hpp"
#include "gui/graphics/ParticleShader.hpp"
#include "gui/graphics/OpenGLFunctions.hpp"

class Particle : public Mesh {
public:

  Particle(Mesh&& geometry);
  void draw(ParticleShader* shader);
  
private:

  OpenGLFunctions* m_gl = nullptr;

};