#include <string>

#pragma once

class Shader {
public:
	Shader(const std::string& frag_shader_path, const std::string& vert_shader_path);
private:
	std::string frag_src;
	std::string vert_src;
};
