#include "GlfwManager.hpp"

#include <glad/glad.h>

namespace GlfwManager
{
  GLFWwindow* Setup() {
	glfwInit();

	GLFWwindow* window = glfwCreateWindow(1200, 800, "Hahaha", nullptr, nullptr);
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1); // Enable vsync

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glfwShowWindow(window);
	return window;
  }

  void PostFrame(GLFWwindow* _window) {
	int display_w, display_h;
	glfwGetFramebufferSize(_window, &display_w, &display_h);
	glad_glViewport(0, 0, display_w, display_h);

	glfwSwapBuffers(_window);
  }
}