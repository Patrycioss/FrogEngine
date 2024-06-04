#pragma once

#include <src/FrogEngine.hpp>

class TestSpriteComponent : public fe::Component {
 private:
  fe::Texture* texture;
  b2Vec2 offset;
  fe::Colour colour;
  bool makeShape;
  b2Vec2 size;
  
 public:
  explicit TestSpriteComponent(fe::Texture* _texture, const b2Vec2& _size = {-1,-1}, bool _makeShape = true);
  
  void Start() override;
  void Update(float _deltaTime) override;
  void Render() override;
  
  void SetOffset(const b2Vec2& _offset);
  void SetColour(const fe::Colour& _colour);
};
