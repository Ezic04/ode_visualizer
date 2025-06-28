#pragma once

#include <string>
#include <vector>

#include "graphics/Vec3.hpp"
#include "graphics/Program.hpp"

namespace graphics {

/*
 * @brief Class that creates
 *  a mesh on the GPU and stores
 *  handles to that mesh. It can 
 *  be used to manipulate that mesh.
 */
class Mesh {
public:

  /*
   * @brief Creates a new mesh object 
   *  from vectors of vertices and indices. 
   *  Vertices are pure floats that indices 
   *  join into groups of 3 to define points. 
   *  Indices are read in groups of 3 and 
   *  each index in the group defines one 
   *  of the coordinates in 3D space of a 
   *  given vertex.
   * 
   * @param vertices List of values from 
   *  which points will be constructed. 
   * @param indices List of indexes that 
   *  will be read in groups of 3 to construct
   *  points using the vector of vertices.
   * @param program GPU program that will be 
   *  used to render the mesh.
   * 
   * @throw std::runtime_error In case of 
   *  failure during mesh creation process. 
   */
  Mesh(
    const std::vector<float>& vertices, 
    const std::vector<unsigned int>& indices,
    Program& program
  );

  /*
   * @brief Creates a new mesh
   *  object from an .obj file. 
   *  The mesh data is allocated 
   *  in the GPU memory.
   * 
   * @param filepath Path to the 
   *  .obj file containing the 
   *  mesh data. 
   * @param program GPU program 
   *  that will be used to render
   *  the mesh.
   * 
   * @throw std::runtime_error In 
   *  case of failure during mesh 
   *  creation process.
   */
  Mesh(const std::string& filepath, Program& program);

  /*
   * @brief Destroys the mesh 
   *  object.
   */
  ~Mesh(void);

  /*
   * @brief Assigns a GPU program 
   *  that will be used to render
   *  the mesh.
   * 
   * @param program Program to be 
   *  assigned.
   */
  void assignProgram(Program& program) { m_program = &program; }

  /*
   * @brief Scales the mesh 
   *  relatively to its current
   *  scale.
   * 
   * @param s Vector in which each 
   *  coordinate represents the scaling 
   *  along the corresponding axis.
   */
  void scale(const Vec3& s);

  /*
   * @brief Translates the mesh
   *  relatively to its current
   *  translation.
   * 
   * @param t Vector in which each
   *  coordinate represents the translation 
   *  along the corresponding axis
   */
  void translate(const Vec3& t);

  /*
   * @brief Rotates the mesh
   *  relatively to its current
   *  rotation.
   * 
   * @param r Vector in which each
   *  coordinate represents the 
   *  rotation along the corresponding
   *  axis (in degrees).
   */
  void rotate(const Vec3& r);
   
  /*
   * @brief Sets the scale of 
   *  the mesh.
   * 
   * @param s Vector in which each 
   *  coordinate represents the scaling 
   *  along the corresponding axis.
   */
  void setScale(const Vec3& s);
  
  /*
   * @brief Sets the translation
   *  of the mesh.
   * 
   * @param t Vector in which each
   *  coordinate represents the translation 
   *  along the corresponding axis
   */
  void setTranslation(const Vec3& t);
  
  /*
   * @brief Sets the rotation of 
   *  the mesh.
   * 
   * @param r Vector in which each
   *  coordinate represents the 
   *  rotation along the corresponding
   *  axis (in degrees).
   */
  void setRotation(const Vec3& r);

  /*
   * @brief Returns the current scale
   *  of the mesh.
   * 
   * @return Vec3 Current scale of 
   *  the mesh.
   */
  Vec3 getScale(void) const;

  /*
   * @brief Returns the current 
   *  translation of the mesh.
   * 
   * @return Vec3 Current tranlation
   *  of the mesh.
   */
  Vec3 getTranslation(void) const;

  /*
   * @brief Returns the current 
   *  rotation of the mesh.
   * 
   * @return Current rotation of 
   *  the mesh.
   */
  Vec3 getRotation(void) const;

  void render(void);

private:

  void calculateModelMatrix(void);

  /*
   * @brief Private enum type 
   *  for indexing into the internal 
   *  array of transformation matrices.
   */
  enum Transforms {
    SCALE,
    ROTATION,
    POSITION 
  };

  static constexpr uint8_t k_transform_count = 3;

  /*
   * Array of glm::vec3 representing 
   * the applied model transforms.
   */
  void* m_transforms;

  /*
   * Pointer to a glm::mat4 object
   * representing combined model 
   * transforms.
   */
  void* m_model_matrix;

  /*
   * Handles to vertex data
   * stored in the GPU memory.
   */
  unsigned int m_VAO;
  unsigned int m_VBO;
  unsigned int m_IBO;
  
  Program* m_program; ///< GPU program to use during rendering
  size_t m_index_count;

};
  
}

