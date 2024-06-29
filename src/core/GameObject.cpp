#include "src/core/GameObject.hpp"
#include "src/core/Engine.hpp"

namespace fe
{
  uint32_t GameObject::IDs = 0;
  
  GameObject::GameObject(b2BodyType _b2BodyType, const b2Vec2& _position) :
	  ID(IDs++), wasRenderedThisFrame(false),
	  components(), body(_position, _b2BodyType),
	  shapeDef(b2DefaultShapeDef()) {

	ID = IDs++;
  }

  GameObject::~GameObject() = default;

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

  b2ShapeDef& GameObject::GetShapeDef() {
	return shapeDef;
  }

  Body& GameObject::GetBody() {
	return body;
  }

  uint32_t GameObject::GetID() const {
	return ID;
  }

  b2ShapeId GameObject::AddShape(const b2ShapeDef& _shapeDef, const b2Polygon& _polygon) {
	return body.AddShape(_shapeDef, _polygon);
  }
  
  b2ShapeId GameObject::AddShape(const b2Polygon& _polygon) {
	return body.AddShape(shapeDef, _polygon);
  }
}