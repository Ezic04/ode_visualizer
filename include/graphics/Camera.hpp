#pragma once

#include <cstdint>

#include "graphics/Vec3.hpp"
#include "graphics/Mesh.hpp"

namespace graphics {

class Camera {
public:

  struct Parameters {
    Vec3 position           = Vec3(0.0f, 0.0f, 0.0f);
    Vec3 rotation           = Vec3(0.0f, 0.0f, 0.0f);
    uint16_t screen_width   = 800;
    uint16_t screen_height  = 600;
    float FOV               = 45.0f;
    float near_clip_plane   = 0.1f;
    float far_clip_plane    = 100.0f;
    float max_pitch         = 80.0f;
    float min_pitch         = -80.0f;
    float max_roll          = 0.0f;
    float min_roll          = 0.0f;
  };

  Camera(const Parameters& params);
  ~Camera(void);


  void setTranslation(const Vec3& t);
  void setRotation(const Vec3& r);

  void moveLongitudinal(float distance);
  void moveLateral(float distance);
  void moveVertical(float distance);

  void tiltPitch(float tilt);
  void tiltYaw(float tilt);
  void tiltRoll(float tilt);

  void setCameraPrameters(const Parameters& params);
  Parameters getCameraParameters(void) const { return m_params; }

  void render(const Mesh& mesh);

private:

  void translate(const Vec3& t);
  void rotate(const Vec3& r);

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

  enum Vectors {
    FRONT,
    RIGHT,
    UP
  };

  static constexpr uint8_t k_matrix_count = 3;
  static constexpr uint8_t k_vector_count = 3;

  /*
   * Array of glm::mat4 representing
   * the camera's view, projection and
   * V*P matrices.
   */
  void* m_matrices;

  /*
   * Array of Vec3 representing the 
   * front and right helper vectors
   * used in the camera movement and
   * view matrix calculations.
   */
  Vec3 m_vectors[k_vector_count];

  Parameters m_params;

};

}