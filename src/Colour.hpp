#pragma once

namespace fe{
  struct Colour{
	float r;
	float g;
	float b;
	float a;
	
	Colour(float _r, float _g, float _b, float _a = 1.0f){
	  r = _r;
	  g = _g;
	  b = _b;
	  a = _a;
	}
	
	const static Colour RED;
	const static Colour GREEN;
	const static Colour BLUE;
	const static Colour WHITE;
	const static Colour BLACK;
  };
  
  
}