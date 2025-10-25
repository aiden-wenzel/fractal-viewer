#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstring>
#include <cmath>
#include <cassert>
#include <getopt.h>

#include "frac/app.hpp"

int main(int argc, char** argv) {
	
	float width = 900.0f;
	float height= 900.0f;
	App application(width, height);
	application.run();
	glfwTerminate();
	return 0;
}
