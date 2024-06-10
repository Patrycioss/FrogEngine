#pragma once

#include <string>
#include <cstring>
#include <iostream>
#include <box2d/box2d.h>

namespace fe
{
  class Texture {
   private:
	uint32_t ID{};
	int width = 0;
	int height = 0;
	uint32_t internalFormat;
	uint32_t imageFormat;

   public:
	explicit Texture(uint32_t _imageFormat, uint32_t _internalFormat);
	[[nodiscard]] const uint32_t& GetID() const;
	[[nodiscard]] b2Vec2 GetSize() const;
	void Generate(int _imageWidth, int _imageHeight, unsigned char* _data);
	void Generate(int _imageWidth, int _imageHeight, unsigned char* _data, int _x, int _y, int _frameWidth, int _frameHeight);
	void Bind() const;
  };
}