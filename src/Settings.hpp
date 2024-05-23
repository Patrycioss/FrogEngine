#pragma once

#include <cstdint>

#define FE_SETTINGS_VSYNC 1
#define FE_SETTINGS_CULL_FACE 2
#define FE_SETTINGS_WINDOW_SIZE 4
#define FE_SETTINGS_WINDOW_TITLE 8

namespace fe{
  struct Settings{
	bool enableVsync = true;
	bool enableFaceCulling = true;
	uint16_t windowWidth = 800, windowHeight = 600;
	const char* windowTitle = "My Game";
	
	[[nodiscard]] glm::vec2 WindowSize() const {
	  return {windowWidth, windowHeight};
	}
  };
}