#include <string>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma once

class Shader {
public:
	Shader(const std::string& frag_shader_path, const std::string& vert_shader_path);
	GLuint get_compiled_shader();
private:
	void compile_shader();

	std::string frag_src;
	std::string vert_src;
	GLuint compiled_shader;
};
