#pragma once

#include <array>
#include <vector>

#include <QMatrix4x4>

#include "gui/graphics/OpenGLFunctions.hpp"

class Mesh {
public:

  Mesh(
    const std::vector<float> &vertices, 
    const std::vector<unsigned int> &indices,
    const std::vector<float> &normals,
    const std::vector<std::array<float, 3>> &instances
  );
  Mesh(Mesh &&other);
  ~Mesh(void);

  Mesh(const Mesh &other) = delete;
  void operator=(const Mesh& other) = delete;

  inline void rotate(float x, float y, float z) { m_model_matrix.rotate(x, y, z); }
  inline void scale(float x, float y, float z) { m_model_matrix.scale(x, y, z); }
  inline void resetTransforms(void) { m_model_matrix.setToIdentity(); }

  void update(const std::vector<std::array<float, 3>>& positions);

  inline QMatrix4x4 getModelMatrix(void) const { return m_model_matrix; }
  inline unsigned int getIndexCount(void) const { return m_index_count; }
  inline unsigned int getVertexCount(void) const { return m_vertex_count; }
  inline unsigned int getInstanceCount(void) const { return m_instance_count; }

protected:

  QMatrix4x4 m_model_matrix;

  GLuint m_VAO = 0;
  GLuint m_IBO = 0;
  GLuint m_vertices_VBO = 0;
  GLuint m_normals_VBO = 0;
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