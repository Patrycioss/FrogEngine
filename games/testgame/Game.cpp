#include "Game.hpp"
#include "TestObject.hpp"

#define GLM_ENABLE_EXPERIMENTAL
#include "gtx/string_cast.hpp"

float timePassed;

Game::Game()
{
  // Good place to alter settings
  fe::Engine::SetWindowTitle("Test Title!");
  fe::Engine::SetWindowSize(1000, 1000);
}

void Game::Start() {

  texture = fe::ResourceManager::LoadTexture("resources/textures/awesomeface.png");
  

  camera.NearPlane = -1.0f;

  fe::GameObject* test = scene.AddObject<TestObject>();
  scene.Start();
}

void Game::Update(float _deltaTime) {
  fe::Util::ClearScreen({0.45f, 0.55f, 0.60f, 1.00f});
  
  scene.Update(_deltaTime);
  
//  camera.Zoom += 0.001f;
//  fe::Shader::SetMatrix4(shader, "projection", camera.GetProjectionMatrix());

//  fe::SpriteRenderer::DrawSprite(texture, {0, 0}, {512, 512});
//  fe::SpriteRenderer::DrawSprite(texture, {512, 512}, {512, 512});
//  fe::SpriteRenderer::DrawSprite(texture, {200, 200}, {200, 200});
}

void Game::Stop() {
  delete gameObject;
}