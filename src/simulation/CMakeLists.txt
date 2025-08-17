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
  PRIVATE
  SHADER_PATH="${CMAKE_SOURCE_DIR}/shader"
)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_libraries(
    Simulation 
    PRIVATE 
    stdc++exp
  )
endif()