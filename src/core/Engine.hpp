#pragma once

#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>

#include <box2d/box2d.h>
#include <unordered_map>
#include <mat4x4.hpp>

#include "src/settings/Settings.hpp"
#include "src/core/GameObject.hpp"

namespace fe
{
  class GameTemplate;
  class Renderer;

  /**
   * Drives all the underlying functionality to make the game work.
   */
  class Engine {
	// Todo: Look at this mess.
	friend Renderer;

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
	static b2WorldId world;
	static b2WorldDef worldDef;
	
	// Todo: Move to renderer.
	static glm::mat4 projectionMatrix;

	// Uses the index from the body ID to find Objects.
	static std::unordered_map<int32_t, std::unique_ptr<GameObject>> objectRegistry;
	
	static bool ScreenQueryCallback(b2ShapeId _shape, void* context);
	static void WindowResizeCallback(GLFWwindow* _window, int _width, int _height);
	static void RecalculateProjectionMatrix();
	
   public:
	/**
	 * Initializes the engine. Should always be called before constructing the user's game.
	 */
	static void Initialize();

	/**
	 * Starts the engine with a game.
	 * @param _gameTemplate User made game that inherits from a GameTemplate.
	 */
	static void Start(GameTemplate& _gameTemplate);
	
	/**
	 * Stops the engine and thus the game.
	 */
	static void Stop();

	/**
	 * Settings that are currently in use by the engine. 
	 */
	static const Settings& GetCurrentSettings();

	/**
	 * Box2D world that the game uses.
	 */
	static const b2WorldId& GetWorldId();
	
	/**
	 * @return The window size from the current settings. 
	 */
	static b2Vec2 GetWindowSize();
	
	/**
	 * Create a GameObject that is then managed by the engine.
	 * @tparam T Type of GameObject to create, this should always inherit from GameObject.
	 * @tparam Args The arguments necessary to construct a GameObject of the given type. This allows for custom constructors.
	 * @return A pointer to the created GameObject. Do not delete this pointer manually but instead use the Destroy() function.
	 */
	template<Derived<GameObject> T, typename... Args>
	static T* Instantiate(Args... args) {
	  auto a = std::unique_ptr<T>(new T(std::move(args)...));
	  auto pair = objectRegistry.emplace(a->GetBody().index1, std::move(a));
	  return (T*)pair.first->second.get();
	}
	
	/**
	 * Used to destroy a GameObject.
	 * @param _object GameObject to destroy.
	 */
	static void Destroy(GameObject* _object);

	/**
	 * Creates a Box2D body.
	 * @param _bodyDef Definition of the body.
	 * @return A b2BodyId that can be used to alter the created body.
	 */
	[[nodiscard]] static b2BodyId CreateBody(b2BodyDef* _bodyDef);

	/**
	 * Sets the window size.
	 * @param _width The width of the window.
	 * @param _height The height of the window.
	 */
	static void SetWindowSize(uint16_t _width, uint16_t _height);
	
	/**
	 * Enables or disables vsync.
	 */
	static void ToggleVsync(bool _enable);
	
	/**
	 * Sets the title that appears on the top of the window.
	 * @param _title The desired title.
	 */
	static void SetWindowTitle(const char* _title);
	
	/**
	 * Sets the gravity that the engine uses for its physics.
	 * @param _gravity The gravity as a 2D vector.
	 */
	static void SetGravity(b2Vec2 _gravity);
	
	/**
	 * Sets the background colour used to clear the screen every render loop.
	 */
	static void SetBackgroundColour(const Colour& _colour);
	
	/**
	 * Sets the zoom factor for the rendering.
	 */
	static void SetZoom(float _value);

	/**
	 * Sets the near plane that is used for rendering.
	 * Should be lower than the far plane.
	 */
	static void SetNearPlane(float _value);

	/**
	 * Sets the far plane that is used for rendering.
	 * Should higher than the near plane.
	 */
	static void SetFarPlane(float _value);
  };
}