#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <box2d/box2d.h>
#include <glm.hpp>

#include "GameTemplate.hpp"

namespace fe
{
  class Engine {
   private:
	static GLFWwindow* window;
	static b2World world;

   public:
	static void Init(GameTemplate& _gameTemplate);
	static void Stop();
  };
}