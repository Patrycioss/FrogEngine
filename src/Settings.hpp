#pragma once

#include <cstdint>
#include <box2d/box2d.h>

namespace fe{
  struct Settings{
	bool enableVsync = true;
	bool enableFaceCulling = true;
	uint16_t windowWidth = 800, windowHeight = 600;
	const char* windowTitle = "My Game";
	b2Vec2 gravity = {0,0};
  };
}