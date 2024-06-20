#include "src/core/Time.hpp"

#include <GLFW/glfw3.h>

namespace fe
{
  float Time::GetTimeSeconds() {
	return (float) glfwGetTime();
  }
}