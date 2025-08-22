add_subdirectory(expr)
add_subdirectory(IO)
add_subdirectory(graphics)
add_subdirectory(solver)
add_subdirectory(simulation)
add_subdirectory(gui)

# set(GUI_SRC
#   gui/MainWindow.cpp
#   ../include/gui/MainWindow.hpp
# )
# message(gui_src ${GUI_SRC})

add_executable(
  ${PROJECT_NAME}
  main.cpp
  # ${GUI_SRC}
)

target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  gui
  Simulation
  Qt6::Widgets
  Qt6::OpenGLWidgets
  Qt6::Gui
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${INCLUDE_DIR}
)

# include

# Qt deployment
set(QT_DEPLOY_TOOL ${QT_DIR}bin/windeployqt.exe)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${QT_DEPLOY_TOOL} "$<TARGET_FILE:ode_visualizer>"
  COMMENT "Running windeployqt..."
)
