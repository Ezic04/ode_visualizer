#pragma once

#include <string>
#include <vector>

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
   * @param x Scaling factor in 
   *  the x axis.
   * @param y Scaling factor in
   *  the y axis.
   * @param z Scaling factor in 
   *  the z axis.
   */
  void scale(float x, float y, float z);

  /*
   * @brief Translates the mesh
   *  relatively to its current
   *  translation.
   * 
   * @param x Translation in the
   *  x axis.
   * @param y Translation in the 
   *  y axis.
   * @param z Translation in the
   *  z axis.
   */
  void translate(float x, float y, float z);

  /*
   * @brief Rotates the mesh
   *  relatively to its current
   *  rotation.
   * 
   * @param x Rotation in the 
   *  x axis (degrees).
   * @param y Rotation in the 
   *  y axis (degrees).
   * @param z Rotation in the
   *  z axis (degrees).
   */
  void rotate(float x, float y, float z);
   
  /*
   * @brief Sets the scale of 
   *  the mesh.
   * 
   * @param x Scaling factor in 
   *  the x axis.
   * @param y Scaling factor in
   *  the y axis.
   * @param z Scaling factor in 
   *  the z axis.
   */
  void setScale(float x, float y, float z);
  
  /*
   * @brief Sets the translation
   *  of the mesh.
   * 
   * @param x Translation in the
   *  x axis.
   * @param y Translation in the 
   *  y axis.
   * @param z Translation in the
   *  z axis.
   */
  void setTranslation(float x, float y, float z);
  
  /*
   * @brief Sets the rotation of 
   *  the mesh.
   * 
   * @param x Rotation in the 
   *  x axis (degrees).
   * @param y Rotation in the 
   *  y axis (degrees).
   * @param z Rotation in the
   *  z axis (degrees).
   */
  void setRotation(float x, float y, float z);

  void render(void);

private:

  void calculateModelMatrix(void);

  /*
   * @brief Private enum type 
   *  for indexing internal array 
   *  of transformation matrices 
   */
  enum Transforms {
    SCALE,
    ROTATION,
    TRANSLATION
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

