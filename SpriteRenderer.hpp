#pragma once

#include <glm.hpp>
#include <ext/matrix_transform.hpp>

#include "Texture.hpp"
#include "ShaderProgram.hpp"

class SpriteRenderer {
 private:
  ShaderProgram shader;
  uint32_t VAO{};

  void InitRenderData();

 public:
  explicit SpriteRenderer(ShaderProgram &shader);
  ~SpriteRenderer();

  void DrawSprite(Texture &texture, glm::vec2 position,
                  glm::vec2 size = glm::vec2(10.0f, 10.0f), float rotate = 0.0f,
                  glm::vec3 color = glm::vec3(1.0f, 1.0f, 1.0f));
};