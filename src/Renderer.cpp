#include "Renderer.hpp"
#include "ResourceManager.hpp"
#include "Engine.hpp"

#include <glad/glad.h>

namespace fe
{
  uint32_t Renderer::spriteVAO{};
  ShaderRef Renderer::spriteShader;
  ShaderRef Renderer::shapeShader;
  ShaderRef Renderer::animationShader;
  Camera Renderer::camera{};
  std::vector<Renderer::Polygon> Renderer::polygonsToDraw;

  // TODO: Experiment with altering the z axis in the vertex buffer to do rendering with priority.

  void Renderer::Initialize() {

	spriteShader = ResourceManager::CreateShader("default", "resources/shaders/sprite/vertex.glsl", "resources/shaders/sprite/fragment.glsl");
	shapeShader = ResourceManager::CreateShader("shape", "resources/shaders/line/vertex.glsl", "resources/shaders/line/fragment.glsl");
	animationShader = ResourceManager::CreateShader("animation", "resources/shaders/animation/vertex.glsl", "resources/shaders/animation/fragment.glsl");

	InitializeSprite();
  }

  void Renderer::InitializeSprite() {
	uint32_t VBO;
	float vertices[] = {
		// pos      // tex
		// Draw From Top Left
//		0.0f, 1.0f, 0.0f, 1.0f,
//		1.0f, 0.0f, 1.0f, 0.0f,
//		0.0f, 0.0f, 0.0f, 0.0f,

//		0.0f, 1.0f, 0.0f, 1.0f,
//		1.0f, 1.0f, 1.0f, 1.0f,
//		1.0f, 0.0f, 1.0f, 0.0f

		// Draw From Center
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

  void Renderer::DrawSprite(Texture* _texture, ShaderRef _shader, b2Vec2 _position, b2Vec2 _size, float _rotate, Colour _colour) {

	Shader::Use(_shader);

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(glm::vec2{_position.x, _position.y}, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f));
	model = glm::rotate(model, _rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));

	model = glm::scale(model, glm::vec3(glm::vec2{_size.x, _size.y}, 1.0f));

	Shader::SetMatrix4(_shader, "model", model);
	Shader::SetMatrix4(_shader, "projection", Engine::Camera.GetProjectionMatrix());
	Shader::SetVec4(_shader, "spriteColor", _colour.GetGLReady());

	glActiveTexture(GL_TEXTURE0);
	_texture->Bind();

	glBindVertexArray(spriteVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glActiveTexture(0);
  }

  void Renderer::Cleanup() {
	glDeleteVertexArrays(1, &spriteVAO);
  }

  void Renderer::DrawSprite(Texture* _texture, b2Vec2 _position, b2Vec2 _size, float _rotate, Colour _colour) {
	DrawSprite(_texture, spriteShader, _position, _size, _rotate, _colour);
  }

  void Renderer::DrawPolygon(b2Vec2* _vertices, int _vertexCount, Colour _colour) {
	Polygon polygon;
	polygon.Colour = _colour;
	polygon.Vertices.reserve(_vertexCount);

	for (int i = 0; i < _vertexCount; i++) {
	  polygon.Vertices.push_back(_vertices[i]);
	}

	polygonsToDraw.push_back(polygon);
  }

  void Renderer::Render() {
	Shader::Use(shapeShader);

	for (const auto& polygon : polygonsToDraw) {

	  Shader::SetVec4(shapeShader, "colour", polygon.Colour.GetGLReady());

	  for (int i = 0; i < polygon.Vertices.size(); i++) {

		int otherIndex = i + 1;

		if (otherIndex == polygon.Vertices.size()) {
		  otherIndex = 0;
		}

		float vertices[] = {polygon.Vertices[i].x, polygon.Vertices[i].y, polygon.Vertices[otherIndex].x, polygon.Vertices[otherIndex].y};

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

  void Renderer::DrawAnimationSprite(Texture* _texture, const AnimationSettings& _animationSettings, float _timeSeconds) {

	Shader::Use(animationShader);
	
	b2Vec2 _position = {300,300};
	b2Vec2 _size = _texture->GetSize();
	_size.x /= (float) _animationSettings.columns;
	_size.y /= (float) _animationSettings.rows;
	
	float _rotate = 0;
	Colour _colour = Colour::WHITE;

	glm::mat4 model = glm::mat4(1.0f);
	model = glm::translate(model, glm::vec3(glm::vec2{_position.x, _position.y}, 0.0f));

	model = glm::translate(model, glm::vec3(0.5f * _size.x, 0.5f * _size.y, 0.0f));
	model = glm::rotate(model, _rotate, glm::vec3(0.0f, 0.0f, 1.0f));
	model = glm::translate(model, glm::vec3(-0.5f * _size.x, -0.5f * _size.y, 0.0f));

	model = glm::scale(model, glm::vec3(glm::vec2{_size.x, _size.y}, 1.0f));

	Shader::SetMatrix4(animationShader, "model", model);
	Shader::SetMatrix4(animationShader, "projection", Engine::Camera.GetProjectionMatrix());
	Shader::SetVec4(animationShader, "spriteColor", _colour.GetGLReady());
	Shader::SetInt(animationShader, "columns", _animationSettings.columns);
	Shader::SetInt(animationShader, "rows", _animationSettings.rows);
	Shader::SetFloat(animationShader, "time", _timeSeconds);
	Shader::SetFloat(animationShader, "animationSpeed", _animationSettings.fps);
	Shader::SetInt(animationShader, "cycleStartFrame", _animationSettings.cycleStartFrame);
	Shader::SetInt(animationShader, "frameCount", _animationSettings.cycleFrameCount);

	glActiveTexture(GL_TEXTURE0);
	_texture->Bind();

	glBindVertexArray(spriteVAO);
	glDrawArrays(GL_TRIANGLES, 0, 6);
	glBindVertexArray(0);

	glActiveTexture(0);
  }
}
