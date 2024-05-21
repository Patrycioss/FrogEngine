#pragma once

#include <box2d/b2_body.h>
#include <vector>
#include <concepts>
#include <memory>

#include "Behaviour.hpp"

template<class T, class U>
concept Derived = std::is_base_of<U, T>::value;

class GameObject {
 private:
  b2Body* body;

  std::vector<std::unique_ptr<Behaviour>> behaviours{};

 public:
  b2Body const& Body = *body;

  explicit GameObject(b2Body* _body);
  
  ~GameObject();

  template<Derived<Behaviour> T>
  T* AddBehaviour() {
	behaviours.emplace_back(new T);
	return dynamic_cast<T*>(behaviours.back().get());
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
