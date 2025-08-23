cmake_minimum_required(VERSION 3.21)
project(ode_visualizer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Qt6
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)
set(CMAKE_PREFIX_PATH ${QT_DIR}lib/cmake)
find_package(Qt6 REQUIRED COMPONENTS 
  Widgets 
  OpenGLWidgets 
  Gui
)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

file(GLOB GUI_INC CMAKE_CONFIGURE_DEPENDS ${INCLUDE_DIR}/gui/*.hpp)

file(GLOB GUI_SRC CMAKE_CONFIGURE_DEPENDS ${SOURCE_DIR}/gui/*.cpp)
file(GLOB EXPR_SRC CMAKE_CONFIGURE_DEPENDS ${SOURCE_DIR}/expr/*.cpp)
file(GLOB SOLVER_SRC CMAKE_CONFIGURE_DEPENDS ${SOURCE_DIR}/solver/*.cpp)
file(GLOB SIMULATION_SRC CMAKE_CONFIGURE_DEPENDS ${SOURCE_DIR}/simulation/*.cpp)

message("Collected all source files: ")
message("GUI_INC: " ${GUI_INC})
message("GUI_SRC: " ${GUI_SRC})
message("EXPR_SRC: " ${EXPR_SRC})
message("SOLVER_SRC: " ${SOLVER_SRC})

add_executable(${PROJECT_NAME})

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${INCLUDE_DIR}
)

target_sources(${PROJECT_NAME} PRIVATE 
  ${SOURCE_DIR}/main.cpp 
  ${GUI_INC}
  ${GUI_SRC} 
  ${EXPR_SRC}
  ${SOLVER_SRC}
  ${SIMULATION_SRC}
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  Qt6::Widgets
  Qt6::OpenGLWidgets
  Qt6::Gui
)

# Qt deployment
set(QT_DEPLOY_TOOL ${QT_DIR}bin/windeployqt.exe)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${QT_DEPLOY_TOOL} "$<TARGET_FILE:ode_visualizer>"
  COMMENT "Running windeployqt..."
)