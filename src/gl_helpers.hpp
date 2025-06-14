#include <glad/gl.h>
#include <GLFW/glfw3.h>

#include <string>

GLFWwindow* initialize_window(size_t width, size_t height);
GLuint compile_shader_program(const char* vertex_shader_source, const char* fragment_shader_source);
void read_shader_file(const std::string& filePath, std::string& shaderString);
void cursor_position_callback(GLFWwindow* window, double xpos, double ypos);
void mouse_button_callback(GLFWwindow* window, int button, int action, int mods);
void scroll_callback(GLFWwindow* window, double xoffset, double yoffset);
