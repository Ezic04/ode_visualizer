cmake_minimum_required(VERSION 3.16)
project("odeVisualizer")
set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON CACHE INTERNAL "")

set(include_path ${CMAKE_SOURCE_DIR}/include)
add_subdirectory(src)
