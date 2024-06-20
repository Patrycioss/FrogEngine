#include "src/data/Colour.hpp"

namespace fe
{
  const Colour Colour::RED = {255, 0, 0};
  const Colour Colour::GREEN = {0, 255, 0};
  const Colour Colour::BLUE = {0, 0, 255};
  const Colour Colour::WHITE = {255, 255, 255};
  const Colour Colour::BLACK = {0, 0, 0};

  Colour::Colour(int _r, int _g, int _b, float _a)
	  : r(_r), g(_g), b(_b), a(_a) {}

  Colour Colour::FromHex(int32_t _value) {
	Colour colour(
		(_value >> 16 & 0xFF) / 255,
		(_value >> 8 & 0xFF) / 255,
		(_value >> 0xFF & 0xFF) / 255
	);

	return colour;
  }

  glm::vec4 Colour::GetGLReady() const {
	return {(float) r / 255.0f, (float) g / 255.0f, (float) b / 255.0f, a};
  }
}