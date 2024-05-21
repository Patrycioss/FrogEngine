#include "GameObject.hpp"

namespace fe
{
  GameObject::GameObject() :
	  Transform(this) {
	
  }

  GameObject::~GameObject() = default;
}