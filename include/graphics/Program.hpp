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
   *  MVP matrix ID.
   * 
   * @return Uniform MVP matrix
   *  ID
   */
  [[nodiscard]] inline unsigned int getUniformMVPID(void) const { return m_MVP_matrix_id; }

  /*
   * @brief Binds the object as 
   *  the currently used program.
   *  The method performs a check
   *  to see if any other program 
   *  is currently being used. If 
   *  yes then the binding is aborted.
   * 
   * @return bool True if current program 
   *  is bound, regardless of if it 
   *  was bound before the method call.
   */
  bool bind(void) const;

  /*
   * @brief Unbinds the object and
   *  stops it from being used during 
   *  rendering. The method performs 
   *  a check if the object is currently 
   *  bound. If not the the unbinding
   *  is aborted.
   * 
   * @return bool True if the current 
   *  program was unbound successfuly.
   */
  bool unbind(void) const;

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
   * @brief Frees the program 
   *  from the GPU memory and 
   *  resets the uniform variables 
   *  to 0.
   */
  void clear(void);

  /* 
   * ID of a summary transformation 
   * matrix consisting of model, view
   * and projection matrices stored in 
   * the GPU memory.
   */
  unsigned int m_MVP_matrix_id;
  unsigned int m_id; ///< ID of the program in GPU memory

}; 

} 


