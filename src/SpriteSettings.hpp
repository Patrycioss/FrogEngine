#pragma once

#include <box2d/box2d.h>

#include "Colour.hpp"

namespace fe{
  struct SpriteSettings{
	b2Vec2 position{};
	float angle{};
	b2Vec2 size{};
	Colour colour = Colour::WHITE;
  };
}