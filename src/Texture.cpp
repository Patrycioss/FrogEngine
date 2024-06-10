#include "Texture.hpp"

#include <glad/glad.h>

namespace fe
{
  Texture::Texture(uint32_t _imageFormat, uint32_t _internalFormat)
	  : imageFormat(_imageFormat), internalFormat(_internalFormat) {
	glGenTextures(1, &ID);
  }

  const uint32_t& Texture::GetID() const {
	return ID;
  }

  void Texture::Generate(int _imageWidth, int _imageHeight, unsigned char* _data) {
	width = _imageWidth;
	height = _imageHeight;

	glBindTexture(GL_TEXTURE_2D, ID);
	glTexImage2D(GL_TEXTURE_2D, 0, (int)internalFormat, (int)width, (int)height, 0, internalFormat, GL_UNSIGNED_BYTE, _data);

//	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_ALPHA_TYPE, GL_BLEND_DST_ALPHA);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

	std::cout << "Generated Texture!" << "\n";
  }

  void Texture::Bind() const {
	glBindTexture(GL_TEXTURE_2D, ID);
  }

  b2Vec2 Texture::GetSize() const {
	return {(float) width, (float) height};
  }

  void Texture::Generate(int _imageWidth, int _imageHeight, unsigned char* _data, int _x, int _y, int _frameWidth, int _frameHeight) {
	width = _frameWidth;
	height = _frameHeight;

	glBindTexture(GL_TEXTURE_2D, ID);
	glPixelStorei(GL_UNPACK_ROW_LENGTH, _imageWidth);
	glPixelStorei(GL_UNPACK_SKIP_PIXELS, _x);
	glPixelStorei(GL_UNPACK_SKIP_ROWS, _y);
	glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
	glTexImage2D(GL_TEXTURE_2D, 0, (int)internalFormat, _frameWidth, _frameHeight, 0, imageFormat, GL_UNSIGNED_BYTE, _data);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	glBindTexture(GL_TEXTURE_2D, 0);

  }
}

