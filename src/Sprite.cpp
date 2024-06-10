#include "Sprite.hpp"
#include "Renderer.hpp"
#include "GameObject.hpp"

namespace fe
{
  void Sprite::Render() {
	if (!show) {
	  return;
	}
	fe::Renderer::DrawSprite(texture, {
		GameObject->GetPosition() + offset,
		GameObject->GetAngle(),
		size * GameObject->GetScale(),
		colour
	});
  }

  void Sprite::Start() {
	if (size.x < 0 && size.y < 0) {
	  size = GetDefaultSize();
	}
	
	if (makeShape) {
	  b2Polygon polygon = b2MakeBox(size.x / 2.0f, size.y / 2.0f);
	  GameObject->AddShape(polygon);
	}
  }

  Sprite::Sprite(fe::Texture* _texture, const b2Vec2& _size, bool _makeShape)
	  : texture(_texture), offset({0, 0}), colour(fe::Colour::WHITE), makeShape(_makeShape), size(_size), show(true) {
	
  }

  void Sprite::SetOffset(const b2Vec2& _offset) {
	offset = _offset;
  }

  void Sprite::SetColour(const fe::Colour& _colour) {
	colour = _colour;
  }

  void Sprite::Update(float _deltaTime) {}

  void Sprite::Show(bool _value) {
	show = _value;
  }

  b2Vec2 Sprite::GetDefaultSize() {
	return texture->GetSize();
  }
}