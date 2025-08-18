add_library(
  Solver
  STATIC
  solver.cpp
  parser.cpp
)

target_include_directories(
  Solver
  PRIVATE
  ${INCLUDE_DIR}
)
