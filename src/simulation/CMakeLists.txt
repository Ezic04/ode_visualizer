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

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_libraries(
    Simulation 
    PRIVATE 
    stdc++exp
  )
endif()