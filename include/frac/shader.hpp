#include <string>
#include <vector>
#include <unordered_map>

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#pragma once

class Shader {
public:
	Shader(const std::string& frag_shader_path, const std::string& vert_shader_path);
	GLuint get_compiled_shader();
	void set_float(const std::string& uniform_name, float val);
	void set_vec2(const std::string& uniform_name, const std::vector<float>& val);
private:
	void compile_shader();

	std::vector<std::string> uniforms = {"u_screen_dim", "u_offset", "u_scale"};
	std::unordered_map<std::string, GLint> uniform_locations;
	std::string frag_src;
	std::string vert_src;
	GLuint compiled_shader;
};
