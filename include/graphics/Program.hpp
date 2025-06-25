#pragma once

#include <string>
#include <vector>

namespace graphics {
 
/*
 * @brief GPU program class 
 *  that consists of a vertex 
 *  and a buffer shader.
 */
class Program {
public:

  /*
   * @brief Creates a program object
   *  from vertex and fragmet shader
   *  files. 
   * 
   * @param vertex_shader_path Path to 
   *  a vertex shader file. 
   * @param fragment_shader_path Path to 
   *  a fragment shader file. 
   * 
   * @throw std::runtime_error In case of 
   *  an error during execution of any of
   *  the necessary initialization steps.
   */
  Program(const std::string& vertex_shader_path, const std::string& fragment_shader_path);

  /*
   * @brief Destroys the GPU program 
   *  by freeing the created shaders. 
   */
  ~Program(void);

  /*
   * @brief Returns the uniform 
   *  model matrix ID.
   * 
   * @return Uniform model value.
   */
  [[nodiscard]] inline unsigned int getUniformModelID(void) const { return m_uniform_model_id; }
  
  /*
   * @brief Returns the uniform 
   *  projection matrix ID.
   * 
   * @return Uniform projection value.
   */
  [[nodiscard]] inline unsigned int getUniformProjectionID(void) const { return m_uniform_projection_id; }

  /*
   * @brief Returns the uniform 
   *  view matrix ID.
   * 
   * @return Uniform view value.
   */
  [[nodiscard]] inline unsigned int getUniformViewID(void) const { return m_uniform_view_id; }

  /*
   * @brief Sets the object as 
   *  the currently used program.
   *  By calling use on an object 
   *  it replaces the currently 
   *  used program. Only one program 
   *  can be used at a given moment.
   */
  void use(void);

private:

  /*
   * @brief Loads the contents 
   *  of a shader file to a 
   *  vector of chars.
   * 
   * @param shader_path Path to 
   *  the shader file to be loaded.
   * 
   * @return std::vector<char> vector 
   *  containing the entire shader file.
   * 
   * @throw std::runtime_error If the file
   *  cannot be read.
   */
  std::vector<char> loadShader(const std::string& shader_path);

  /*
   * @brief Compiles a shader.
   *
   * @param code Pointer to the 
   *  char array containing the
   *  shader's source code.
   * @param code_length Length 
   *  of the array containing the 
   *  shader's source code. 
   * @param type Type of the shader. 
   *  Value should be taken from the 
   *  predefined types in the generated 
   *  OpenGL header.
   * 
   * @throw std::runtime_error If the 
   *  shader fails to compile.
   */
  void compileShader(const char* code, const int& code_length, const unsigned int& type);

  /*
   * @brief Links the created 
   *  program.
   * 
   * @throw std::runtime_error If 
   *  the program fails to link.
   */
  void linkProgram(void);

  /*
   * @brief Validates the created 
   *  program.
   * 
   * @throw std::runtime_error If 
   *  the program fails to validate.
   */
  void validateProgram(void);

  /* 
   * @brief Allocates memory for
   *  the uniform translation matrices
   *  on the GPu and assigns received
   *  IDs to the corresponding member 
   *  variables.
   */
  void loadUniforms(void);

  /*
   * @brief Frees the program 
   *  from the GPU memory and 
   *  resets the uniform variables 
   *  to 0.
   */
  void clear(void);

  /* 
   * IDs of transformation matrices 
   * stored in the GPU memory. They're 
   * used by the vertex shader and can 
   * be accessed by their IDs.
   */
  unsigned int m_uniform_model_id;       ///< Model matrix ID
  unsigned int m_uniform_projection_id;  ///< Projection matrix ID
  unsigned int m_uniform_view_id;        ///< View matrix ID

  unsigned int m_id; ///< ID of the program in GPU memory

}; 

} 


