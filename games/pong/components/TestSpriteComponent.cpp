#include "TestSpriteComponent.hpp"

void TestSpriteComponent::Render() {
  fe::SpriteRenderer::DrawSprite(texture,
								 GameObject->GetPosition() + offset,
								 size * GameObject->GetScale(),
								 GameObject->GetAngle(),
								 colour);
}

void TestSpriteComponent::Start() {
  if (makeShape) {
	b2Vec2 textureSize = texture->GetSize();
	b2Polygon polygon = b2MakeBox(textureSize.x / 2.0f, textureSize.y / 2.0f);
	GameObject->AddShape(polygon);
  }
}

TestSpriteComponent::TestSpriteComponent(fe::Texture* _texture, const b2Vec2& _size, bool _makeShape)
	: texture(_texture), offset({0, 0}), colour(fe::Colour::WHITE), makeShape(_makeShape), size({0, 0}) {
  
  if (_size.x < 0 && _size.y < 0) {
	size = _texture->GetSize();
  } else {
	size = _size;
  }
}

void TestSpriteComponent::SetOffset(const b2Vec2& _offset) {
  offset = _offset;
}

void TestSpriteComponent::SetColour(const fe::Colour& _colour) {
  colour = _colour;
}

void TestSpriteComponent::Update(float _deltaTime) {

}

