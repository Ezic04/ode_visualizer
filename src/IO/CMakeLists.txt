add_library(
  IO
  STATIC
  Window.cpp
  InputHandler.cpp
)

target_link_libraries(
  IO 
  PRIVATE
  GLAD
  glfw
)

target_include_directories(
  IO
  PRIVATE
  ${INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
  ${GLFW_INCLUDE_DIR}
)

