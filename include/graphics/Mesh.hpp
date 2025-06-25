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
   * @brief Destroys the mesh object
   *  by freeing the memory allocated 
   *  on the GPU.
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

  void render(void);

private:

  /*
   * @brief Frees the mesh
   *  from the GPU memory and
   *  resets the member variables
   *  to 0.
   */
  void clear(void);

  unsigned int m_VAO;
  unsigned int m_VBO;
  unsigned int m_IBO;  
  size_t m_index_count;
  Program* m_program;

};
  
}

