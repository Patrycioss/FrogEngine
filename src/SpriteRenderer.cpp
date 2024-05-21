#include "SpriteRenderer.hpp"

#include <glad/glad.h>

namespace fe
{
  uint32_t SpriteRenderer::VAO{};
  
  void SpriteRenderer::Initialize() {
	uint32_t VBO;
	float vertices[] = {
		// pos      // tex
		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f,
		0.0f, 0.0f, 0.0f, 0.0f,

		0.0f, 1.0f, 0.0f, 1.0f,
		1.0f, 1.0f, 1.0f, 1.0f,
		1.0f, 0.0f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &VAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(VAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
  }

  void SpriteRenderer::DrawSprite(Texture& _texture, ShaderRef _shader, glm::vec2 _position, glm::vec2 _size, float _rotate, glm::vec3 _colour) {
	Shader::Use(_shader);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(_position, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f));
	model = glm::rotate(model, glm::radians(_rotate), glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));

	model = glm::scale(model, glm::vec3(_size, 1.0f));

	Shader::SetMatrix4(_shader, "model", model);
	Shader::SetVec3(_shader, "spriteColor", _colour);

	glActiveTexture(GL_TEXTURE0);
	_texture.Bind();

	glBindVertexArray(VAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);
  }

  void SpriteRenderer::Cleanup() {
	glDeleteVertexArrays(1, &VAO);
  }
}
