#pragma once

#include <cstdint>
#include <glm.hpp>

namespace fe
{
  /**
   * Colour expressed in RGB 255 format.
   */
  struct Colour {
	const static Colour RED;
	const static Colour GREEN;
	const static Colour BLUE;
	const static Colour WHITE;
	const static Colour BLACK;

	int r;
	int g;
	int b;

	/**
	 * Alpha transparency ranges from 0f for transparent to 1f for solid.
	 */
	float a;

	/**
	 * Creates a colour from using 0-255 rgb values. Alpha transparency ranges from 0f for transparent to 1f for solid.
	 */
	Colour(int _r, int _g, int _b, float _a = 1.0f);

	/**
	 * @return The colour in RGB 0f to 1f format for use in shaders. 
	 */
	[[nodiscard]] glm::vec4 GetGLReady() const;

	/**
	 * @return A RGB 255 colour from Hex. 
	 */
	[[nodiscard]] static Colour FromHex(int32_t _value);
  };
}