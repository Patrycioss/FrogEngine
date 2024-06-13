#pragma once

#include <box2d/box2d.h>

#include "src/core/Engine.hpp"

namespace fe
{
  /**
   * Inherit from this for your own game. Used by the engine.
   */
  class GameTemplate {
	friend Engine;
   protected:
	/**
     * Called when the game is started by the engine. 
     */
	virtual void Start() {};

	/** 
	 * Called every frame by the engine. 
	 */
	virtual void Update(float _deltaTime) {};

	/** 
	 * Called at the end of the game. 
	 */
	virtual void Stop() {};

	/**
	 * Create a GameObject that is then managed by the engine. Shortcut for Engine::Instantiate.
	 * @tparam T Type of GameObject to create, this should always inherit from GameObject.
	 * @tparam Args The arguments necessary to construct a GameObject of the given type. This allows for custom constructors.
	 * @return A pointer to the created GameObject. Do not delete this pointer manually but instead use the Destroy() function.
	 */
	template<Derived<GameObject> T, typename... Args>
	T* Instantiate(Args... args) {
	  return Engine::Instantiate<T>(args...);
	}
  };
}