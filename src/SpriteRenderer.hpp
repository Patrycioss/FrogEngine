#pragma once

#include <glm.hpp>
#include <ext/matrix_transform.hpp>
#include <box2d/box2d.h>

#include "Texture.hpp"
#include "Shader.hpp"
#include "Camera.hpp"
#include "Colour.hpp"

namespace fe
{
  class SpriteRenderer {
   private:
	static uint32_t VAO;
	static ShaderRef defaultShader;
	static Camera camera;

   public:
	static void Initialize();
	static void DrawSprite(Texture* _texture, ShaderRef _shader, b2Vec2 _position,
						   b2Vec2 _size = {10.0f, 10.0f}, float _rotate = 0.0f,
						   Colour _colour = {1.0f, 1.0f, 1.0f});

	static void DrawSprite(Texture* _texture, b2Vec2 _position,
						   b2Vec2 _size = {10.0f, 10.0f}, float _rotate = 0.0f,
						   Colour _colour = {1.0f, 1.0f, 1.0f});
	
	static void Cleanup();
  };
}