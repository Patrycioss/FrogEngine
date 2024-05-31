#include "Paddle.hpp"

void Paddle::OnStart() {
	texture = fe::ResourceManager::LoadTexture("resources/textures/awesomeface.png");  
}

void Paddle::OnUpdate(float _deltaTime) {
}


Paddle::Paddle(b2Vec2 _position, b2Rot _rotation) {
  b2Body_SetTransform(body, _position, b2Rot_GetAngle(_rotation));
}

void Paddle::Render() {
  fe::SpriteRenderer::DrawSprite(texture, GetPosition(), {30, 80});
}
