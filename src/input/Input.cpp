#include "src/input/Input.hpp"

namespace fe
{
  std::vector<Input::StateInfo> Input::stateInfos{};

  bool Input::anyKeyDown = false;
  b2Vec2 Input::mousePosition = {0, 0};

  void Input::Initialize() {
	stateInfos.reserve(400);

	for (int i = 0; i <= 400; i++) {
	  stateInfos.push_back(StateInfo{false, false, false});
	}
  }

  void Input::Reset() {
	for (StateInfo& info : stateInfos) {
	  info.GoingDown = false;
	  info.GoingUp = false;
	}

	anyKeyDown = false;
  }

  void Input::KeyCallback(GLFWwindow*, int _key, int, int _action, int) { // _window, _mods
	StateInfo& currentInfo = stateInfos[_key];

	if (_action == GLFW_PRESS) {
	  currentInfo.GoingDown = true;
	  anyKeyDown = true;
	} else if (_action == GLFW_RELEASE) {
	  currentInfo.GoingUp = true;
	  currentInfo.Down = false;
	}
	currentInfo.Down = _action == GLFW_PRESS || _action == GLFW_REPEAT;
  }

  void Input::MouseCallback(GLFWwindow*, int _button, int _action, int) { // _window, _mods 
	StateInfo& currentInfo = stateInfos[_button];
	if (_action == GLFW_PRESS) {
	  currentInfo.GoingDown = true;
	} else currentInfo.GoingUp = true;

	currentInfo.Down = _action == GLFW_PRESS;
  }

  void Input::CursorPosCallback(GLFWwindow*, double _xPos, double _yPos) { // _window
	mousePosition = {(float)_xPos, (float)_yPos};
  }

  bool Input::GetKeyDown(Key _key) {
	return stateInfos[(int)_key].GoingDown;
  }

  bool Input::GetKeyUp(Key _key) {
	return stateInfos[(int)_key].GoingUp;
  }

  bool Input::GetKey(Key _key) {
	StateInfo& info = stateInfos[(int)_key];
	return info.Down || info.GoingDown;
  }

  bool Input::GetAnyKeyDown() {
	return anyKeyDown;
  }

  bool Input::GetMouseUp(MouseButton _button) {
	return stateInfos[(int)_button].GoingUp;
  }

  bool Input::GetMouseDown(MouseButton _button) {
	return stateInfos[(int)_button].GoingDown;
  }

  bool Input::GetMouse(MouseButton _button) {
	return stateInfos[(int)_button].Down;
  }

  b2Vec2 Input::GetMousePos() {
	return mousePosition;
  }
}