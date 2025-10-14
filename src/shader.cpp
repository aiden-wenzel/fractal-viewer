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

	while (std::getline(frag_stream, tmp)) {
		this->vert_src.append(tmp + "\n");
	}
	
	vert_stream.close();
}
