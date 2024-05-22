#pragma once

#include <box2d/box2d.h>

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include "ResourceManager.hpp"

namespace fe
{
  class GameTemplate {
   private:
	b2World world;
	ResourceManager resourceManager{};
	GLFWwindow* window = nullptr;

   protected:
	explicit GameTemplate(b2Vec2 _gravity) : world(_gravity) {};

	b2World& World = world;
	ResourceManager& ResourceManager = resourceManager;

   public:
	virtual void Start() = 0;
	virtual void Update(float _deltaTime) = 0;
	virtual void Stop() = 0;
  };
}