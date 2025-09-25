#include "gui/graphics/Mesh.hpp"

#include <array>
#include <cmath>
#include <numbers>
#include <vector>
#include <cstddef>

Mesh::Mesh(
  const std::vector<float> &vertices, 
  const std::vector<unsigned int> &indices,
  const std::vector<float> &normals, 
  const std::vector<std::array<float, 3>> &instances
) : m_index_count(indices.size()),
    m_vertex_count(vertices.size()),
    m_instance_count(instances.size()),
    m_gl(OpenGLFunctions::getInstance())
{
  m_gl->glGenVertexArrays(1, &m_VAO);
  m_gl->glBindVertexArray(m_VAO);


  // ibo setup 
  m_gl->glGenBuffers(1, &m_IBO);
  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_IBO);
  m_gl->glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * indices.size(), indices.data(), GL_STATIC_DRAW);


  // vertices vbo setup
  m_gl->glGenBuffers(1, &m_vertices_VBO);
  m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_vertices_VBO);
  m_gl->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * vertices.size(), vertices.data(), GL_STATIC_DRAW);

  m_gl->glEnableVertexAttribArray(0);
  m_gl->glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, nullptr);


  // normals vbo setup
  m_gl->glGenBuffers(1, &m_normals_VBO);
  m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_normals_VBO);
  m_gl->glBufferData(GL_ARRAY_BUFFER, sizeof(float) * normals.size(), normals.data(), GL_STATIC_DRAW);

  m_gl->glEnableVertexAttribArray(1);
  m_gl->glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 0, nullptr); 


  // instances vbo setup
  m_gl->glGenBuffers(1, &m_instances_VBO);
  m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_instances_VBO);
  m_gl->glBufferData(GL_ARRAY_BUFFER, sizeof(std::array<float, 3>) * instances.size(), instances.data()->data(), GL_DYNAMIC_DRAW);

  m_gl->glEnableVertexAttribArray(2);
  m_gl->glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, sizeof(float) * 3, nullptr);
  m_gl->glVertexAttribDivisor(2, 1);


  // unbind buffers
  m_gl->glBindBuffer(GL_ARRAY_BUFFER, 0);
  m_gl->glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0);
  m_gl->glBindVertexArray(0);
}

Mesh::Mesh(Mesh&& other) {
  m_VAO = other.m_VAO;                        other.m_VAO = 0;
  m_IBO = other.m_IBO;                        other.m_IBO = 0;
  m_vertices_VBO = other.m_vertices_VBO;      other.m_vertices_VBO = 0;
  m_normals_VBO = other.m_normals_VBO;        other.m_normals_VBO = 0;
  m_instances_VBO = other.m_instances_VBO;    other.m_instances_VBO = 0;

  m_index_count = other.m_index_count;        other.m_index_count = 0;
  m_vertex_count = other.m_vertex_count;      other.m_vertex_count = 0;
  m_instance_count = other.m_instance_count;  other.m_instance_count = 0;

  m_gl = other.m_gl;                          other.m_gl = nullptr;
}

Mesh::~Mesh(void) {
  if (m_VAO != 0) { m_gl->glDeleteVertexArrays(1, &m_VAO); }
  if (m_IBO != 0) { m_gl->glDeleteBuffers(1, &m_IBO); }
  if (m_vertices_VBO != 0) { m_gl->glDeleteBuffers(1, &m_vertices_VBO); }
  if (m_normals_VBO!= 0) { m_gl->glDeleteBuffers(1, &m_normals_VBO); }
  if (m_instances_VBO != 0) { m_gl->glDeleteBuffers(1, &m_instances_VBO); }
}

void Mesh::update(const std::vector<std::array<float, 3>> &positions) {
  const size_t instance_count = positions.size();
  const size_t data_size = sizeof(std::array<float, 3>) * instance_count;
  const float *const data = positions.data()->data();
  m_gl->glBindBuffer(GL_ARRAY_BUFFER, m_instances_VBO);
  if (instance_count != m_instance_count) { m_gl->glBufferData(GL_ARRAY_BUFFER, data_size, data, GL_DYNAMIC_DRAW);
    m_instance_count = instance_count;
  } else {
    m_gl->glBufferSubData(GL_ARRAY_BUFFER, 0, data_size, data);
  }
}

