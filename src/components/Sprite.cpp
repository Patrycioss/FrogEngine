#include "src/components/Sprite.hpp"
#include "src/core/Renderer.hpp"
#include "src/core/GameObject.hpp"

namespace fe
{
  b2Vec2 Sprite::GetDefaultSize() {
	return texture->GetSize();
  }

  Sprite::Sprite(fe::Texture* _texture, bool _makeShape, const b2Vec2& _size)
	  : texture(_texture), offset({0, 0}), spriteSettings(), makeShape(_makeShape), show(true) {
	spriteSettings.size = _size;
  }

  Sprite::Sprite(fe::Texture* _texture, bool _makeShape)
	  : texture(_texture), offset({0, 0}), spriteSettings(), makeShape(_makeShape), show(true) {
	spriteSettings.size = {-1, -1};
  }

  Sprite::Sprite(fe::Texture* _texture, const b2Vec2& _size)
	  : texture(_texture), offset({0, 0}), spriteSettings(), makeShape(true), show(true) {
	spriteSettings.size = _size;
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

  void Sprite::Update(float _deltaTime) {
	spriteSettings.position = GameObject->GetPosition();
	spriteSettings.angle = GameObject->GetAngle();
  }

  void Sprite::Render() {
	if (!show) {
	  return;
	}
	fe::Renderer::DrawSprite(texture, spriteSettings);
  }

  const SpriteSettings& Sprite::GetSpriteSettings() const {
	return spriteSettings;
  }

  void Sprite::SetSpriteSettings(const SpriteSettings& _spriteSettings) {
	spriteSettings = _spriteSettings;
  }

  void Sprite::SetOffset(const b2Vec2& _offset) {
	offset = _offset;
  }

  void Sprite::SetColour(const fe::Colour& _colour) {
	spriteSettings.colour = _colour;
  }

  void Sprite::FlipHorizontal(bool _value) {
	spriteSettings.flipHorizontal = _value;
  }

  void Sprite::FlipVertical(bool _value) {
	spriteSettings.flipVertical = _value;
  }

  void Sprite::Show(bool _value) {
	show = _value;
  }
} 