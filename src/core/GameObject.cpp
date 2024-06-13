#include "src/core/GameObject.hpp"
#include "src/core/Engine.hpp"

namespace fe
{
  uint32_t GameObject::IDs = 0;
  
  GameObject::GameObject(b2BodyType _b2BodyType) :
	  ID(IDs++), wasRenderedThisFrame(false),
	  components(), body(),
	  shapeDef(b2DefaultShapeDef()) {

	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = _b2BodyType;
	bodyDef.position = {300, 300};
	body = Engine::CreateBody(&bodyDef);
	ID = IDs++;
  }

  GameObject::~GameObject() {
	b2DestroyBody(body);
  }

  void GameObject::InternalStart() {
	for (auto& component : components) {
	  component->Start();
	}

	Start();
  }

  void GameObject::InternalUpdate(float _deltaTime) {
	wasRenderedThisFrame = false;

	for (auto& component : components) {
	  component->Update(_deltaTime);
	}

	Update(_deltaTime);
  }

  void GameObject::InternalRender() {
	if (!wasRenderedThisFrame) {
	  for (const auto& component : components) {
		component->Render();
	  }

	  wasRenderedThisFrame = true;
	}
  }

  b2Vec2 GameObject::GetPosition() const {
	return b2Body_GetPosition(body);
  }

  b2Rot GameObject::GetRotation() const {
	return b2Body_GetRotation(body);
  }

  float GameObject::GetAngle() const {
	return b2Body_GetAngle(body);
  }

  const b2BodyId& GameObject::GetBody() const {
	return body;
  }

  uint32_t GameObject::GetID() const {
	return ID;
  }

  void GameObject::SetTransform(const b2Vec2& _position, float _angle) {
	b2Body_SetTransform(body, _position, _angle);
  }

  void GameObject::SetTransform(const b2Vec2& _position, const b2Rot& _rotation) {
	SetTransform(_position, b2Rot_GetAngle(_rotation));
  }

  void GameObject::SetPosition(const b2Vec2& _position) {
	SetTransform(_position, GetAngle());
  }

  void GameObject::SetAngle(float _angle) {
	SetTransform(GetPosition(), _angle);
  }

  void GameObject::SetRotation(const b2Rot& _rotation) {
	SetTransform(GetPosition(), _rotation);
  }

  b2ShapeId GameObject::AddShape(const b2ShapeDef& _shapeDef, const b2Polygon& _polygon) {
	return b2CreatePolygonShape(body, &_shapeDef, &_polygon);
  }
  
  b2ShapeId GameObject::AddShape(const b2Polygon& _polygon) {
	// Todo: Allow for setting the position of the shape.
	return b2CreatePolygonShape(body, &shapeDef, &_polygon);
  }
}