#include "frac/app.hpp"
#include "frac/mouse.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cmath>
#include <iostream>

std::vector<double> screen_dim = {900, 900};
std::vector<double> center = {-0.743643887037151, 0.131825904205330};

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
	glUseProgram(this->fractal_shader->get_compiled_shader());

	this->initialize_verticies();
}

App::~App() {
	delete this->fractal_shader;
}

void App::run() {
	
	// Pass in screen dimensions.
	this->fractal_shader->set_vec2("u_screen_dim", screen_dim);
	this->fractal_shader->set_vec2("u_center", center);

	int loop_count = 0;
	float step_size = 0.01;
	while (!glfwWindowShouldClose(this->window)) {
		this->fractal_shader->set_float("zoom", exp(-loop_count*step_size));
		loop_count++;
		/*
		this->mouse.poll_current_mouse_pos(this->window);
		offset[0] -= mouse.get_mouse_diff()[0];
		offset[1] += mouse.get_mouse_diff()[1]; // Mouse position and panning
		*/

		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(this->VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(this->window);
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &this->VAO);
	glDeleteBuffers(1, &this->VBO);
	glDeleteProgram(this->fractal_shader->get_compiled_shader());
}

void App::initialize_verticies() {
	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	}; 

	glGenVertexArrays(1, &this->VAO);
	glGenBuffers(1, &this->VBO);
	glBindVertexArray(this->VAO);
	glBindBuffer(GL_ARRAY_BUFFER, this->VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 
}

GLFWwindow* App::get_window() {
	return this->window;
}

Shader* App::get_shader() {
	return this->fractal_shader;
}
