#include "SpriteRenderer.hpp"

void SpriteRenderer::InitRenderData() {
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
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void *)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

SpriteRenderer::SpriteRenderer(ShaderProgram &shader) :
	shader(shader) {

  InitRenderData();

}

void SpriteRenderer::DrawSprite(Texture &texture, glm::vec2 position, glm::vec2 size, float rotate, glm::vec3 color) {

  shader.Use();
  glm::mat4 model = glm::mat4(1.0f);
  model = glm::translate(model, glm::vec3(position, 0.0f));

  model = glm::translate(model, glm::vec3(0.5f * size.x, 0.5f * size.y, 0.0f));
  model = glm::rotate(model, glm::radians(rotate), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::translate(model, glm::vec3(-0.5f * size.x, -0.5f * size.y, 0.0f));

  model = glm::scale(model, glm::vec3(size, 1.0f));
  
  shader.SetMatrix4("model", model);
  shader.SetVec3("spriteColor", color);

  glActiveTexture(GL_TEXTURE0);
  texture.Bind();

  glBindVertexArray(VAO);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

SpriteRenderer::~SpriteRenderer() {
  glDeleteVertexArrays(1, &VAO);
}