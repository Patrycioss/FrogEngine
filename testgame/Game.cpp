#include "Game.hpp"
#include "TestObject.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include <gtx/string_cast.hpp>

Game::Game()
{
  // Good place to alter settings
  settings.windowTitle = "My Super Awesome Game!";
  settings.windowHeight = 1000;
}

void Game::Start() {

  shader = ResourceManager.CreateShader("default", "resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
  texture = ResourceManager.LoadTexture("resources/textures/awesomeface.png", true);

  camera.NearPlane = -1.0f;
  fe::Shader::Use(shader);
  fe::Shader::SetMatrix4(shader, "projection", camera.GetProjectionMatrix());

  fe::GameObject* test = scene.AddObject<TestObject>();
//  scene.Start();
}

void Game::Update(float _deltaTime) {
  fe::Util::ClearScreen({0.45f, 0.55f, 0.60f, 1.00f});

//  scene.Update(_deltaTime);
  
//  camera.Zoom += 0.001f;
//  fe::Shader::SetMatrix4(shader, "projection", camera.GetProjectionMatrix());
  

  fe::SpriteRenderer::DrawSprite(*texture, shader, {0, 0}, {512, 512});
  fe::SpriteRenderer::DrawSprite(*texture, shader, {512, 512}, {512, 512});
}

void Game::Stop() {
  delete gameObject;
}