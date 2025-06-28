add_library(
  Graphics
  STATIC
  Vec3.cpp
  Mesh.cpp
  Camera.cpp
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

