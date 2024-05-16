﻿#pragma once

#include <glm.hpp>
#include <ext/matrix_transform.hpp>

#include "Texture.hpp"
#include "Shader.hpp"

namespace FrogEngine
{
  class SpriteRenderer {
   private:
	uint32_t VAO{};

	void InitRenderData();

   public:
	explicit SpriteRenderer();
	~SpriteRenderer();

	void DrawSprite(Texture& _texture, ShaderRef _shader, glm::vec2 _position,
					glm::vec2 _size = glm::vec2(10.0f, 10.0f), float _rotate = 0.0f,
					glm::vec3 _colour = glm::vec3(1.0f, 1.0f, 1.0f)) const;
  };
}