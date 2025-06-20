
set(expr_src expr/tree.cpp expr/parser.cpp)

add_executable(${PROJECT_NAME} ${expr_src} main.cpp)

if(CMAKE_CXX_COMPILER_ID STREQUAL "GNU")
  target_link_libraries(${PROJECT_NAME} PRIVATE stdc++exp)
endif()

target_link_libraries(${PROJECT_NAME} PRIVATE SDL3::SDL3)

target_include_directories(${PROJECT_NAME} PUBLIC ${include_path})
