#include "SpriteRenderer.hpp"
#include "Renderer.hpp"
#include "GameObject.hpp"

namespace fe
{
  void SpriteRenderer::Render() {
	if (!show){
	  return;
	}
	fe::Renderer::DrawSprite(texture,
							 GameObject->GetPosition() + offset,
							 size * GameObject->GetScale(),
							 GameObject->GetAngle(),
							 colour);
  }

  void SpriteRenderer::Start() {
	if (makeShape) {
//	  printf("X: %f, Y: %f\n", GameObject->GetPosition().x, GameObject->GetPosition().y);
	  b2Polygon polygon = b2MakeBox(size.x / 2.0f, size.y / 2.0f);
	  b2ShapeId  id = GameObject->AddShape(polygon);
	  
//	  for (int i = 0; i < polygon.count; i++){
//		printf("%i: %f, %f\n", i, polygon.vertices[i].x, polygon.vertices[i].y);
//	  }
//	  
//	  printf("%f, %f \n", GameObject->GetPosition().x, GameObject->GetPosition().y);
	  
	}
  }

  SpriteRenderer::SpriteRenderer(fe::Texture* _texture, const b2Vec2& _size, bool _makeShape, bool _show)
	  : texture(_texture), offset({0, 0}), colour(fe::Colour::WHITE), makeShape(_makeShape), size({0, 0}), show(_show) {

	if (_size.x < 0 && _size.y < 0) {
	  size = _texture->GetSize();
	} else {
	  size = _size;
	}
  }

  void SpriteRenderer::SetOffset(const b2Vec2& _offset) {
	offset = _offset;
  }

  void SpriteRenderer::SetColour(const fe::Colour& _colour) {
	colour = _colour;
  }

  void SpriteRenderer::Update(float _deltaTime) {

  }

  void SpriteRenderer::Show(bool _value) {
	show = _value;
  }
}