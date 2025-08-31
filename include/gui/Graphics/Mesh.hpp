#pragma once

#include <array>
#include <vector>

#include <QOpenGLFunctions_4_5_Core>

class Mesh : protected QOpenGLFunctions_4_5_Core {
public:
  Mesh(void) = default;
  Mesh(const Mesh &other) = delete;
  Mesh(Mesh &&other) = delete;
  ~Mesh(void);

  bool initializeGL(const std::vector<float> &vertices, const std::vector<unsigned int> &indices,
                    const std::vector<std::array<float, 3>> &instances);

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
};