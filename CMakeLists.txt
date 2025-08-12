cmake_minimum_required(VERSION 3.10)
project(conways_game_of_life)
set(CXXFLAGS "-g3")

# Find OpenGL glfw3
find_package(OpenGL REQUIRED)
find_package(glfw3 REQUIRED)
include_directories("include")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(src)
