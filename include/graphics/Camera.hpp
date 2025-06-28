#pragma once

#include <cstdint>

#include "graphics/Vec3.hpp"
#include "graphics/Mesh.hpp"

namespace graphics {

class Camera {
public:

  struct Parameters {
    Vec3 position = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 rotation = Vec3(0.0f, 0.0f, 0.0f);
    float FOV = 45.0f;
    uint16_t screen_width = 800;
    uint16_t screen_height = 600;
    float near_clip_plane = 0.1f;
    float far_clip_plane = 100.0f;
  };

  Camera(const Camera::Parameters& params);
  ~Camera(void);

  void translate(const Vec3& t);
  void rotate(const Vec3& r);

  void setCameraPrameters(const Camera::Parameters& params);
  Camera::Parameters getCameraParameters(void) const { return m_params; }

  void render(const Mesh& mesh);

private:

  void updateViewMatrix(void);
  void updateProjectionMatrix(void);

  /*
   * @brief Updates the camera 
   *  matrix based on the camera
   *  parameters and applied camera
   *  transforms.
   */
  void updateCameraMatrix(void);

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

  Camera::Parameters m_params;

};

}