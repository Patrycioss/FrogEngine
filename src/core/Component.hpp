#pragma once

namespace fe
{
  class GameObject;

  /**
   * Can be attached to a GameObject to separate functionality and allow for easy access from other GameObjects.
   */
  class Component {
	friend GameObject;

   protected:
	
	/**
	 * The GameObject this Component is attached to.
	 */
	GameObject* GameObject = nullptr;

	/**
 	 * Called before the GameObject's Start() is called.
 	 */
	virtual void Start() {};
	
	/**
	 * Called every frame before the GameObject's Update() is called. 
	 * @param _deltaTime The delta time between the current and previous frame.
	 */
	virtual void Update(float _deltaTime) {};

	/**
	 * Called every frame after GameObject's Update() before GameObject's Render().
	 */
	virtual void Render() {};

   public:
	Component() = default;
	virtual ~Component() = default;
  };
}

