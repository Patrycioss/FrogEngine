#include <iostream>
#include "GameObject.hpp"

namespace fe
{
  uint32_t GameObject::IDs = 0;

  GameObject::GameObject() {
	ID = IDs++;
  }

  uint32_t GameObject::GetID() const {
	return ID;
  }

  GameObject::~GameObject() {
	for (auto& behaviour : behaviours) {
	  delete behaviour;
	}
  }
}