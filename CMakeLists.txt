cmake_minimum_required(VERSION 3.16)
project(ode_visualizer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

# build GLAD
set(GLAD_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/glad)
set(GLAD_INCLUDE_DIR ${GLAD_SOURCE_DIR}/include)
add_subdirectory(${GLAD_SOURCE_DIR})

# build GLFW
set(GLFW_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/glfw)
set(GLFW_INCLUDE_DIR ${GLFW_SOURCE_DIR}/include)
add_subdirectory(${GLFW_SOURCE_DIR})

set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)
