#pragma once

#include <glm.hpp>

namespace fe
{
  class GameObject;

  class Transform {
   public:
	glm::vec2 Position;
	glm::vec2 Scale;
	GameObject* GameObject;

	explicit Transform(class GameObject* _gameObject) : GameObject(_gameObject) {};

  };
}