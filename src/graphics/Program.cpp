#include "graphics/Program.hpp"

#include <cassert>
#include <fstream> 

#include <glad/glad.h>

constexpr uint16_t k_error_log_size = 1024;

using namespace graphics;

Program::Program(
  const std::string& vertex_shader_path, 
  const std::string& fragment_shader_path
) : m_id(0),
    m_MVP_matrix_id(0)
{
  m_id = glCreateProgram();
  if (!m_id) {
    std::string error_msg = "Failed to create program from shaders: " 
      + vertex_shader_path 
      + " " 
      + fragment_shader_path;
    throw std::runtime_error(error_msg);
  }

  std::vector<char> vertex_code = this->loadShader(vertex_shader_path);
  std::vector<char> fragment_code = this->loadShader(fragment_shader_path);

  this->compileShader(vertex_code.data(), vertex_code.size(), GL_VERTEX_SHADER);
  this->compileShader(fragment_code.data(), fragment_code.size(), GL_FRAGMENT_SHADER);

  this->linkProgram();
  this->validateProgram();

  m_MVP_matrix_id = glGetUniformLocation(m_id, "MVP");
}

Program::~Program(void) {
  this->clear();
}

bool Program::bind(void) const {
  assert(m_id);
  GLint current_program = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
  if (current_program) { return current_program == m_id; }
  glUseProgram(m_id);
  return true;
}

bool Program::unbind(void) const {
  assert(m_id);
  GLint current_program = 0;
  glGetIntegerv(GL_CURRENT_PROGRAM, &current_program);
  if (current_program != m_id) { return current_program == 0; }
  glUseProgram(0);
  return true;
}

std::vector<char> Program::loadShader(const std::string& shader_path) {
  std::ifstream shader_file(
    shader_path, 
    std::ios::in | std::ios::binary | std::ios::ate
  );

  if (!shader_file.is_open()) {
    std::string error_msg = "Failed to open shader file: " + shader_path;
    throw std::runtime_error(error_msg);
  }

  std::streamsize shader_file_size = shader_file.tellg();
  shader_file.seekg(0, std::ios::beg);

  std::vector<char> shader_code(shader_file_size);
  if (!shader_file.read(shader_code.data(), shader_file_size)) {
    shader_file.close();
    std::string error_msg = "Failed to read the contents of a shader file: " + shader_path;
    throw std::runtime_error(error_msg);
  }

  shader_file.close();
  return std::move(shader_code);
}

void Program::compileShader(
  const char* code, 
  const int& code_length, 
  const unsigned int& type
) {
  GLuint shader = glCreateShader(type);
  glShaderSource(shader, 1, &code, &code_length);
  glCompileShader(shader);

  GLint compile_result = 0;
  GLchar error_log[k_error_log_size] = { 0 };
  glGetShaderiv(shader, GL_COMPILE_STATUS, &compile_result);
  if (!compile_result) {
    glGetShaderInfoLog(shader, k_error_log_size, nullptr, error_log);
    std::string error_msg = "Failed to compile shader: ";
    error_msg += static_cast<char*>(error_log);
    throw std::runtime_error(error_msg);
  }

  glAttachShader(m_id, shader);
}

void Program::linkProgram(void) {
  GLint link_result = 0;
  GLchar error_log[k_error_log_size] = { 0 };
  glLinkProgram(m_id);
  glGetProgramiv(m_id, GL_LINK_STATUS, &link_result);
  if (!link_result) {
    glGetProgramInfoLog(m_id, k_error_log_size, nullptr, error_log);
    std::string error_msg = "Failed to link GPU program: ";
    error_msg += static_cast<const char*>(error_log);
    throw std::runtime_error(error_msg);
  }
}

void Program::validateProgram(void) {
  GLint validate_result = 0;
  GLchar error_log[k_error_log_size] = { 0 };
  glValidateProgram(m_id);
  glGetProgramiv(m_id, GL_LINK_STATUS, &validate_result);
  if (!validate_result) {
    glGetProgramInfoLog(m_id, k_error_log_size, nullptr, error_log);
    std::string error_msg = "Failed to validate GPU program: ";
    error_msg += static_cast<const char*>(error_log);
    throw std::runtime_error(error_msg);
  }
}

void Program::clear(void) {
  if (m_id) { glDeleteProgram(m_id); }
  m_id = 0;
  m_MVP_matrix_id = 0;
}