#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstring>
#include <vector>
#include <cmath>
#include <cassert>
#include <getopt.h>

#include "frac/gl_helpers.hpp"
#include "shader.hpp"
#include "app.hpp"

// settings
float SCR_WIDTH = 900.0f;
float SCR_HEIGHT = 900.0f;
float scale = 4.0f;

int main(int argc, char** argv) {
	App application(SCR_WIDTH, SCR_HEIGHT);
	glUseProgram(application.get_shader()->get_compiled_shader());

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

	// Pass in screen dimensions.
	application.get_shader()->set_vec2("u_screen_dim", {SCR_WIDTH, SCR_HEIGHT});

	// pass in cursor information.
	std::vector<float> offset = {-SCR_WIDTH/2, -SCR_HEIGHT/2};

	while (!glfwWindowShouldClose(application.get_window())) {
		// Mouse position and panning
		application.get_shader()->set_vec2("u_offset", offset);
		application.get_shader()->set_float("u_scale", scale);
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		glfwSwapBuffers(application.get_window());
		glfwPollEvents();
	}

	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(application.get_shader()->get_compiled_shader());

	glfwTerminate();
	return 0;
}
