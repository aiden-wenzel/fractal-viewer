cmake_minimum_required(VERSION 3.10)
project(conways_game_of_life)

# fetch google test
include(FetchContent)
set(CXXFLAGS "-g3")

# GLFW
FetchContent_Declare(
	glfw
	URL https://github.com/glfw/glfw/archive/refs/tags/3.4.tar.gz
)

FetchContent_makeAvailable(glfw)

# GLAD
FetchContent_Declare(
	glad
	GIT_REPOSITORY https://github.com/Dav1dde/glad
	GIT_TAG        v2.0.6
	GIT_SHALLOW    TRUE
	GIT_PROGRESS   TRUE
)

FetchContent_GetProperties(glad)
if(NOT glad_POPULATED)
	message("Fetching glad")
	FetchContent_MakeAvailable(glad)

	add_subdirectory("${glad_SOURCE_DIR}/cmake" glad_cmake)
	glad_add_library(glad REPRODUCIBLE EXCLUDE_FROM_ALL LOADER API gl:core=4.6 EXTENSIONS GL_ARB_bindless_texture GL_EXT_texture_compression_s3tc)
endif()

include_directories("./build/_deps/glfw-src/include/")
include_directories("./build/_deps/glfw-src/deps/")

set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
add_subdirectory(src)
