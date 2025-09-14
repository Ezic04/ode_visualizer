#pragma once

#include <array>
#include <vector>

#include "gui/graphics/OpenGLFunctions.hpp"

class Mesh {
public:

  Mesh(
    const std::vector<float> &vertices, 
    const std::vector<unsigned int> &indices,
    const std::vector<std::array<float, 3>> &instances
  );
  Mesh(Mesh &&other);
  ~Mesh(void);

  Mesh(const Mesh &other) = delete;
  void operator=(const Mesh& other) = delete;

  void update(const std::vector<std::array<float, 3>>& positions);

  inline const GLuint getVAO(void) const { return m_VAO; }
  inline const GLuint getIBO(void) const { return m_IBO; }
  inline const GLuint getVerticesVBO(void) const { return m_vertices_VBO; }
  inline const GLuint getInstancesVBO(void) const { return m_instances_VBO; }

  inline const unsigned int getIndexCount(void) const { return m_index_count; }
  inline const unsigned int getVertexCount(void) const { return m_vertex_count; }
  inline const unsigned int getInstanceCount(void) const { return m_instance_count; }

protected:

  GLuint m_VAO = 0;
  GLuint m_IBO = 0;
  GLuint m_vertices_VBO = 0;
  GLuint m_instances_VBO = 0;

  unsigned int m_index_count = 0;
  unsigned int m_vertex_count = 0;
  unsigned int m_instance_count = 0;

  OpenGLFunctions* m_gl;
  
};

class Plane : public Mesh {
public:
  Plane(
    float width,
    float depth,
    const std::vector<std::array<float, 3>>& instances
  );
private:
  static Mesh construct(
    float width,
    float depth,
    const std::vector<std::array<float, 3>>& instances
  );
};

class Cube : public Mesh {
public:
  Cube(
    float width,
    float height,
    float depth,
    const std::vector<std::array<float, 3>>& instances 
  );
private:
  static Mesh construct(
    float width,
    float height,
    float depth,
    const std::vector<std::array<float, 3>>& instances
  );
};

class Sphere : public Mesh {
public:
  Sphere(
    float radius,
    unsigned char resolution,
    const std::vector<std::array<float, 3>>& instances
  );
private:
  static Mesh construct(
    float radius,
    unsigned char resolution,
    const std::vector<std::array<float, 3>>& instances
  );
};