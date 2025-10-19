#include "app.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

App::App (size_t width, size_t height) {
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	this->window = glfwCreateWindow(width, height, "Fractal Visualizer", NULL, NULL);
	if (this->window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	glfwMakeContextCurrent(this->window);
	gladLoadGL();

	std::string vertex_shader_path = "../src/mandel.vert";
	std::string frag_shader_path = "../src/mandel.frag";
	
	this->fractal_shader = new Shader(frag_shader_path, vertex_shader_path);
}

GLFWwindow* App::get_window() {
	return this->window;
}

Shader* App::get_shader() {
	return this->fractal_shader;
}
