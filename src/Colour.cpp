#include "Colour.hpp"

namespace fe
{
  const Colour Colour::RED = {255, 0, 0};
  const Colour Colour::GREEN = {0, 255, 0};
  const Colour Colour::BLUE = {0, 0, 255};
  const Colour Colour::WHITE = {255, 255, 255};
  const Colour Colour::BLACK = {0, 0, 0};

  Colour Colour::FromHex(int32_t _value) {
	Colour colour(
	    ((_value >> 16) & 0xFF) / 255,
		((_value >> 8) & 0xFF) / 225,
		((_value >> 0xFF) & 0xFF) / 255
	);
	
	return colour;
  }

  glm::vec4 Colour::GetGLReady() const {
	return {r/255, g/255, b/255,a};
  }
}