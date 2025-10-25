#include "frac/mouse.hpp"
#include <GLFW/glfw3.h>
#include <iostream>

Mouse::Mouse() {
	this->curr_mouse_pos.resize(2);
	this->prev_mouse_pos.resize(2);
	this->mouse_diff.resize(2);

	this->curr_mouse_pos = {0, 0};
	this->prev_mouse_pos = {0, 0};
}

const std::vector<double>& Mouse::get_mouse_diff() {
	return this->mouse_diff;
}

Mouse::~Mouse() {
	 
}

void Mouse::poll_current_mouse_pos(GLFWwindow* window) {
	this->prev_mouse_pos = this->curr_mouse_pos;
	glfwGetCursorPos(window, &this->curr_mouse_pos[0], &this->curr_mouse_pos[1]);


	int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
	if (state == GLFW_PRESS) {
		this->mouse_diff[0] = this->curr_mouse_pos[0] - this->prev_mouse_pos[0];
		this->mouse_diff[1] = this->curr_mouse_pos[1] - this->prev_mouse_pos[1];
	}
	else {
		this->mouse_diff[0] = 0;
		this->mouse_diff[1] = 0;
	}
	std::cout << this->mouse_diff[0] << " " << this->mouse_diff[1] << "\n";
}
