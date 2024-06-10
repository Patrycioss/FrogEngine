#pragma once

#include <box2d/box2d.h>
#include <vector>
#include <concepts>
#include <memory>

#include "Component.hpp"

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

namespace fe
{
  class GameObject {
   private:
	static uint32_t IDs;
	uint32_t ID;

	std::vector<std::unique_ptr<Component>> components{};
	
	bool wasRenderedThisFrame{};

   protected:
	b2BodyId body{};
	b2ShapeDef shapeDef;

   protected:
	/* Called after the behaviours are added and started. */
	virtual void OnStart() {};

	/* Called every frame. */
	virtual void OnUpdate(float _deltaTime) {};
	
	/* Called every frame after update if on the screen. */
	virtual void OnRender(){};

   public:

	void Start();
	void Update(float _deltaTime);
	void Render();

	b2ShapeId AddShape(const b2Polygon& _polygon);
	b2ShapeId AddShape(const b2ShapeDef& _shapeDef, const b2Polygon& _polygon);
	
	explicit GameObject(b2BodyType _b2BodyType);
	virtual ~GameObject();

	[[nodiscard]] uint32_t GetID() const;
	[[nodiscard]] b2Vec2 GetPosition() const;
	[[nodiscard]] b2Rot GetRotation() const;
	[[nodiscard]] const b2BodyId& GetBody() const;
	
	// The angle of the body in Radians.
	[[nodiscard]] float GetAngle() const;
	
	void SetPosition(const b2Vec2& _position);
	void SetRotation(const b2Rot& _rotation);
	void SetTransform(const b2Vec2& _position, const b2Rot& _rotation);

	template<Derived<Component> T, typename... Args>
	T* AddComponent(Args... args) {
	  components.push_back(std::unique_ptr<T>(new T(std::move(args)...)));
	  T* component = (T*) components.back().get();
	  component->GameObject = this;
	  return component;
	}

	template<class T>
	void RemoveComponentsOfType() {
	  for (auto iterator = components.begin(); iterator < components.end(); iterator++) {
		T* a = dynamic_cast<T*>(*iterator.base());
		if (a != nullptr) {
		  components.erase(iterator);
		}
	  }
	};

	template<class T>
	T* GetComponent() {
	  for (auto& component : components) {
		T* a = dynamic_cast<T*>(component.get());
		if (a != nullptr) {
		  return a;
		}
	  }
	  return nullptr;
	};

  };

  inline bool operator==(const GameObject& _left, const GameObject& _right) {
	return _left.GetID() == _right.GetID();
  }

}