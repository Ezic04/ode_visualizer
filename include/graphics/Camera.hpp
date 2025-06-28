#pragma once

#include <vector>
#include <cstdint>

#include "graphics/Mesh.hpp"

namespace graphics {

class Camera {
public:

  Camera();
  ~Camera(void);

  void move(float x, float y, float z);
  void rotate(float x, float y, float z);

  void setPosition(float x, float y, float z);
  void setRotation(float x, float y, float z);

  void render(const Mesh& mesh);
  void render(const std::vector<Mesh>& scene);
  void render(const std::vector<Mesh*>& scene);

private:

  /*
   * @brief Private enum type
   * for indexing into the internal 
   * array of view and projection
   * matrices.
   */
  enum Matrices {
    VIEW,
    PROJECTION,
    CAMERA
  };

  static constexpr uint8_t k_matrix_count = 3;

  /*
   * Array of glm::mat4 representing
   * the camera's view, projection and
   * V*P matrices.
   */
  void* m_matrices;

};

}