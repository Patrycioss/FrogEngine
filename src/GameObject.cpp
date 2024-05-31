﻿#include <iostream>
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

}