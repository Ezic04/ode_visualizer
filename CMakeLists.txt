cmake_minimum_required(VERSION 3.21)
project(ode_visualizer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


set(CMAKE_PREFIX_PATH ${QT_DIR}lib/cmake)

find_package(Qt6 REQUIRED COMPONENTS Widgets OpenGLWidgets Gui)

set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)


# build GLAD
set(GLAD_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/glad)
set(GLAD_INCLUDE_DIR ${GLAD_SOURCE_DIR}/include)
add_subdirectory(${GLAD_SOURCE_DIR})
# build GLFW
set(GLFW_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/glfw)
set(GLFW_INCLUDE_DIR ${GLFW_SOURCE_DIR}/include)
add_subdirectory(${GLFW_SOURCE_DIR})
# link GLM
set(GLM_SOURCE_DIR ${CMAKE_SOURCE_DIR}/deps/glm) # src and incl dirs are the same
add_subdirectory(${GLM_SOURCE_DIR})



set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

add_subdirectory(src)

