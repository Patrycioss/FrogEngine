#pragma once

#include "Component.hpp"
#include "Texture.hpp"
#include "Colour.hpp"

namespace fe
{
  class Sprite : public fe::Component {
   private:
	fe::Texture* texture;
	b2Vec2 offset;
	fe::Colour colour;
	bool makeShape;
	b2Vec2 size;
	bool show;

   public:
	explicit Sprite(fe::Texture* _texture, const b2Vec2& _size = {-1, -1}, bool _makeShape = true, bool _show = true);

	void Start() override;
	void Update(float _deltaTime) override;
	void Render() override;

	void SetOffset(const b2Vec2& _offset);
	void SetColour(const fe::Colour& _colour);
	void Show(bool _value);
  };
}