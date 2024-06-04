#pragma once

namespace fe
{
  class GameObject;

  class Component {
	friend GameObject;

   protected:
	GameObject* GameObject = nullptr;

   public:
	Component() = default;
	virtual void Start(){};
	virtual void Update(float _deltaTime){};
	virtual void Render(){};
	virtual ~Component() = default;
  };

}

