#include "src/core/Engine.hpp"

#include <glad/glad.h>
#include <ext/matrix_clip_space.hpp>
#include <ext/matrix_transform.hpp>

#include "src/Core/Renderer.hpp"
#include "src/input/Input.hpp"
#include "src/Core/Box2DDebug.hpp"
#include "src/Core/GameTemplate.hpp"

namespace fe
{
  Engine::State Engine::state;
  GLFWwindow* Engine::window;
  Settings Engine::currentSettings{};
  b2WorldId Engine::world;
  b2WorldDef Engine::worldDef = b2DefaultWorldDef();
  glm::mat4 Engine::projectionMatrix;

  std::unordered_map<int32_t, std::unique_ptr<GameObject>> Engine::objectRegistry;

  void Engine::Initialize() {
	if (state != State::None) {
	  throw std::runtime_error("Engine has already been initialized!");
	}

	state = State::Initialize;

	worldDef.gravity = currentSettings.gravity;
	worldDef.enableContinous = true;
	world = b2CreateWorld(&worldDef);
	

	glfwInit();
	window = glfwCreateWindow(currentSettings.windowWidth, currentSettings.windowHeight, currentSettings.windowTitle, nullptr, nullptr);
	glfwMakeContextCurrent(window);

	glfwSetKeyCallback(window, Input::KeyCallback);
	glfwSetMouseButtonCallback(window, Input::MouseCallback);
	glfwSetCursorPosCallback(window, Input::CursorPosCallback);
	glfwSetWindowSizeCallback(window, Engine::WindowResizeCallback);

	RecalculateProjectionMatrix();

	Input::Initialize();

	//vsync
	glfwSwapInterval(currentSettings.enableVsync); // Enable: 1, Disable: 0

	gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);

	glEnable(GL_CULL_FACE);

	// Enable alpha transparency
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	glEnable(GL_BLEND);

	glfwShowWindow(window);

	Renderer::Initialize();
	Box2DDebug::Initialize();
  }

  void Engine::Start(GameTemplate& _gameTemplate) {

	if (state == State::None) {
	  throw std::runtime_error("Can't start the engine without initializing first!");
	}

	if (state == State::Start) {
	  throw std::runtime_error("Engine has already started!");
	}

	state = State::Start;

	float timeStep = 1.0f / 120.0f;
	int subStepCount = 10;

	_gameTemplate.Start();
	for (const auto& a : objectRegistry) {
	  a.second->InternalStart();
	}

	double lastTime = glfwGetTime();
	float deltaTime = 0;

	while (!glfwWindowShouldClose(window)) {
	  glfwPollEvents();

	  glClearColor(0.5f, 0.5f, 0.5f, 1.0f); // background color
//	  glClearDepth(1.0f);
	  glClear(GL_COLOR_BUFFER_BIT);
//	  glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	  double nowTime = glfwGetTime();
	  deltaTime = (float)(nowTime - lastTime);
	  lastTime = nowTime;

	  b2World_Step(world, timeStep, subStepCount);
	  
	  
	  _gameTemplate.Update(deltaTime);
	  for (auto& a : objectRegistry) {
		a.second->InternalUpdate(deltaTime);
	  }
	  

	  // Render
	  b2World_OverlapAABB(world,
						  {{0, 0}, {(float)currentSettings.windowWidth, (float)currentSettings.windowHeight}},
						  b2DefaultQueryFilter(),
						  &ScreenQueryCallback,
						  nullptr);

	  if (Box2DDebug::enabled) {
		b2World_Draw(world, &Box2DDebug::debugDraw);
	  }

	  Renderer::RenderQueued();

	  int display_w, display_h;
	  glfwGetFramebufferSize(window, &display_w, &display_h);
	  glad_glViewport(0, 0, display_w, display_h);

	  glfwSwapBuffers(window);

	  Input::Reset();
	}

	_gameTemplate.Stop();

	// Always clear objects before destroying world.
	// Otherwise, objects can't clean themselves up properly.
	objectRegistry.clear();
	b2DestroyWorld(world);
	Renderer::Cleanup();
	glfwDestroyWindow(window);
	glfwTerminate();
  }

  void Engine::Stop() {
	if (!glfwWindowShouldClose(window)) {
	  glfwSetWindowShouldClose(window, true);
	  return;
	}
  }

  bool Engine::ScreenQueryCallback(b2ShapeId _shape, void* context) {
	objectRegistry[b2Shape_GetBody(_shape).index1]->InternalRender();
	return true;
  }

  void Engine::WindowResizeCallback(GLFWwindow* _window, int _width, int _height) {
	currentSettings.windowWidth = _width;
	currentSettings.windowHeight = _height;
	RecalculateProjectionMatrix();
  }

  void Engine::RecalculateProjectionMatrix() {
	float left = 0;
	float right = currentSettings.windowWidth;
	float bottom = currentSettings.windowHeight;
	float top = 0;

	glm::mat4 orthographicMatrix = glm::ortho(left, right, bottom, top, currentSettings.nearPlane, currentSettings.farPlane);
	glm::mat4 zoomMatrix = glm::scale(glm::mat4(1.0f), {currentSettings.zoom, currentSettings.zoom, currentSettings.zoom});

	projectionMatrix = orthographicMatrix * zoomMatrix;
  }

  const Settings& Engine::GetCurrentSettings() {
	return currentSettings;
  }

  const b2WorldId& Engine::GetWorldId() {
	return world;
  }

  [[nodiscard]] b2Vec2 Engine::GetWindowSize() {
	return {(float) currentSettings.windowWidth, (float) currentSettings.windowHeight};
  }

  b2BodyId Engine::CreateBody(b2BodyDef* _bodyDef) {
	return b2CreateBody(world, _bodyDef);
  }

  void Engine::SetWindowSize(uint16_t _width, uint16_t _height) {
	currentSettings.windowWidth = _width;
	currentSettings.windowHeight = _height;
	Box2DDebug::SetDrawingBounds({{0, 0}, {(float)_width, (float)_height}});
	glfwSetWindowSize(window, currentSettings.windowWidth, currentSettings.windowHeight);
  }

  void Engine::ToggleVsync(bool _enable) {
	currentSettings.enableVsync = _enable;
	glfwSwapInterval(currentSettings.enableVsync);
  }

  void Engine::SetWindowTitle(const char* _title) {
	currentSettings.windowTitle = _title;
	glfwSetWindowTitle(window, currentSettings.windowTitle);
  }

  void Engine::SetGravity(b2Vec2 _gravity) {
	currentSettings.gravity = _gravity;
	b2World_SetGravity(world, currentSettings.gravity);
  }

  void Engine::Destroy(GameObject* _object) {
	objectRegistry.erase(_object->GetBody().index1);
  }

  void Engine::SetZoom(float _value) {
	currentSettings.zoom = _value;
	RecalculateProjectionMatrix();
  }

  void Engine::SetNearPlane(float _value) {
	currentSettings.nearPlane = _value;
	RecalculateProjectionMatrix();
  }

  void Engine::SetFarPlane(float _value) {
	currentSettings.farPlane = _value;
	RecalculateProjectionMatrix();
  }
}