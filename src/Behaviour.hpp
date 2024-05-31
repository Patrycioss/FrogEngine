#pragma once

namespace fe
{
  class GameObject;

  class Behaviour {
	friend GameObject;

   protected:
	GameObject* GameObject = nullptr;

   public:
	Behaviour() = default;
	virtual void Start(){};
	virtual void Update(float _deltaTime){};
	virtual void Render(){};
	virtual ~Behaviour() = default;
  };

}

