add_subdirectory(expr)
add_subdirectory(graphics)
set(TEST_SRC tests/eval_test.cpp)

add_executable(${PROJECT_NAME} ${TEST_SRC} main.cpp)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_libraries(
    ${PROJECT_NAME} 
      PRIVATE 
      stdc++exp
  )
endif()

target_link_libraries(
  ${PROJECT_NAME} 
  PRIVATE 
  Expr
  Graphics
  GLAD
  glm::glm
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${INCLUDE_DIR}
  ${GLAD_INCLUDE_DIR}
  ${GLM_SOURCE_DIR}
)
