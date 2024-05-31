#pragma once

#include <cstdint>

namespace fe{
  struct Settings{
	bool enableVsync = true;
	bool enableFaceCulling = true;
	uint16_t windowWidth = 800, windowHeight = 600;
	const char* windowTitle = "My Game";
	b2Vec2 gravity = {0,0};
	
	[[nodiscard]] glm::vec2 WindowSize() const {
	  
	  return {windowWidth, windowHeight};
	}
	
	enum{
	  VSYNC = 1 << 0,
	  CULL_FACE = 1 << 1,
	  WINDOW_SIZE = 1 << 2,
	  WINDOW_TITLE = 1 << 3,
	  GRAVITY = 1 << 4,
	};
  };
}