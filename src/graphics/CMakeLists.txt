add_library(
  Graphics
  STATIC
  Window.cpp
  Program.cpp
)

target_link_libraries(
  Graphics
  PRIVATE
  GLAD
  glfw
  glm::glm
)

target_include_directories(
  Graphics
  PRIVATE
  ${INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIR}
  ${GLM_SOURCE_DIR}
)

