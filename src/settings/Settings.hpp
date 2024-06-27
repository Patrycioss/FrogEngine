#pragma once

#include <box2d/box2d.h>
#include "data/Colour.hpp"

namespace fe{
  /**
   * Settings used by the Engine.
   */
  struct Settings{
	/**
	 * Whether to enable vertical sync. Synchronizes the games frame rate to the refresh rate of the monitor.
	 * Enabled by default.
	 */
	bool enableVsync = true;
	
	/**
	 * The width of the window.
	 */
	uint16_t windowWidth = 800; 
	
	/**
	 * The height of the window.
	 */
	uint16_t windowHeight = 600;
	
	/**
	 * The title that appears on the top of the window.
	 */
	const char* windowTitle = "My Game";
	
	/**
	 * Background colour, used to clear the screen at the start of every render loop.
	 */
	Colour backgroundColour = fe::Colour::BLUE;
	
	/**
	 * The near plane of the render projection. By default -1.
	 */
	float nearPlane = -1.0f;
	
	/**
	 * The far plane of the render projection. By default 1.
	 */
	float farPlane = 1.0f;
	
	/**
	 * How far the camera is zoomed in on the game. By default factor of 1.
	 */
	float zoom = 1.0f;
  };
}