#include "gl_helpers.hpp"

#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>

extern float scale;

GLFWwindow* initialize_window(size_t width, size_t height) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(width, height, "Fractal Visualizer", NULL, NULL);
	if (window == NULL) {
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	return window;
}

GLuint compile_shader_program(const char* vertex_shader_source, const char* fragment_shader_source) {
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertex_shader_source, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader_source, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	unsigned int shader_program = glCreateProgram();
	glAttachShader(shader_program, vertexShader);
	glAttachShader(shader_program, fragmentShader);
	glLinkProgram(shader_program);
	// check for linking errors
	glGetProgramiv(shader_program, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shader_program, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shader_program;
}

void read_shader_file(const std::string& filePath, std::string& shaderString) {
	std::fstream fileStream(filePath);
	if (!fileStream.is_open()) {
		std::cout << "Could not open file " << filePath << "\n";
		exit(-2);
	}

	std::string tmp;
	while (std::getline(fileStream, tmp)) {
		shaderString.append(tmp + "\n");
	}
	
	fileStream.close();
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods) {
 //    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
	// 	std::cout << "Pressing\n";
	// }
}

void scroll_callback(GLFWwindow* window, double xoffset, double yoffset) {
    if (yoffset > 0) {
        // Scrolled up (zooming in)
		scale *= 0.8;
    } else if (yoffset < 0) {
        // Scrolled down (zooming out)
		scale *= 1.2;
    }
}

