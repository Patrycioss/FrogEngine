#include "Game.hpp"
#include "TestObject.hpp"

Game::Game() {
  // Good place to alter settings
  settings.windowTitle = "My Super Awesome Game!";
}

void Game::Start() {

  shader = ResourceManager.CreateShader("default", "resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
  texture = ResourceManager.LoadTexture("resources/textures/awesomeface.png", true);

  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

  fe::Shader::Use(shader);
  fe::Shader::SetMatrix4(shader, "projection", projection);

  fe::GameObject* test = scene.AddObject<TestObject>();
  scene.Start();
}

void Game::Update(float _deltaTime) {
  fe::Util::ClearScreen({0.45f, 0.55f, 0.60f, 1.00f});

  scene.Update(_deltaTime);

  fe::SpriteRenderer::DrawSprite(*texture, shader, {0, 0}, {512, 512});
  fe::SpriteRenderer::DrawSprite(*texture, shader, {500, 500}, {512, 512});
}

void Game::Stop() {
  delete gameObject;
}