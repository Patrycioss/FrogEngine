#include "Paddle.hpp"
#include "components/TestSpriteComponent.hpp"

const float Paddle::MOVE_SPEED = 500.0f;

void Paddle::OnStart() {

}

void Paddle::OnUpdate(float _deltaTime) {

  b2Vec2 direction = {0, 0};

  if (fe::Engine::IsKeyPressed(keyUp)) {
	direction += {0, -1};
  }
  
  if (fe::Engine::IsKeyPressed(keyDown)) {
	direction += {0, 1};
  }

  SetPosition(b2Vec2{baseX, GetPosition().y} + direction * (MOVE_SPEED * _deltaTime));
}

Paddle::Paddle(b2Vec2 _position, b2Rot _rotation)
	: keyUp(fe::Key::UP), keyDown(fe::Key::DOWN), baseX(_position.x), fe::GameObject(b2_staticBody) {
  
  fe::Texture* texture = fe::ResourceManager::LoadTexture("resources/textures/awesomeface.png");
  AddComponent<TestSpriteComponent>(texture, b2Vec2(20, 100));
  SetTransform(_position, _rotation);
}

void Paddle::SetControls(fe::Key _keyUp, fe::Key _keyDown) {
  keyUp = _keyUp;
  keyDown = _keyDown;
}