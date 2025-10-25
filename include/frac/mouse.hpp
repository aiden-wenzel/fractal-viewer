#include <GLFW/glfw3.h>
#include <vector>

#pragma once

class Mouse {
	public:
		Mouse();
		~Mouse();

	void poll_current_mouse_pos(GLFWwindow* window); 
	const std::vector<double>& get_mouse_diff();
	private:
		std::vector<double> curr_mouse_pos;
		std::vector<double> prev_mouse_pos;
		std::vector<double> mouse_diff;
};
