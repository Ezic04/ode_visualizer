add_library(
  Simulation
  STATIC
  Simulation.cpp
)

target_include_directories(
  Simulation
  PRIVATE
  ${INCLUDE_DIR}
)

target_link_libraries(
  Simulation
  PRIVATE
  Expr
  Graphics
  Solver
  IO
)

target_compile_definitions(
  Simulation
  PUBLIC
  VERT_PATH="${CMAKE_SOURCE_DIR}/shader/shader.vert"
  FRAG_PATH="${CMAKE_SOURCE_DIR}/shader/shader.frag"
)
