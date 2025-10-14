#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <cstring>

class App {
public:
	App	(size_t width, size_t height);

	GLFWwindow* get_window();
private:
	GLFWwindow* window;
};
