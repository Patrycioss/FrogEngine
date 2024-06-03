#pragma once

#include <box2d/box2d.h>
#include <vector>
#include <concepts>
#include <memory>

#include "Behaviour.hpp"

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

namespace fe
{
  class GameObject {
   private:
	static uint32_t IDs;
	uint32_t ID;

	std::vector<Behaviour*> behaviours{};

   protected:
	b2BodyId body;

   protected:
	/* Called after the behaviours are added and started. */
	virtual void OnStart() {};

	/* Called every frame. */
	virtual void OnUpdate(float _deltaTime) {};

   public:

	void Start();
	void Update(float _deltaTime);
	virtual void Render();

	GameObject();
	virtual ~GameObject();

	[[nodiscard]] uint32_t GetID() const;
	[[nodiscard]] b2Vec2 GetPosition() const;
	[[nodiscard]] b2Rot GetRotation() const;
	[[nodiscard]] const b2BodyId& GetBody() const;

	template<Derived<Behaviour> T>
	T* AddBehaviour() {
	  behaviours.emplace_back(new T());
	  T * behaviour = dynamic_cast<T*>(behaviours.back());
	  behaviour->GameObject = this;
	  return behaviour;
	}

	template<class T>
	void RemoveBehavioursOfType() {
	  for (auto iterator = behaviours.begin(); iterator < behaviours.end(); iterator++) {
		T* a = dynamic_cast<T*>(*iterator.base());
		if (a != nullptr) {
		  behaviours.erase(iterator);
		  delete a;
		}
	  }
	};

	template<class T>
	T* GetComponent() {
	  for (auto& behaviour : behaviours) {
		T* a = dynamic_cast<T*>(behaviour);
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