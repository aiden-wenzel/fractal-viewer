#include "frac/shader.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstring>

#pragma once

class App {
public:
	App	(size_t width, size_t height);
	~App();
	void run();

	GLFWwindow* get_window();
	Shader* get_shader();
private:
	void initialize_verticies(); 
	GLFWwindow* window;
	Shader* fractal_shader;
	unsigned int VBO, VAO;
};
