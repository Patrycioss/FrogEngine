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
	virtual void Start() = 0;
	virtual void Update(float _deltaTime) = 0;
	virtual void Render() = 0;
	virtual ~Behaviour() = default;
  };

}

