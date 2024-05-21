#pragma once

#include <string>
#include <cstring>
#include <iostream>

#include "vec2.hpp"

namespace fe
{
  class Texture {
   private:
	uint32_t ID{};
	uint32_t width = 0;
	uint32_t height = 0;
	uint32_t internalFormat;
	uint32_t imageFormat;

   public:
	explicit Texture(uint32_t _imageFormat, uint32_t _internalFormat);
	[[nodiscard]] const uint32_t& GetID() const;;
	void Generate(unsigned int _width, unsigned int _height, unsigned char* _data);
	void Bind() const;
  };
}