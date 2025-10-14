cmake_minimum_required(VERSION 3.10)
project(conways_game_of_life)
set(CMAKE_CXX_FLAGS "-g3")

add_subdirectory(deps/glfw)

# Find OpenGL glfw3
find_package(OpenGL REQUIRED)
include_directories("include")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(src)
