#include "frac/app.hpp"
#include "frac/mouse.hpp"

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>

float SCR_WIDTH = 900.0f;
float SCR_HEIGHT = 900.0f;
float scale = 4.0f;

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
	this->fractal_shader->set_vec2("u_screen_dim", {SCR_WIDTH, SCR_HEIGHT});

	// pass in cursor information.
	std::vector<double> offset = {-SCR_WIDTH/2, -SCR_HEIGHT/2};

	while (!glfwWindowShouldClose(this->window)) {
		this->mouse.poll_current_mouse_pos(this->window);
		offset[0] -= mouse.get_mouse_diff()[0];
		offset[1] += mouse.get_mouse_diff()[1]; // Mouse position and panning

		this->fractal_shader->set_vec2("u_offset", offset);
		this->fractal_shader->set_float("u_scale", scale);
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
