add_executable(main main.cpp app.cpp shader.cpp ../deps/glad/glad.c)
target_link_libraries(main glfw)
