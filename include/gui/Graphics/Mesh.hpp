#pragma once

#include <array>
#include <vector>

#include "gui/graphics/OpenGLFunctions.hpp"

class Mesh {
public:

  static Mesh Plane(float width, float length, const std::vector<std::array<float, 3>>& instances);
  static Mesh Cube(float width, float height, float lenght, const std::vector<std::array<float, 3>>& instances);
  static Mesh Sphere(float radius, unsigned char resolution, const std::vector<std::array<float, 3>>& instances);

  Mesh(
    const std::vector<float> &vertices, 
    const std::vector<unsigned int> &indices,
    const std::vector<std::array<float, 3>> &instances
  );
  Mesh(Mesh &&other);
  ~Mesh(void);

  Mesh(const Mesh &other) = delete;
  void operator=(const Mesh& other) = delete;

  void updateInstances(const std::vector<std::array<float, 3>> &instances);

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