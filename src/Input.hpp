#pragma once

#include <vector>

#include "Key.hpp"
#include "box2d/math_functions.h"
#include "MouseButton.hpp"

namespace fe
{
  class Engine;

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
	static bool GetKeyDown(Key _key);
	static bool GetKeyUp(Key _key);
	static bool GetKey(Key _key);
	static bool GetAnyKeyDown();

	static bool GetMouseUp(MouseButton _button);
	static bool GetMouseDown(MouseButton _button);
	static bool GetMouse(MouseButton _button);
	
	[[nodiscard]] static b2Vec2 GetMousePos();
  };
}


