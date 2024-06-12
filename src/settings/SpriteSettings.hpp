#pragma once

#include <box2d/box2d.h>

#include "src/data/Colour.hpp"

namespace fe{
  
  /**
   * Settings necessary to render a sprite to the screen.
   */
  struct SpriteSettings{
	/**
	 * Position of the sprite on the screen.
	 */
	b2Vec2 position{};
	
	/**
	 * Angle of rotation of the sprite in radians.
	 */
	float angle{};
	
	/**
	 * Dimensions of the sprite.
	 */
	b2Vec2 size{};
	
	/**
	 * Colour that is applied on top of the sprites colours.
	 * Keep white for normal colour.
	 */
	Colour colour = Colour::WHITE;
	
	/**
	 * Whether to flip the sprite vertically.
	 */
	bool flipVertical = false;
	
	/**
	 * Whether to flip the sprite horizontally.
	 */
	bool flipHorizontal = false;
  };
}