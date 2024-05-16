#include "Game.hpp"

Game::Game() : Engine({0.0f, -10.0f}) {
  }

void Game::OnStart() {

  shader = resourceManager.CreateShader("default", "resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
  texture = resourceManager.LoadTexture("resources/textures/awesomeface.png", true);

  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);

  FrogEngine::Shader::Use(shader);
  FrogEngine::Shader::SetMatrix4(shader, "projection", projection);

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, -10.0f);

  b2Body* groundBody = world.CreateBody(&groundBodyDef);

  b2PolygonShape groundBox;
  groundBox.SetAsBox(50.0f, 10.0f);

  groundBody->CreateFixture(&groundBox, 0.0f);

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 4.0f);
  b2Body* body = world.CreateBody(&bodyDef);

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;

  body->CreateFixture(&fixtureDef);
}

void Game::OnUpdate(float _deltaTime) {
  FrogEngine::ClearScreen({0.45f, 0.55f, 0.60f, 1.00f});

  // Rendering
  ImGui::Begin("Ha");
  ImGui::SetWindowSize({300, 300});
  ImGui::End();
  
  ImGui::ShowDemoWindow();

  FrogEngine::SpriteRenderer::DrawSprite(*texture, shader, {0,0}, {512,512});
}

void Game::OnStop() {

}

