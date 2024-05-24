#pragma once

#include <cstdint>

namespace fe{
  struct Settings{
	bool enableVsync = true;
	bool enableFaceCulling = true;
	uint16_t windowWidth = 800, windowHeight = 600;
	const char* windowTitle = "My Game";
	
	[[nodiscard]] glm::vec2 WindowSize() const {
	  return {windowWidth, windowHeight};
	}
	
	const static uint16_t VSYNC = 1;
	const static uint16_t CULL_FACE = 2;
	const static uint16_t WINDOW_SIZE = 4;
	const static uint16_t WINDOW_TITLE = 8;
  };
}