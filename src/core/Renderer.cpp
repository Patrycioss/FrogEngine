#include "src/core/Renderer.hpp"
#include "src/core/Engine.hpp"
#include "src/core/Time.hpp"

#include <glad/glad.h>
#include <ext/matrix_transform.hpp>

namespace fe
{
  uint32_t Renderer::spriteVAO{};
  ShaderRef Renderer::spriteShader;
  ShaderRef Renderer::shapeShader;
  ShaderRef Renderer::animationShader;
  std::vector<Renderer::Polygon> Renderer::polygonsToDraw;

  void Renderer::Initialize() {

	spriteShader = Shader::Create("resources/shaders/sprite.vert", "resources/shaders/sprite.frag");
	shapeShader = Shader::Create("resources/shaders/shape.vert", "resources/shaders/shape.frag");
	animationShader = Shader::Create("resources/shaders/animation.vert", "resources/shaders/animation.frag");

	SetupGLData();
  }

  void Renderer::SetupGLData() {
	uint32_t VBO;
	float vertices[] = {
		// Draw From Center
		// pos      // tex
		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f,
		-0.5f, -0.5f, 0.0f, 0.0f,

		-0.5f, 0.5f, 0.0f, 1.0f,
		0.5f, 0.5f, 1.0f, 1.0f,
		0.5f, -0.5f, 1.0f, 0.0f
	};

	glGenVertexArrays(1, &spriteVAO);
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glBindVertexArray(spriteVAO);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);
  }

  void Renderer::RenderQueued() {
	Shader::Use(shapeShader);

	for (const Polygon& polygon : polygonsToDraw) {

	  Shader::SetVec4(shapeShader, "colour", polygon.colour.GetGLReady());

	  for (int i = 0; i < polygon.vertices.size(); i++) {

		int otherIndex = i + 1;

		if (otherIndex == polygon.vertices.size()) {
		  otherIndex = 0;
		}

		float vertices[] = {polygon.vertices[i].x, polygon.vertices[i].y, polygon.vertices[otherIndex].x, polygon.vertices[otherIndex].y};

		uint32_t VAO, VBO;

		glGenVertexArrays(1, &VAO);
		glGenBuffers(1, &VBO);

		glBindVertexArray(VAO);
		glBindBuffer(GL_ARRAY_BUFFER, VBO);
		glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);
		glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 2 * sizeof(GLfloat), nullptr);
		glEnableVertexAttribArray(0);

		glDrawArrays(GL_LINES, 0, 2);
	  }
	}

	polygonsToDraw.clear();
  }

  void Renderer::Cleanup() {
	glDeleteVertexArrays(1, &spriteVAO);
	Shader::Delete(spriteShader);
	Shader::Delete(shapeShader);
	Shader::Delete(animationShader);
  }

  void Renderer::DrawSprite(Texture* _texture, const SpriteSettings& _spriteSettings) {

	Shader::Use(spriteShader);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(glm::vec2{_spriteSettings.position.x, _spriteSettings.position.y}, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * _spriteSettings.size.x, 0.5f * _spriteSettings.size.y, 0.0f));
	model = glm::rotate(model, _spriteSettings.angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * _spriteSettings.size.x, -0.5f * _spriteSettings.size.y, 0.0f));

	model = glm::scale(model, glm::vec3(glm::vec2{_spriteSettings.size.x, _spriteSettings.size.y}, 1.0f));

	Shader::SetMatrix4(spriteShader, "model", model);
	Shader::SetMatrix4(spriteShader, "projection", Engine::projectionMatrix);
	Shader::SetVec4(spriteShader, "spriteColor", _spriteSettings.colour.GetGLReady());
	Shader::SetBool(spriteShader, "flipHorizontal", _spriteSettings.flipHorizontal);
	Shader::SetBool(spriteShader, "flipVertical", _spriteSettings.flipVertical);

	glActiveTexture(GL_TEXTURE0);
	_texture->Bind();

	glBindVertexArray(spriteVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glActiveTexture(0);
  }

  void Renderer::DrawPolygon(b2Vec2* _vertices, int _vertexCount, Colour _colour) {
	Polygon polygon;
	polygon.colour = _colour;
	polygon.vertices.reserve(_vertexCount);

	for (int i = 0; i < _vertexCount; i++) {
	  polygon.vertices.push_back(_vertices[i]);
	}

	polygonsToDraw.push_back(polygon);
  }

  void Renderer::DrawAnimationSprite(Texture* _texture, const AnimationSettings& _animationSettings, const SpriteSettings& _spriteSettings) {

	Shader::Use(animationShader);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(glm::vec2{_spriteSettings.position.x, _spriteSettings.position.y}, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * _spriteSettings.size.x, 0.5f * _spriteSettings.size.y, 0.0f));
	model = glm::rotate(model, _spriteSettings.angle, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * _spriteSettings.size.x, -0.5f * _spriteSettings.size.y, 0.0f));

	model = glm::scale(model, glm::vec3(glm::vec2{_spriteSettings.size.x, _spriteSettings.size.y}, 1.0f));

	Shader::SetMatrix4(animationShader, "model", model);
	Shader::SetMatrix4(animationShader, "projection", Engine::projectionMatrix);
	Shader::SetVec4(animationShader, "spriteColor", _spriteSettings.colour.GetGLReady());
	Shader::SetInt(animationShader, "columns", _animationSettings.columns);
	Shader::SetInt(animationShader, "rows", _animationSettings.rows);
	Shader::SetFloat(animationShader, "time", Time::GetTimeSeconds());
	Shader::SetFloat(animationShader, "animationSpeed", _animationSettings.fps);
	Shader::SetInt(animationShader, "cycleStartFrame", _animationSettings.cycleStartFrame);
	Shader::SetInt(animationShader, "frameCount", _animationSettings.cycleFrameCount);
	Shader::SetBool(animationShader, "flipHorizontal", _spriteSettings.flipHorizontal);
	Shader::SetBool(animationShader, "flipVertical", _spriteSettings.flipVertical);

	glActiveTexture(GL_TEXTURE0);
	_texture->Bind();

	glBindVertexArray(spriteVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glActiveTexture(0);
  }
}
