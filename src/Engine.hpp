#pragma once

#include "box2d/box2d.h"

#define GLFW_INCLUDE_NONE
#include "GLFW/glfw3.h"

#include "ResourceManager.hpp"

namespace FrogEngine
{
  class Engine {
   private:
	b2World world;
	ResourceManager resourceManager{};
	GLFWwindow* window = nullptr;

   protected:
	explicit Engine(b2Vec2 _gravity) : world(_gravity) {};
	
	b2World& World = world;
	ResourceManager& ResourceManager = resourceManager;
	
   public:
	virtual void OnStart() = 0;
	virtual void OnUpdate(float _deltaTime) = 0;
	virtual void OnStop() = 0;

  	void Start();
  	void Stop();
  };
}