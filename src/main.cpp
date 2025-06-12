#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <fstream>
#include <vector>

// settings
float SCR_WIDTH = 900.0f;
float SCR_HEIGHT = 900.0f;


GLFWwindow* initializeWindow(size_t width, size_t height);
GLuint compileShadarProgram(const char* vertexShaderSource, const char* fragmentShaderSource);
void readShaderFile(const std::string& filePath, std::string& shaderString);
static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);

int main() {
	auto window = initializeWindow(SCR_WIDTH, SCR_HEIGHT);

	glfwMakeContextCurrent(window);
	gladLoadGL(glfwGetProcAddress);
	
	std::string vertexShaderSource;
	std::string fragmentShaderSource;
	readShaderFile("../src/mandel.vert", vertexShaderSource);
	readShaderFile("../src/mandel.frag", fragmentShaderSource);
	auto shaderProgram = compileShadarProgram(vertexShaderSource.c_str(), fragmentShaderSource.c_str());
	// set up vertex data (and buffer(s)) and configure vertex attributes
	// ------------------------------------------------------------------
	float vertices[] = {
		-1.0f, -1.0f, 0.0f,
		-1.0f, 1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		-1.0f, -1.0f, 0.0f,
		1.0f, 1.0f, 0.0f,
		1.0f, -1.0f, 0.0f
	}; 

	unsigned int VBO, VAO;
	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);
	glBindVertexArray(VAO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, 0); 
	glBindVertexArray(0); 

	glUseProgram(shaderProgram);
	GLint uniform_loc = glGetUniformLocation(shaderProgram, "screen_dim");
	glUniform2f(uniform_loc, SCR_WIDTH, SCR_HEIGHT);

	glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
	GLint u_offset_loc = glGetUniformLocation(shaderProgram, "u_offset");
	std::vector<float> offset = {0.0f, 0.0f};
	std::vector<double> curr_mouse_pos = {0.0f, 0.0f};
	std::vector<double> prev_mouse_pos = {0.0f, 0.0f};
	glfwSetCursorPosCallback(window, cursor_position_callback);
	glfwSetMouseButtonCallback(window, mouse_button_callback);

	while (!glfwWindowShouldClose(window)) {
		glfwGetCursorPos(window, &curr_mouse_pos[0], &curr_mouse_pos[1]);	

		int state = glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT);
		if (state == GLFW_PRESS) {
			offset[0] = offset[0] - (curr_mouse_pos[0] - prev_mouse_pos[0]);
			offset[1] = offset[1] + (curr_mouse_pos[1] - prev_mouse_pos[1]);
		}

		glUniform2f(u_offset_loc, offset[0], offset[1]);
		// render
		// ------
		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		glBindVertexArray(VAO);
		glDrawArrays(GL_TRIANGLES, 0, 6);

		prev_mouse_pos = curr_mouse_pos;
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	// optional: de-allocate all resources once they've outlived their purpose:
	// ------------------------------------------------------------------------
	glDeleteVertexArrays(1, &VAO);
	glDeleteBuffers(1, &VBO);
	glDeleteProgram(shaderProgram);

	// glfw: terminate, clearing all previously allocated GLFW resources.
	// ------------------------------------------------------------------
	glfwTerminate();
	return 0;
}

GLFWwindow* initializeWindow(size_t width, size_t height) {

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	GLFWwindow* window = glfwCreateWindow(SCR_WIDTH, SCR_HEIGHT, "LearnOpenGL", NULL, NULL);
	if (window == NULL)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		exit(-1);
	}

	return window;
}

GLuint compileShadarProgram(const char* vertexShaderSource, const char* fragmentShaderSource) {
	// vertex shader
	unsigned int vertexShader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);
	// check for shader compile errors
	int success;
	char infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	unsigned int fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
	glCompileShader(fragmentShader);
	// check for shader compile errors
	glGetShaderiv(fragmentShader, GL_COMPILE_STATUS, &success);
	if (!success)
	{
		glGetShaderInfoLog(fragmentShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::FRAGMENT::COMPILATION_FAILED\n" << infoLog << std::endl;
	}
	// link shaders
	unsigned int shaderProgram = glCreateProgram();
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);
	// check for linking errors
	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success) {
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::PROGRAM::LINKING_FAILED\n" << infoLog << std::endl;
	}
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);

	return shaderProgram;
}

void readShaderFile(const std::string& filePath, std::string& shaderString) {
	std::fstream fileStream(filePath);
	if (!fileStream.is_open()) {
		std::cout << "Could not open file " << filePath << "\n";
		exit(-2);
	}

	std::string tmp;
	while (std::getline(fileStream, tmp)) {
		shaderString.append(tmp + "\n");
	}
	
	fileStream.close();
}

static void cursor_position_callback(GLFWwindow* window, double xpos, double ypos) {

}

void mouse_button_callback(GLFWwindow* window, int button, int action, int mods)
{
 //    if (button == GLFW_MOUSE_BUTTON_RIGHT && action == GLFW_PRESS) {
	// 	std::cout << "Pressing\n";
	// }
}
