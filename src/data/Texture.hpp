#pragma once

#include <box2d/box2d.h>

namespace fe
{
  class Texture {
   private:
	uint32_t ID{};
	int width = 0;
	int height = 0;
	uint32_t imageFormat;
	bool hardPixels;

   public:
	/**
	 * Construct a Texture.
	 * @param _imageFormat The format of the image, e.g. RGB, RGBA...
	 */
	explicit Texture(uint32_t _imageFormat, bool _hardPixels);
	
	/**
	 * @return The ID of the Texture.
	 */
	[[nodiscard]] const uint32_t& GetID() const;
	
	/**
	 * @return The size of the image. 
	 */
	[[nodiscard]] b2Vec2 GetSize() const;
	
	/**
	 * Generates a Texture based on loaded in data.
	 * @param _imageWidth The width of the image.
	 * @param _imageHeight The height of the image.
	 * @param _data The image data.
	 */
	void Generate(int _imageWidth, int _imageHeight, unsigned char* _data);
	
	/**
	 * Binds the texture to OpenGL.
	 */
	void Bind() const;
  };
}