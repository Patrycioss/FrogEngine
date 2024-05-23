#pragma once

#include <box2d/box2d.h>

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include "ResourceManager.hpp"
#include "Settings.hpp"

namespace fe
{
  class GameTemplate {
   private:
	ResourceManager resourceManager{};
	GLFWwindow* window = nullptr;

   protected:
	ResourceManager& ResourceManager = resourceManager;
	
	/* Settings for the engine. */
	Settings settings{};

	/* Applies all settings in the settings member.*/
	void ApplyAllSettings() const;

	/* Applies settings selected with the flags.*/
	void ApplySettings(uint8_t _flags) const;

   public:
	/* Called when the game is started by the engine. */
	virtual void Start() = 0;
	
	/* Called every frame by the engine. */
	virtual void Update(float _deltaTime) = 0;
	
	/* Called at the end of the game. */
	virtual void Stop() = 0;

	/* Settings that the engine can use. */
	const Settings& Settings = settings;
  };
}