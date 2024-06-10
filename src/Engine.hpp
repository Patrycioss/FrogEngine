#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <box2d/box2d.h>
#include <glm.hpp>
#include <unordered_map>

#include "Settings.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "Key.hpp"

namespace fe
{
  class GameTemplate;
  class Engine {
   public:
	enum class State {
	  None,
	  Initialize,
	  Start
	};

   private:

	static State state;
	static GLFWwindow* window;
	static Settings currentSettings;
	static Camera camera;

	static b2WorldId world;
	static b2WorldDef worldDef;
	
//	static std::vector<int32_t> objectsToDestroy;

	/* Uses the index from the body ID to find Objects. */
	static std::unordered_map<int32_t, std::unique_ptr<GameObject>> objectRegistry;

	static bool ScreenQueryCallback(b2ShapeId _shape, void* something);

   public:
	/* Initialize the game */
	static void Initialize();

	/* Start the game using a GameTemplate */
	static void Start(GameTemplate& _gameTemplate);

	/* Stop the game. */
	static void Stop();

	/* Settings that are currently in use by the engine. */
	static const Settings& CurrentSettings;

	static const Camera& Camera;

	static b2WorldId& World;

	static void Destroy(GameObject* _object);

	template<Derived<GameObject> T, typename... Args>
	static T* Instantiate(Args... args) {
	  auto a = std::unique_ptr<T>(new T(std::move(args)...));
	  auto pair = objectRegistry.emplace(a->GetBody().index1, std::move(a));
	  return (T*)pair.first->second.get();
	}

	[[nodiscard]] static b2BodyId CreateBody(b2BodyDef* _bodyDef);

	static void SetWindowSize(uint16_t _width, uint16_t _height);
	static void EnableVsync(bool _enable);
	static void EnableFaceCulling(bool _enable);
	static void SetWindowTitle(const char* _title);
	static void SetGravity(b2Vec2 _gravity);
	static void WindowResizeCallback(GLFWwindow* _window, int _width, int _height);
	
  };
}