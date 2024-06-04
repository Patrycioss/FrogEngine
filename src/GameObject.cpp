#include <iostream>

#include "GameObject.hpp"
#include "Engine.hpp"

namespace fe
{
  uint32_t GameObject::IDs = 0;

  GameObject::GameObject(b2BodyType _b2BodyType) :
	  shapeDef(b2DefaultShapeDef()) {
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = _b2BodyType;
	bodyDef.position = {300, 300};
	body = Engine::CreateBody(&bodyDef);

	printf("Created body with id: %i \n", body.index1);

//	std::vector<b2ShapeId> shapes{};
//	int shapesAmount = b2Body_GetShapeCount(body);
//	shapes.reserve(shapesAmount);
//	b2Body_GetShapes(body, shapes.data(), shapesAmount);

	ID = IDs++;
  }

  uint32_t GameObject::GetID() const {
	return ID;
  }

  GameObject::~GameObject() {
	b2DestroyBody(body);
  }

  void GameObject::Start() {
	for (auto& component : components) {
	  component->Start();
	}

	OnStart();
  }

  void GameObject::Update(float _deltaTime) {
	wasRenderedThisFrame = false;

	for (auto& component : components) {
	  component->Update(_deltaTime);
	}

	OnUpdate(_deltaTime);
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

  void GameObject::Render() {
	if (!wasRenderedThisFrame) {
	  for (const auto& component : components) {
		component->Render();
	  }

	  wasRenderedThisFrame = true;
	}
  }

  const b2BodyId& GameObject::GetBody() const {
	return body;
  }

  void GameObject::AddShape(const b2ShapeDef& _shapeDef, const b2Polygon& _polygon) {
	b2CreatePolygonShape(body, &_shapeDef, &_polygon);
  }

  void GameObject::AddShape(const b2Polygon& _polygon) {
	b2CreatePolygonShape(body, &shapeDef, &_polygon);
  }

  void GameObject::SetPosition(const b2Vec2& _position) {
	b2Body_SetTransform(body, _position, GetAngle());
  }

  void GameObject::SetRotation(const b2Rot& _rotation) {
	b2Body_SetTransform(body, GetPosition(), b2Rot_GetAngle(_rotation));
  }

  void GameObject::SetTransform(const b2Vec2& _position, const b2Rot& _rotation) {
	b2Body_SetTransform(body, _position, b2Rot_GetAngle(_rotation));
  }

  float GameObject::GetScale() const {
	return scale;
  }

  void GameObject::SetScale(float _scale) {

  }
}