#include <iostream>

#include "GameObject.hpp"
#include "Engine.hpp"

namespace fe
{
  uint32_t GameObject::IDs = 0;

  GameObject::GameObject() {
	b2BodyDef bodyDef = b2DefaultBodyDef();
	bodyDef.type = b2_dynamicBody;
	bodyDef.position = {300, 300};
	body = Engine::CreateBody(&bodyDef);

	printf("Created body with id: %i \n", body.index1);

	b2ShapeDef shapeDef = b2DefaultShapeDef();
	shapeDef.density = 1.0f;
	shapeDef.friction = 0.3f;
	b2Polygon polygon = b2MakeBox(5, 5);
	b2CreatePolygonShape(body, &shapeDef, &polygon);

	std::vector<b2ShapeId> shapes{};
	int shapesAmount = b2Body_GetShapeCount(body);
	shapes.reserve(shapesAmount);
	b2Body_GetShapes(body, shapes.data(), shapesAmount);

	ID = IDs++;
  }

  uint32_t GameObject::GetID() const {
	return ID;
  }

  GameObject::~GameObject() {
	for (auto& behaviour : behaviours) {
	  delete behaviour;
	}

	b2DestroyBody(body);
  }

  void GameObject::Start() {
	for (auto& behaviour : behaviours) {
	  behaviour->Start();
	}

	OnStart();
  }

  void GameObject::Update(float _deltaTime) {
	for (auto& behaviour : behaviours) {
	  behaviour->Update(_deltaTime);
	}

	OnUpdate(_deltaTime);
  }

  b2Vec2 GameObject::GetPosition() const {
	return b2Body_GetPosition(body);
  }

  b2Rot GameObject::GetRotation() const {
	return b2Body_GetRotation(body);
  }

  void GameObject::Render() {

  }

  const b2BodyId& GameObject::GetBody() const {
	return body;
  }

}