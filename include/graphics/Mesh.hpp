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
   * @brief Destroys the mesh 
   *  object.
   */
  ~Mesh(void);

  /*
   * @brief Sets the GPU program 
   *  used by the mesh object.
   * 
   * @param program Program to be 
   *  assigned.
   */
  void setProgram(Program& program) { m_program = &program; }

  /*
   * @brief Returns a pointer to
   *  the GPU program used by the 
   *  mesh object.
   * 
   * @return Pointer to the GPU program
   *  used by the mesh object.
   */
  const Program* const getProgram(void) const { return m_program; }

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
   * @brief Returns the current 
   *  scale of the mesh.
   * 
   * @return Current scale of 
   *  the mesh.
   */
  Vec3 getScale(void) const;

  /*
   * @brief Returns the current 
   *  translation of the mesh.
   * 
   * @return Current tranlation
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

  /*
   * @brief Returns a pointer 
   *  to the calculated model
   *  matrix containing all 
   *  of the applied transformations.
   * 
   * @return Pointer to the 
   *  model matrix (glm::mat4*).
   */
  const void* const getModelMatrix(void) const { return m_model_matrix; }
  
  /*
   * @brief Returns the ID of 
   *  the Vertex Array Object 
   *  stored in the GPU memory.
   * 
   * @return VAO ID.
   */
  unsigned int getVAO(void) const { return m_VAO; }

  /*
   * @brief Returns the ID of
   *  the Vertex Buffer Object
   *  stored in the GPU memory.
   * 
   * @return VBO ID.
   */
  unsigned int getVBO(void) const { return m_VBO; }

  /*
   * @brief Returns the ID of
   *  the Indices Buffer Object
   *  (Element Array Buffer) stored
   *  in the GPU memory.
   * 
   * @return IBO ID.
   */
  unsigned int getIBO(void) const { return m_IBO; }

  /*
   * @brief Returns the index 
   *  count of the mesh object.
   * 
   * @return Index count of the
   *  mesh object.
   */
  size_t getIndexCount(void) const { return m_index_count; }


private:

  /*
   * @brief Updates the model
   *  matrix based on the applied
   *  mesh transforms.
   */
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

  /** Count of internal transform vectors */
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