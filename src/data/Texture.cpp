#include "src/data/Texture.hpp"

#include <glad/glad.h>

namespace fe
{
  Texture::Texture(uint32_t _imageFormat, bool _hardPixels)
	  : imageFormat(_imageFormat) {
	glGenTextures(1, &ID);
  }

  const uint32_t& Texture::GetID() const {
	return ID;
  }

  b2Vec2 Texture::GetSize() const {
	return {(float)width, (float)height};
  }

  void Texture::Generate(int _imageWidth, int _imageHeight, unsigned char* _data) {
	width = _imageWidth;
	height = _imageHeight;

	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, (int)imageFormat, (int)width, (int)height, 0, imageFormat, GL_UNSIGNED_BYTE, _data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	
	int pixelMode = GL_LINEAR;
	if (hardPixels){
	  pixelMode = GL_NEAREST;
	}
	
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, pixelMode);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, pixelMode);

	glBindTexture(GL_TEXTURE_2D, 0);
  }

  void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, ID);
  }
}

