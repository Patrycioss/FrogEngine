#include "Paddle.hpp"

const float Paddle::MOVE_SPEED = 1.0f;

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

//  b2Body_ApplyForce(body, direction * (MOVE_SPEED * _deltaTime), b2Body_GetPosition(body), true);


}

Paddle::Paddle(b2Vec2 _position, b2Rot _rotation)
	: keyUp(fe::Key::UP), keyDown(fe::Key::DOWN), texture(fe::ResourceManager::LoadTexture("resources/textures/awesomeface.png")) {
  b2Body_SetTransform(body, _position, b2Rot_GetAngle(_rotation));
}

void Paddle::Render() {
  fe::SpriteRenderer::DrawSprite(texture, GetPosition(), {30, 80});
}

void Paddle::SetControls(fe::Key _keyUp, fe::Key _keyDown) {
  keyUp = _keyUp;
  keyDown = _keyDown;
}
