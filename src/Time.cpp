#include "Time.hpp"

#include <glfw/glfw3.h>

namespace fe
{
  float Time::GetTimeSeconds() {
	return (float) glfwGetTime();
  }
}