#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <cassert>
#include <getopt.h>

#include "gl_helpers.hpp"

// settings
float SCR_WIDTH = 900.0f;
float SCR_HEIGHT = 900.0f;
float scale = 1.0f;

void fill_cycle_values(std::vector<float>& values, size_t n, float lower, float upper);

int main(int argc, char** argv) {
	auto window = initialize_window(SCR_WIDTH, SCR_HEIGHT);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	
	std::string vertex_shader_path = "../src/mandel.vert";
	std::string frag_shader_path = "../src/julia.frag";
	std::string vertex_shader_source;
	std::string fragment_shader_source;
	read_shader_file(vertex_shader_path, vertex_shader_source);
	read_shader_file(frag_shader_path, fragment_shader_source);
	auto shader_program = compile_shader_program(vertex_shader_source.c_str(), fragment_shader_source.c_str());

	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	}; 

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 

	glUseProgram(shader_program);
	GLint u_screen_dim_loc = glGetUniformLocation(shader_program, "u_screen_dim");
	glUniform2f(u_screen_dim_loc, SCR_WIDTH, SCR_HEIGHT);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	GLint u_offset_loc = glGetUniformLocation(shader_program, "u_offset");
	std::vector<float> offset = {0.0f, 0.0f};
	std::vector<double> curr_mouse_pos = {0.0f, 0.0f};
	std::vector<double> prev_mouse_pos = {0.0f, 0.0f};
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);
	glfwSetScrollCallback(window, scroll_callback);

	GLint u_scale_loc = glGetUniformLocation(shader_program, "u_scale");

	size_t num_values = 1000;
	size_t curr_value = 0;
	std::vector<float> cycle_values(num_values);
	fill_cycle_values(cycle_values, num_values, 0.0, 2 * M_PI);
	GLint u_a_loc = glGetUniformLocation(shader_program, "u_a");

	while (!glfwWindowShouldClose(window)) {
		glfwGetCursorPos(window, &curr_mouse_pos[0], &curr_mouse_pos[1]);	

		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS) {
			offset[0] = offset[0] - (curr_mouse_pos[0] - prev_mouse_pos[0]);
			offset[1] = offset[1] + (curr_mouse_pos[1] - prev_mouse_pos[1]);
		}

		if (curr_value == 1001) {
			curr_value = 0;
		}
		glUniform1f(u_a_loc, cycle_values[curr_value]);
		curr_value++;

		glUniform2f(u_offset_loc, offset[0], offset[1]);
		glUniform1f(u_scale_loc, scale);
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		prev_mouse_pos = curr_mouse_pos;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shader_program);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

void fill_cycle_values(std::vector<float>& values, size_t n, float lower, float upper) {
	assert(n > 0);
	float step = (upper - lower) / (double)n;

	for (size_t i = 0; i < n; i++) {
		values[i] = lower + float(i) * step;
	}
}
