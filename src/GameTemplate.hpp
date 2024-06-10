#pragma once

#include <box2d/box2d.h>

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

namespace fe
{
  class GameTemplate {
   private:
	GLFWwindow* window = nullptr;

   protected:
	template<Derived<GameObject> T, typename... Args>
	T* Instantiate(Args... args) {
	  return Engine::Instantiate<T>(args...);
	}
	
   public:
	/* Called when the game is started by the engine. */
	virtual void Start() = 0;
	
	/* Called every frame by the engine. */
	virtual void Update(float _deltaTime) = 0;
	
	/* Called at the end of the game. */
	virtual void Stop() = 0;
  };
}