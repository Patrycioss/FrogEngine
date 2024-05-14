#pragma once

#include <GLFW/glfw3.h>

namespace GlfwManager{

	inline GLFWwindow* Setup(){
	  glfwInit();

	  GLFWwindow* window = glfwCreateWindow(1200, 800, "Hahaha", nullptr, nullptr);
	  glfwMakeContextCurrent(window);
	  glfwSwapInterval(1); // Enable vsync

	  gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	  glfwShowWindow(window);
	  return window;
	}
	
	inline void PostFrame(GLFWwindow* window){
	  int display_w, display_h;
	  glfwGetFramebufferSize(window, &display_w, &display_h);
	  glad_glViewport(0, 0, display_w, display_h);

	  glfwSwapBuffers(window);
	}
}