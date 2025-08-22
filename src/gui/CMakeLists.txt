add_library(
  gui
  STATIC
  ${INCLUDE_DIR}/gui/MainWindow.hpp
  MainWindow.cpp
)

target_include_directories(
  gui
  PRIVATE
  ${INCLUDE_DIR}
)

target_link_libraries(
  gui
  PRIVATE
  Qt6::Widgets
  Qt6::OpenGLWidgets
  Qt6::Gui
)
