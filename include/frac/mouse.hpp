#include <GLFW/glfw3.h>
#include <vector>

#pragma once

class Mouse {
	public:
		Mouse();
		~Mouse();

	void poll_current_mouse_pos(GLFWwindow* window); 
	private:
		std::vector<double> curr_mouse_pos;
};
