#pragma once

#define GLFW_INCLUDE_NONE
#include <glfw/glfw3.h>

#include <box2d/box2d.h>
#include <glm.hpp>

#include "GameTemplate.hpp"
#include "Camera.hpp"
#include "GameObject.hpp"
#include "Key.hpp"

namespace fe
{
  class Engine {
   public:
	enum class State{
	  None,
	  Initialize,
	  Start
	};
	
   private:

	static State state;
	static GLFWwindow* window;
	static b2WorldId world;
	static b2WorldDef worldDef;
	static Settings currentSettings;
	static Camera camera;
	
	/* Uses the index from the body ID to find Objects. */
	static std::unordered_map<int32_t, GameObject*> objectRegistry;
	
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
	
	static void RegisterObject(GameObject* _object);
	
	
	[[nodiscard]] static b2BodyId CreateBody(b2BodyDef* _bodyDef);
	
	static void SetWindowSize(uint16_t _width, uint16_t _height);
	static void EnableVsync(bool _enable);
	static void EnableFaceCulling(bool _enable);
	static void SetWindowTitle(const char* _title);
	static void SetGravity(b2Vec2 _gravity);
	
	
	static bool IsKeyPressed(Key _key);
	
  };
}