#include "Body.hpp"

#include "src/core/Engine.hpp"

namespace fe
{
  Body::Body(const b2Vec2& _position, const b2BodyType& _bodyType) {
	bodyDef.position = _position;
	bodyDef.type = _bodyType;
	id = Engine::GetWorld().CreateBody(bodyDef);
  }

  Body::~Body() {
	b2DestroyBody(id);
  }

  b2Vec2 Body::GetPosition() const {
	return b2Body_GetPosition(id);
  }

  b2Rot Body::GetRotation() const {
	return b2Body_GetRotation(id);
  }

  float Body::GetAngle() const {
	return b2Body_GetAngle(id);
  }

  void Body::SetTransform(const b2Vec2& _position, float _angle) {
	b2Body_SetTransform(id, _position, _angle);
  }
  
  void Body::SetTransform(const b2Vec2& _position, const b2Rot& _rotation) {
	b2Body_SetTransform(id, _position, b2Rot_GetAngle(_rotation));
  }

  void Body::SetPosition(const b2Vec2& _position) {
	b2Body_SetTransform(id, _position, b2Body_GetAngle(id));
  }
  
  void Body::SetAngle(float _angle) {
	b2Body_SetTransform(id, b2Body_GetPosition(id), _angle);
  }
  
  void Body::SetRotation(const b2Rot& _rotation) {
	b2Body_SetTransform(id, b2Body_GetPosition(id), b2Rot_GetAngle(_rotation));
  }

  b2ShapeId Body::AddShape(const b2ShapeDef& _shapeDef, const b2Polygon& _polygon) {
	return b2CreatePolygonShape(id, &_shapeDef, &_polygon);
  }
}