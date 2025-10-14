#include <iostream>
#include <fstream>

#include "shader.hpp"

Shader::Shader(const std::string& frag_shader_path, const std::string& vert_shader_path) {
	// Read in fragment shader.
	std::fstream frag_stream(frag_shader_path);
	if (!frag_stream.is_open()) {
		std::cout << "Could not open file " << frag_shader_path << "\n";
		exit(-2);
	}

	std::string tmp;
	while (std::getline(frag_stream, tmp)) {
		this->frag_src.append(tmp + "\n");
	}
	
	frag_stream.close();

	// Read in vertex shader.
	std::fstream vert_stream(vert_shader_path);
	if (!vert_stream.is_open()) {
		std::cout << "Could not open file " << vert_shader_path << "\n";
		exit(-2);
	}

	while (std::getline(vert_stream, tmp)) {
		this->vert_src.append(tmp + "\n");
	}
	
	vert_stream.close();

	this->compile_shader();
}

GLuint Shader::get_compiled_shader() {
	return this->compiled_shader;
}

void Shader::compile_shader() {
	// vertex shader
	const char* vert_src = this->vert_src.c_str();
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vert_src, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success) {
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	const char* frag_src = this->frag_src.c_str();
	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &frag_src, NULL);
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

	this->compiled_shader = shader_program;
}
