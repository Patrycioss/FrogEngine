#pragma once

#include "Component.hpp"
#include "Texture.hpp"
#include "Colour.hpp"
#include "SpriteSettings.hpp"

namespace fe
{
  class Sprite : public fe::Component {
   protected:
	SpriteSettings spriteSettings;
	fe::Texture* texture;
	b2Vec2 offset;
	bool makeShape;
	bool show;
	
   protected:
	virtual b2Vec2 GetDefaultSize();

   public:
	explicit Sprite(fe::Texture* _texture, const b2Vec2& _size = {-1, -1}, bool _makeShape = true);

	void Start() override;
	void Update(float _deltaTime) override;
	void Render() override;

	void SetOffset(const b2Vec2& _offset);
	void SetColour(const fe::Colour& _colour);
	void FlipHorizontal(bool _value);
	void FlipVertical(bool _value);
	void Show(bool _value);
	void SetZIndex(float _value);
  };
}