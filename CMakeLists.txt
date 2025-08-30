cmake_minimum_required(VERSION 3.21)
project(ode_visualizer)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(CMAKE_PREFIX_PATH ${QT_DIR}/lib/cmake)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTORCC ON)

set(SOURCE_DIR ${CMAKE_SOURCE_DIR}/src)
set(INCLUDE_DIR ${CMAKE_SOURCE_DIR}/include)

find_package(Qt6 REQUIRED COMPONENTS
  Widgets
  OpenGLWidgets
  Gui
)

add_library(backend)
target_include_directories(backend PRIVATE ${INCLUDE_DIR})
set(BACKEND_SOURCE_DIR ${SOURCE_DIR}/backend)
target_sources(backend PRIVATE
  ${BACKEND_SOURCE_DIR}/expr.cpp
  ${BACKEND_SOURCE_DIR}/parser.cpp
  ${BACKEND_SOURCE_DIR}/solver.cpp
  ${BACKEND_SOURCE_DIR}/simulation.cpp
)



file(GLOB GUI_INC CMAKE_CONFIGURE_DEPENDS ${INCLUDE_DIR}/gui/*.hpp)
file(GLOB GUI_SRC CMAKE_CONFIGURE_DEPENDS ${SOURCE_DIR}/gui/*.cpp)
set(GUI_LIB
  Qt6::Widgets
  Qt6::OpenGLWidgets
  Qt6::Gui
)


add_executable(${PROJECT_NAME})
target_include_directories(${PROJECT_NAME} PRIVATE ${INCLUDE_DIR})
target_sources(${PROJECT_NAME} PRIVATE ${SOURCE_DIR}/main.cpp ${GUI_SRC} ${GUI_INC})
target_link_libraries(${PROJECT_NAME} PRIVATE backend ${GUI_LIB})


# Qt deployment
set(QT_DEPLOY_TOOL ${QT_DIR}/bin/windeployqt.exe)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${QT_DEPLOY_TOOL} "$<TARGET_FILE:ode_visualizer>"
  COMMENT "Running windeployqt..."
)
