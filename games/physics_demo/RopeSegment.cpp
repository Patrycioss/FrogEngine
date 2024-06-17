#include "RopeSegment.hpp"

namespace PhysicsDemo
{
  RopeSegment::RopeSegment(b2Vec2 _size, b2Vec2 _position) :
	  fe::GameObject(b2_dynamicBody, _position) {

	fe::Texture* texture = fe::AssetManager::LoadTexture("resources/textures/brown_square.png");

	AddComponent<fe::Sprite>(texture, _size);

	SetPosition(_position);
	shapeDef.density = 0.001f;
	b2Polygon rect = b2MakeBox(_size.x / 2.0f, _size.y / 2.0f);
	AddShape(rect);

	b2MassData massData{};
	massData.mass = 0.001f;
	b2Body_SetMassData(body, massData);
  }
}
