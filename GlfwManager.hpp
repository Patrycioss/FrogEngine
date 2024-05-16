#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

namespace GlfwManager
{

  GLFWwindow* Setup();

  void PostFrame(GLFWwindow* _window);
}