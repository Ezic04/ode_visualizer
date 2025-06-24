add_library(
  Graphics
  STATIC
  Window.cpp
  Shader.cpp
)

target_link_libraries(
  Graphics
  PRIVATE
  GLAD
  glfw
)

target_include_directories(
  Graphics
  PRIVATE
  ${INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIR}
)

