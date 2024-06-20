#pragma once

#include <vector>
#include <box2d/box2d.h>

#include "src/input/Key.hpp"
#include "src/input/MouseButton.hpp"

namespace fe
{
  class Engine;

  /**
   * Manages user input.
   */
  class Input {
	friend Engine;

   private:
	struct StateInfo {
	  bool GoingDown;
	  bool GoingUp;
	  bool Down;
	};

	static bool anyKeyDown;
	static b2Vec2 mousePosition;
	static std::vector<StateInfo> stateInfos;

	static void Initialize();
	static void Reset();

	static void KeyCallback(GLFWwindow* _window, int _key, int _scancode, int _action, int _mods);
	static void MouseCallback(GLFWwindow* _window, int _button, int _action, int _mods);
	static void CursorPosCallback(GLFWwindow* _window, double _xPos, double _yPos);

   public:
	/**
	 * @return Whether the given key is pressed this frame.
	 */
	static bool GetKeyDown(Key _key);
	
	/**
	 * @return Whether the given key is released this frame.
	 */
	static bool GetKeyUp(Key _key);
	
	/**
	 * @return Whether the given key is down.
	 */
	static bool GetKey(Key _key);
	
	/**
	 * @return Whether any key is pressed this frame.
	 */
	static bool GetAnyKeyDown();

	/**
	 * @return Whether the given mouse button is released this frame. 
	 */
	static bool GetMouseUp(MouseButton _button);
	
	/**
	 * @return Whether the given mouse button is pressed this frame.
	 */
	static bool GetMouseDown(MouseButton _button);
	
	/**
	 * @return Whether the given mouse button is down.
	 */
	static bool GetMouse(MouseButton _button);
	
	/**
	 * @return The position of the mouse on the screen. 
	 */
	[[nodiscard]] static b2Vec2 GetMousePos();
  };
}