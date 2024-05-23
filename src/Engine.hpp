﻿#pragma once

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
	static bool initCalled;
	static Settings currentSettings;

   public:
	/* Applies all settings.*/
	static void ApplyAllSettings(const Settings& _settings);

	/* Applies settings selected with the flags.*/
	static void ApplySettings(const Settings& _settings, uint16_t _flags);

	/* Initialize the game using a GameTemplate */
	static void Initialize(GameTemplate& _gameTemplate);
	
	/* Stop the game. */
	static void Stop();
	
	/* Settings that are currently in use by the engine. */
	static const Settings& CurrentSettings;
  };
}