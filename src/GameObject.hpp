#pragma once

#include <box2d/b2_body.h>
#include <vector>
#include <concepts>
#include <memory>

#include "Behaviour.hpp"
#include "Transform.hpp"

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

namespace fe
{
  class GameObject {
   private:

	std::vector<std::unique_ptr<Behaviour>> behaviours{};

   public:
	Transform Transform;
	explicit GameObject();

	~GameObject();

	template<Derived<Behaviour> T>
	T* AddBehaviour() {
	  behaviours.emplace_back(new T());
	  T * behaviour = dynamic_cast<T*>(behaviours.back().get());
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
		T* a = dynamic_cast<T*>(behaviour.get());
		if (a != nullptr) {
		  return a;
		}
	  }
	  return nullptr;
	};
  };
}