Plane::Plane(
  float width,
  float depth,
  const std::vector<std::array<float, 3>>& instances
) : Mesh(Plane::construct(width, depth, instances))
{}

Mesh Plane::construct(  
  float width,
  float depth,
  const std::vector<std::array<float, 3>>& instances
) {
  width /= 2.0f;
  depth /= 2.0f;

  return std::move(Mesh({
    -width, 0.0f, -depth,
    -width, 0.0f,  depth,
     width, 0.0f,  depth,
     width, 0.0f, -depth
  }, {
    0, 2, 1,
    0, 3, 2
  }, {
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f,
    0.0f, 1.0f, 0.0f
  }, instances)); 
}

Cube::Cube(
  float width,
  float height,
  float depth,
  const std::vector<std::array<float, 3>>& instances
) : Mesh(Cube::construct(width, height, depth, instances)) 
{}

Mesh Cube::construct(
  float width,
  float height,
  float depth,
  const std::vector<std::array<float, 3>>& instances
) {
  width /= 2.0f;
  height /= 2.0f;
  depth /= 2.0f;

  return std::move(Mesh({
    -width, -height,  depth,
    -width,  height,  depth,
     width,  height,  depth,
     width, -height,  depth,

    -width, -height, -depth,
    -width,  height, -depth,
     width,  height, -depth,
     width, -height, -depth
  }, {
    0, 2, 1,
    0, 3, 2,
    0, 4, 7,
    0, 7, 3,
    3, 6, 2,
    3, 7, 6,
    4, 0, 1,
    4, 1, 5,
    5, 1, 2,
    5, 2, 6,
    7, 4, 5,
    7, 5, 6
  }, {
    // add normals
  }, instances));
}

Sphere::Sphere(
  float radius,
  unsigned char resolution,
  const std::vector<std::array<float, 3>>& instances
) : Mesh(Sphere::construct(radius, resolution, instances))
{}

// taken and modified from https://www.songho.ca/opengl/gl_sphere.html#sphere
Mesh Sphere::construct(
  float radius,
  unsigned char resolution,
  const std::vector<std::array<float, 3>>& instances
) {
  unsigned int k1 = 0, k2 = 0;
  unsigned char sector_count = resolution;
  unsigned char stack_count = resolution / 2;
  
  float x = 0.0f, y = 0.0f, z = 0.0f, xz = 0.0f;
  float sector_step = 2.0f * std::numbers::pi / (float)sector_count;
  float stack_step = std::numbers::pi / (float)stack_count;
  float sector_angle = 0.0f, stack_angle = 0.0f;
 
  unsigned int vertex_count = (stack_count + 1) * (sector_count + 1) * 3;

  std::vector<float> vertices;
  vertices.reserve(vertex_count);
  
  std::vector<unsigned int> indices;
  indices.reserve(stack_count * (sector_count + 1) * 6);

  std::vector<float> normals;
  normals.reserve(vertex_count);

  for(int i = 0; i < stack_count + 1; ++i) {
      stack_angle= std::numbers::pi / 2.0f - (i * stack_step);
      xz = radius * cosf(stack_angle);
      y = radius * sinf(stack_angle);
 
      k1 = i * (sector_count+ 1);
      k2 = k1 + sector_count + 1;

    for(int j = 0; j < sector_count + 1; ++j, ++k1, ++k2) {
      sector_angle= j * sector_step;
    
      vertices.push_back(xz * cosf(sector_angle));
      vertices.push_back(y);
      vertices.push_back(xz * sinf(sector_angle));

      if(i) {
          indices.push_back(k1 + 1);
          indices.push_back(k2);
          indices.push_back(k1);
      }
      
      if(i != (stack_count - 1)) {
          indices.push_back(k2 + 1);
          indices.push_back(k2);
          indices.push_back(k1 + 1);
      }
    }
  }

  return std::move(Mesh(vertices, indices, normals, instances)); 
}