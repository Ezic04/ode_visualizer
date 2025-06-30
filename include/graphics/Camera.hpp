#pragma once

#include <cstdint>

#include "graphics/Vec3.hpp"
#include "graphics/Mesh.hpp"

namespace graphics {

/*
 * @brief Class that represents a 
 *  camera in 3D space and is used
 *  for rendering geometry onto the 
 *  screen.
 */
class Camera {
public:

  /*
   * @brief All modifiable camera
   *  parameters that can be passed
   *  to and applied by a camera object.
   */
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

  /*
   * @brief Constructs a camera
   *  object with given parameters.
   * 
   * @param params Parameters that 
   *  will be used to construct a 
   *  new camera.
   */
  Camera(const Parameters& params);

  /*
   * @brief Destroys a camera
   *  object.
   */
  ~Camera(void);

  /*
   * @brief Sets the position 
   *  of the camera in 3D space.
   * 
   * @param t 3D vector representing
   *  the new camera position in 3D
   *  space.
   */
  void setTranslation(const Vec3& t);

  /*
   * @brief Sets the rotation 
   *  of the camera in 3D space.
   * 
   * @param r 3D vector representing
   *  the new camera rotation in 3D
   *  space. The rotation is given in
   *  degrees and parsed like this:
   *  - x_coord - pitch
   *  - y_coord - yaw
   *  - z_coord - roll
   */
  void setRotation(const Vec3& r);

  /*
   * @brief Moves the camera in the 
   *  direction of the camera front
   *  vector. Positive values move the
   *  camera forwards and negative values
   *  move the camera backwars.
   * 
   * @param distance Distance of the
   *  translation.
   */
  void moveLongitudinal(float distance);

  /*
   * @brief Moves the camera in the 
   *  direction of the camera right
   *  vector. Positive values move 
   *  the camera rightwards and negative 
   *  values move the camera leftwards.
   * 
   * @param distance Distance of the
   *  translation.
   */
  void moveLateral(float distance);

  /*
   * @brief Moves the camera in the 
   *  direction of the world-up vector 
   *  (0.0, 1.0, 0.0). Positive values 
   *  move the camera upwards and negative 
   *  values move the camera downwards.
   * 
   * @param distance Distance of the
   *  translation.
   */
  void moveVertical(float distance);

  /*
   * @brief Adjusts the pitch of the
   *  camera relative to the current
   *  camera pitch (up-down movement).
   * 
   * @param tilt Pitch change given 
   *  in degrees. Positive values tilt
   *  the camera backwards and negative
   *  values tilt the camera forwards.
   */
  void tiltPitch(float tilt);

  /*
   * @brief Adjusts the yaw of the
   *  camera relative to the current
   *  camera yaw. (left-right movement).
   * 
   * @param tilt Yaw change given 
   *  in degrees. Positive values rotate 
   *  the camera rightwards and negative
   *  values rotate the camera leftwards.
   */
  void tiltYaw(float tilt);
  
  /*
   * @brief Adjusts the roll of the
   *  camera relative to the current
   *  camera roll. (side to side movement).
   * 
   * @param tilt Roll change given 
   *  in degrees. Positive values tilt 
   *  the camera rightwards and negative
   *  values tilt the camera leftwards.
   */
  void tiltRoll(float tilt);

  /*
   * @brief Sets the camera parameters
   *  to a given set of new parameters
   *  and recalculates projection matrices.
   * 
   * @param params New camera parameters.
   */
  void setCameraPrameters(const Parameters& params);

  /*
   * @brief Returns the current camera
   *  parameters.
   * 
   * @return Current camera parameters.
   */
  Parameters getCameraParameters(void) const { return m_params; }

  /*
   * @brief Renders a mesh onto the
   *  screen using mesh' program and
   *  current camera parameters.
   * 
   * @param mesh Mesh to be rendered
   *  onto the screen.
   */
  void render(const Mesh& mesh);

private:

  /*
   * @brief Translates the camera relative 
   *  to its current position and recalculates
   *  the view and projection matrices. This 
   *  method doesn't take the camera's rotation 
   *  into consideration and moves it alongside 
   *  world coordinates.
   * 
   * @param t 3D vector representing the 
   *  translation in 3D space.
   */
  void translate(const Vec3& t);

  /*
   * @brief Rotates the camera and
   *  recalculates the view and projection
   *  matrices.
   * 
   * @param r 3D vector representing the 
   *  rotation in 3D space.
   */
  void rotate(const Vec3& r);

  /*
   * @brief Updates the view matrix
   *  based on the current camera 
   *  parameters.
   */
  void updateViewMatrix(void);
 
  /*
   * @brief Updates the projection 
   *  matrix based on the current 
   *  camera parameters.
   */ 
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
   *  for indexing into the internal 
   *  array of view and projection
   *  matrices.
   */
  enum Matrices {
    VIEW,
    PROJECTION,
    CAMERA
  };

  /*
   * @brief Private enum type
   *  for indexing into the 
   *  internal array of camera 
   *  vectors.
   */
  enum Vectors {
    FRONT,
    RIGHT,
    UP
  };

  /** Count of internal matrices */
  static constexpr uint8_t k_matrix_count = 3;

  /** Count of internal vectors */
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

  /** Current camera parameters */
  Parameters m_params;

};

}