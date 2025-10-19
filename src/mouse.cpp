#include "frac/mouse.hpp"
#include <GLFW/glfw3.h>

Mouse::Mouse() {
	this->curr_mouse_pos.resize(2);
}

Mouse::~Mouse() {
	 
}

void Mouse::poll_current_mouse_pos(GLFWwindow* window) {
	glfwGetCursorPos(window, &this->curr_mouse_pos[0], &this->curr_mouse_pos[1]);
}
