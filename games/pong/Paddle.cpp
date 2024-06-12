#include "Paddle.hpp"

const float Paddle::MOVE_SPEED = 500.0f;

void Paddle::Start() {

}

void Paddle::Update(float _deltaTime) {
  b2Vec2 direction = {0, 0};

  if (fe::Input::GetKey(keyUp)) {
	direction += {0, -1};
  }
  
  if (fe::Input::GetKey(keyDown)) {
	direction += {0, 1};
  }

  SetPosition(b2Vec2{baseX, GetPosition().y} + direction * (MOVE_SPEED * _deltaTime));
}

Paddle::Paddle(b2Vec2 _position, b2Rot _rotation)
	: keyUp(fe::Key::UP), keyDown(fe::Key::DOWN), baseX(_position.x), fe::GameObject(b2_staticBody) {
  
  fe::Texture* texture = fe::AssetManager::LoadTexture("resources/textures/awesomeface.png");
  fe::Sprite* spriteRenderer = AddComponent<fe::Sprite>(texture, b2Vec2(20,100));

  spriteRenderer->Show(false);
  
  SetTransform(_position, _rotation);
  b2Polygon polygon = b2MakeBox(20, 100);
  AddShape(polygon);
}

void Paddle::SetControls(fe::Key _keyUp, fe::Key _keyDown) {
  keyUp = _keyUp;
  keyDown = _keyDown;
}