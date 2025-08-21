add_subdirectory(expr)
add_subdirectory(IO)
add_subdirectory(graphics)
add_subdirectory(solver)
add_subdirectory(simulation)

find_package(Qt6 REQUIRED COMPONENTS Widgets)

add_executable(${PROJECT_NAME} main.cpp)


target_link_libraries(
  ${PROJECT_NAME}
  PRIVATE
  Simulation
  Qt6::Widgets
)

target_include_directories(
  ${PROJECT_NAME}
  PRIVATE
  ${INCLUDE_DIR}
)

# Qt deployment
set(QT_DEPLOY_TOOL ${QT_DIR}bin/windeployqt.exe)
add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
  COMMAND ${QT_DEPLOY_TOOL} "$<TARGET_FILE:ode_visualizer>"
  COMMENT "Running windeployqt..."
)
