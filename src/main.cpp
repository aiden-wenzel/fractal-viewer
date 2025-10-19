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


int main(int argc, char** argv) {
	
	float width = 900.0f;
	float height= 900.0f;
	App application(width, height);
	application.run();
	glfwTerminate();
	return 0;
}
