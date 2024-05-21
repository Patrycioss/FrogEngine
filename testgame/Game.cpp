#include "Game.hpp"
#include "Behaviours/TestBehaviour.hpp"

Game::Game() : GameTemplate({0.0f, -10.0f}) {
  }

void Game::Start() {

  shader = ResourceManager.CreateShader("default", "resources/shaders/vertex.glsl", "resources/shaders/fragment.glsl");
  texture = ResourceManager.LoadTexture("resources/textures/awesomeface.png", true);

  glm::mat4 projection = glm::ortho(0.0f, 800.0f, 600.0f, 0.0f, -1.0f, 1.0f);
  
  
//  World.QueryAABB()
  
  fe::Shader::Use(shader);
  fe::Shader::SetMatrix4(shader, "projection", projection);

  b2BodyDef groundBodyDef;
  groundBodyDef.position.Set(0.0f, -10.0f);

  b2Body* groundBody = World.CreateBody(&groundBodyDef);

  b2PolygonShape groundBox;
  groundBox.SetAsBox(50.0f, 10.0f);

  groundBody->CreateFixture(&groundBox, 0.0f);

  b2BodyDef bodyDef;
  bodyDef.type = b2_dynamicBody;
  bodyDef.position.Set(0.0f, 4.0f);
  b2Body* body = World.CreateBody(&bodyDef);

  b2PolygonShape dynamicBox;
  dynamicBox.SetAsBox(1.0f, 1.0f);

  b2FixtureDef fixtureDef;
  fixtureDef.shape = &dynamicBox;
  fixtureDef.density = 1.0f;
  fixtureDef.friction = 0.3f;

  body->CreateFixture(&fixtureDef);

  gameObject = new GameObject{body};
//  TestBehaviour* behaviour = gameObject.AddBehaviour<TestBehaviour>();
  TestBehaviour* testBehaviour = gameObject->AddBehaviour<TestBehaviour>();
  testBehaviour->Start();
}

void Game::Update(float _deltaTime) {
  fe::Util::ClearScreen({0.45f, 0.55f, 0.60f, 1.00f});

  // Rendering
  ImGui::Begin("Ha");
  ImGui::SetWindowSize({300, 300});
  ImGui::End();
  
  ImGui::ShowDemoWindow();

  fe::SpriteRenderer::DrawSprite(*texture, shader, {0,0}, {512,512});
}

void Game::Stop() {
	delete gameObject;
}

