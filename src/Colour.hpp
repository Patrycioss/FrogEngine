#pragma once

#include <cstdint>
#include <vec4.hpp>

namespace fe{
  struct Colour{
	int r;
	int g;
	int b;
	float a;
	
	Colour(int _r, int _g, int _b, float _a = 1.0f){
	  r = _r;
	  g = _g;
	  b = _b;
	  a = _a;
	}
	
	[[nodiscard]] glm::vec4 GetGLReady() const;
	
	const static Colour RED;
	const static Colour GREEN;
	const static Colour BLUE;
	const static Colour WHITE;
	const static Colour BLACK;
	
	[[nodiscard]] static Colour FromHex(int32_t _value); 
  };
  
  
}