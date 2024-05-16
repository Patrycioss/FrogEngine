#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include "IGame.hpp"
#include "ResourceManager.hpp"

namespace FrogEngine
{
  class Engine {
   private:
	GLFWwindow* window = nullptr;
	ResourceManager resourceManager{};

   public:
	void Start(IGame* _game);
	void Stop();
	ResourceManager& ResourceManager = resourceManager;
  };
}