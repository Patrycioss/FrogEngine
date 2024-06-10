#include "Sprite.hpp"
#include "Renderer.hpp"
#include "GameObject.hpp"

namespace fe
{
  void Sprite::Render() {
	if (!show) {
	  return;
	}
	fe::Renderer::DrawSprite(texture, spriteSettings);
  }

  void Sprite::Start() {
	if (spriteSettings.size.x < 0 && spriteSettings.size.y < 0) {
	  spriteSettings.size = GetDefaultSize();
	}
	
	if (makeShape) {
	  b2Polygon polygon = b2MakeBox(spriteSettings.size.x / 2.0f, spriteSettings.size.y / 2.0f);
	  GameObject->AddShape(polygon);
	}
  }

  Sprite::Sprite(fe::Texture* _texture, const b2Vec2& _size, bool _makeShape)
	  : texture(_texture), offset({0, 0}), spriteSettings(), makeShape(_makeShape), show(true) {
	spriteSettings.size = _size;
  }

  void Sprite::SetOffset(const b2Vec2& _offset) {
	offset = _offset;
  }

  void Sprite::SetColour(const fe::Colour& _colour) {
	spriteSettings.colour = _colour;
  }

  void Sprite::Update(float _deltaTime) {
	spriteSettings.position = GameObject->GetPosition();
	spriteSettings.angle = GameObject->GetAngle();
  }

  void Sprite::Show(bool _value) {
	show = _value;
  }

  b2Vec2 Sprite::GetDefaultSize() {
	return texture->GetSize();
  }

  void Sprite::FlipHorizontal(bool _value) {
	spriteSettings.flipHorizontal = _value;
  }

  void Sprite::FlipVertical(bool _value) {
	spriteSettings.flipVertical = _value;
  }
}