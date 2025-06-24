add_library(
  Expr
  STATIC
  dynamic.cpp
  parser.cpp
)

target_include_directories(
  Expr
  PRIVATE
  ${INCLUDE_DIR}
)
