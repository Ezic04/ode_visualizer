add_library(
  GRAPHICS_LIB
  STATIC
  Window.cpp
)

target_link_libraries(
  GRAPHICS_LIB
  PRIVATE
  GLAD
  glfw
)

target_include_directories(
  GRAPHICS_LIB
  PRIVATE
  ${INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIR}
)

